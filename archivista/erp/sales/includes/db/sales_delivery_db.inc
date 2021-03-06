<?php
//-----------------------------------------------------------------------------
// insert/update sales delivery
//
function write_sales_delivery(&$delivery,$bo_policy)
{

	$trans_no = $delivery->trans_no;
	if (is_array($trans_no)) $trans_no = key($trans_no);

	begin_transaction();

	$delivery_items_total = $delivery->get_items_total_dispatch();
	$freight_tax = $delivery->get_shipping_tax();

// mark sales order for concurrency conflicts check
	update_sales_order_version($delivery->src_docs);

	$tax_total = 0;
	$taxes = $delivery->get_taxes(); // all taxes with freight_tax

	foreach ($taxes as $taxitem) {
		$tax_total +=  $taxitem['Value'];
	}
	/* Insert/update the debtor_trans */
	$delivery_no = write_customer_trans(13, $trans_no, $delivery->customer_id,
		$delivery->Branch, $delivery->document_date, $delivery->reference,
		$delivery_items_total, 0,
		$delivery->tax_included ? 0 : $tax_total-$freight_tax,
		$delivery->freight_cost,
		$delivery->tax_included ? 0 : $freight_tax,
		$delivery->sales_type, $delivery->order_no, 0,
		$delivery->ship_via, $delivery->due_date);

	if ($trans_no == 0) {
		$delivery->trans_no = array($delivery_no=>0);
	} else {
		void_gl_trans(13, $delivery_no, true);
		void_stock_move(13, $delivery_no);
		delete_comments(13, $delivery_no);
	}

	foreach ($delivery->line_items as $delivery_line) {
		$line_price = $delivery_line->line_price();
		$line_taxfree_price = get_tax_free_price_for_item($delivery_line->stock_id,
			$delivery_line->price, 0, $delivery->tax_included,
			$delivery->tax_group_array);

		$line_tax = get_full_price_for_item($delivery_line->stock_id, $delivery_line->price,
			0, $delivery->tax_included, $delivery->tax_group_array) - $line_taxfree_price;

		/* add delivery details for all lines */
		write_customer_trans_detail_item(13, $delivery_no, $delivery_line->stock_id,
			$delivery_line->item_description, 
			$delivery_line->date_from,
			$delivery_line->notes,
			$delivery_line->qty_dispatched,
			$delivery_line->line_price(), $line_tax,
			$delivery_line->discount_percent, $delivery_line->standard_cost,
			$trans_no ? $delivery_line->id : 0);

	// Now update sales_order_details for the quantity delivered
		if ($delivery_line->qty_old != $delivery_line->qty_dispatched)
			update_parent_line(13, $delivery_line->id,
				$delivery_line->qty_dispatched-$delivery_line->qty_old);

		if ($delivery_line->qty_dispatched != 0) {
			add_stock_move_customer(13, $delivery_line->stock_id, $delivery_no,
				$delivery->Location, $delivery->document_date, $delivery->reference,
				-$delivery_line->qty_dispatched, $delivery_line->standard_cost,1,
				$line_price, $delivery_line->discount_percent);


			$stock_gl_code = get_stock_gl_code($delivery_line->stock_id);

			/* insert gl_trans to credit stock and debit cost of sales at standard cost*/
			if ($delivery_line->standard_cost != 0) {

				/*first the cost of sales entry*/
				add_gl_trans_std_cost(13, $delivery_no,
				$delivery->document_date, $stock_gl_code["cogs_account"],
					$stock_gl_code["dimension_id"], $stock_gl_code["dimension2_id"], "",
					$delivery_line->standard_cost * $delivery_line->qty_dispatched,
					payment_person_types::customer(), $delivery->customer_id,
					"The cost of sales GL posting could not be inserted");

				/*now the stock entry*/
				//$stock_gl_code = get_stock_gl_code($order_line->stock_id);

				add_gl_trans_std_cost(13, $delivery_no, $delivery->document_date,
					$stock_gl_code["inventory_account"], 0, 0, "",
					(-$delivery_line->standard_cost * $delivery_line->qty_dispatched),
					payment_person_types::customer(), $delivery->customer_id,
					"The stock side of the cost of sales GL posting could not be inserted");

			} /* end of if GL and stock integrated and standard cost !=0 */

		} /*quantity dispatched is more than 0 */
	} /*end of order_line loop */

	if ($bo_policy == 0) {
		// if cancelling any remaining quantities
		close_sales_order($delivery->order_no);
	}

	// taxes - this is for printing purposes
	foreach ($taxes as $taxitem) {
		if ($taxitem['Value'] != 0) {
    		    add_customer_trans_tax_detail_item(13, $delivery_no, $taxitem['tax_type_id'],
				$taxitem['rate'], $delivery->tax_included, $taxitem['Value']);
		}
	}

	add_comments(13, $delivery_no, $delivery->document_date, $delivery->Comments);

	if ($trans_no == 0) {
		if ($delivery->reference!='auto')
			references::save_last($delivery->reference, 13);
	}

	commit_transaction();

	return $delivery_no;
}

//--------------------------------------------------------------------------------------------------

function void_sales_delivery($type, $type_no)
{
	begin_transaction();

	void_gl_trans($type, $type_no, true);

	// for invoices and credits related to invoices,
	// reverse all the changes in the sales order
	$items_result = get_customer_trans_details($type, $type_no);

	$order = get_customer_trans_order($type, $type_no);

	if ($order) {
		while ($row = db_fetch($items_result)) {
			update_parent_line(13, $row['id'], -$row['quantity']);
		}
	}

	// clear details after they've been reversed in the sales order
	void_customer_trans_details($type, $type_no);

	void_customer_trans_tax_details($type, $type_no);

	void_cust_allocations($type, $type_no);

	// do this last because other voidings can depend on it
	// DO NOT MOVE THIS ABOVE VOIDING or we can end up with trans with alloc < 0
	void_customer_trans($type, $type_no);

	commit_transaction();
}
?>
