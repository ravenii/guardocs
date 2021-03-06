<?php

//-----------------------------------------------------------------------------
//	Add or update Sales Invoice
//
function write_sales_invoice(&$invoice)
{

	$trans_no = $invoice->trans_no;
	if (is_array($trans_no))
		$trans_no = key($trans_no);

	$date_ = $invoice->document_date;
	$charge_shipping =$invoice->freight_cost;

	begin_transaction();

	$company_data = get_company_prefs();

	$branch_data = get_branch_accounts($invoice->Branch);

	// offer price values without freight costs
	$items_total = $invoice->get_items_total_dispatch();
	$freight_tax = $invoice->get_shipping_tax();

	$delivery_no = $invoice->src_docs;
	if (is_array($delivery_no))
		$delivery_no = 0;

	update_customer_trans_version(get_parent_type(10), $invoice->src_docs);

	$ov_gst = 0;
	$taxes = $invoice->get_taxes(); // all taxes with freight_tax

	foreach ($taxes as $taxitem) {
		$ov_gst +=  $taxitem['Value'];
	}

	if($invoice->tax_included==0) {
	    $items_added_tax = $ov_gst-$freight_tax;
	    $freight_added_tax = $freight_tax;
	} else {
	    $items_added_tax = 0;
	    $freight_added_tax = 0;
	}

	/* Insert/update the debtor_trans */
	$sales_order = $invoice->order_no;
	if (is_array($sales_order))
			$sales_order = $sales_order[0]; // assume all crucial SO data are same for every delivery

	$invoice_no = write_customer_trans(10, $trans_no, $invoice->customer_id,
		$invoice->Branch, $date_, $invoice->reference, $items_total, 0,
		$items_added_tax, $invoice->freight_cost, $freight_added_tax,
		$invoice->sales_type, $sales_order, $delivery_no,
		$invoice->ship_via, $invoice->due_date);

	if ($trans_no == 0) {
		$invoice->trans_no = array($invoice_no=>0);
		set_document_parent($invoice);
	} else {
		delete_comments(10, $invoice_no);
		void_gl_trans(10, $invoice_no, true);
		void_cust_allocations(10, $invoice_no); // ?
		void_customer_trans_tax_details(10, $invoice_no);
	}

	foreach ($invoice->line_items as $invoice_line) {

		$line_taxfree_price = get_tax_free_price_for_item($invoice_line->stock_id,
			$invoice_line->price, 0, $invoice->tax_included,
			$invoice->tax_group_array);

		$line_tax = get_full_price_for_item($invoice_line->stock_id,
			$invoice_line->price, 0, $invoice->tax_included,
			$invoice->tax_group_array) - $line_taxfree_price;

		write_customer_trans_detail_item(10, $invoice_no, $invoice_line->stock_id,
			$invoice_line->item_description, $invoice_line->date_from,
			$invoice_line->notes, $invoice_line->qty_dispatched,
			$invoice_line->line_price(), $line_tax,	$invoice_line->discount_percent,
			$invoice_line->standard_cost,
			$trans_no ? $invoice_line->id : 0);

		// Update delivery items for the quantity invoiced
		if ($invoice_line->qty_old != $invoice_line->qty_dispatched)
			update_parent_line(10, $invoice_line->id, ($invoice_line->qty_dispatched-$invoice_line->qty_old));

		if ($invoice_line->qty_dispatched != 0) {
			$stock_gl_code = get_stock_gl_code($invoice_line->stock_id);

			if ($invoice_line->line_price() != 0) {
				//Post sales transaction to GL credit sales

					add_gl_trans_customer(10, $invoice_no, $date_, $stock_gl_code["sales_account"],
						$stock_gl_code["dimension_id"], $stock_gl_code["dimension2_id"],
						(-$line_taxfree_price * $invoice_line->qty_dispatched),
						$invoice->customer_id, "The sales price GL posting could not be inserted");

				if ($invoice_line->discount_percent != 0) {

					add_gl_trans_customer(10, $invoice_no, $date_,
						$branch_data["sales_discount_account"], $stock_gl_code["dimension_id"],
						$stock_gl_code["dimension2_id"],
						($line_taxfree_price * $invoice_line->qty_dispatched * $invoice_line->discount_percent),
						$invoice->customer_id, "The sales discount GL posting could not be inserted");
				} /*end of if discount !=0 */
			}
		} /*quantity dispatched is more than 0 */
	} /*end of delivery_line loop */

	/*Post debtors transaction to GL debit debtors, credit freight re-charged and credit sales */
	if (($items_total + $charge_shipping) != 0) {
		add_gl_trans_customer(10, $invoice_no, $date_, $branch_data["receivables_account"], 0, 0,
			($items_total + $charge_shipping + $items_added_tax + $freight_added_tax),
			$invoice->customer_id, "The total debtor GL posting could not be inserted");
	}
	if ($charge_shipping != 0) {
		add_gl_trans_customer(10, $invoice_no, $date_, $company_data["freight_act"], 0, 0,
			-$invoice->get_tax_free_shipping(), $invoice->customer_id,
			"The freight GL posting could not be inserted");
	}
	// post all taxes
	foreach ($taxes as $taxitem) {
		if ($taxitem['Value'] != 0) {
			add_customer_trans_tax_detail_item(10, $invoice_no, $taxitem['tax_type_id'],
				$taxitem['rate'], $invoice->tax_included, $taxitem['Value']);

			add_gl_trans_customer(10, $invoice_no, $date_, $taxitem['sales_gl_code'], 0, 0,
				(-$taxitem['Value']), $invoice->customer_id,
				"A tax GL posting could not be inserted");
		}
	}

	add_comments(10, $invoice_no, $date_, $invoice->Comments);

	if ($trans_no == 0) {
		references::save_last($invoice->reference, 10);
	}

	commit_transaction();

	return $invoice_no;
}

//--------------------------------------------------------------------------------------------------

function void_sales_invoice($type, $type_no)
{
	begin_transaction();

	void_bank_trans($type, $type_no, true);
	void_gl_trans($type, $type_no, true);

	// for invoices and credits related to invoices,
	// reverse all the changes in the sales order
	$items_result = get_customer_trans_details($type, $type_no);

	$delivery = get_customer_trans_link($type, $type_no);

	if ($delivery) {
		while ($row = db_fetch($items_result)) {
			update_parent_line(10, $row['id'], -$row['quantity']);
		}
	}

	// clear details after they've been reversed in the sales order
	void_customer_trans_details($type, $type_no);

	void_customer_trans_tax_details($type, $type_no);

	void_cust_allocations($type, $type_no);

	// do this last because other voidings can depend on it - especially voiding
	// DO NOT MOVE THIS ABOVE VOIDING or we can end up with trans with alloc < 0
	void_customer_trans($type, $type_no);

	commit_transaction();
}

?>
