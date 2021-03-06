<?php

//-------------------------------------------------------------------------------------------------------------

function add_supp_invoice_item($supp_trans_type, $supp_trans_no, $stock_id, $description,
	$gl_code, $unit_price, $unit_tax, $quantity, $grn_item_id, $po_detail_item_id, $memo_,
	$err_msg="")
{
	$sql = "INSERT INTO supp_invoice_items (supp_trans_type, supp_trans_no, stock_id, description, gl_code, unit_price, unit_tax, quantity,
	  	grn_item_id, po_detail_item_id, memo_) ";
	$sql .= "VALUES ($supp_trans_type, $supp_trans_no, ".db_escape($stock_id).
	", ".db_escape($description).", ".db_escape($gl_code).", $unit_price, $unit_tax, $quantity,
		$grn_item_id, $po_detail_item_id, ".db_escape($memo_).")";

	if ($err_msg == "")
		$err_msg = "Cannot insert a supplier transaction detail record";

	db_query($sql, $err_msg);

	return db_insert_id();
}

//-------------------------------------------------------------------------------------------------------------

function add_supp_invoice_gl_item($supp_trans_type, $supp_trans_no, $gl_code, $amount, $memo_, $err_msg="")
{
	return add_supp_invoice_item($supp_trans_type, $supp_trans_no,  "", "", $gl_code, $amount,
		0, 0, /*$grn_item_id*/0, /*$po_detail_item_id*/0, $memo_, $err_msg);
}


//----------------------------------------------------------------------------------------

function get_supp_invoice_items($supp_trans_type, $supp_trans_no)
{
	$sql = "SELECT *, unit_price AS FullUnitPrice FROM supp_invoice_items
		WHERE supp_trans_type = $supp_trans_type
		AND supp_trans_no = $supp_trans_no ORDER BY id";
	return db_query($sql, "Cannot retreive supplier transaction detail records");
}

//----------------------------------------------------------------------------------------

function void_supp_invoice_items($type, $type_no)
{
	$sql = "UPDATE supp_invoice_items SET quantity=0, unit_price=0
		WHERE supp_trans_type = $type AND supp_trans_no=$type_no";
	db_query($sql, "could not void supptrans details");
}

//----------------------------------------------------------------------------------------

function add_supp_invoice_tax_item($supp_trans_type, $supp_trans_no, $tax_type_id,
	$rate, $included_in_price, $amount)
{
	$sql = "INSERT INTO supp_invoice_tax_items (supp_trans_type, supp_trans_no, tax_type_id, rate, included_in_price, amount)
		VALUES ($supp_trans_type, $supp_trans_no, $tax_type_id, $rate, $included_in_price, $amount)";

	db_query($sql, "The supplier transaction tax detail could not be added");
}

//----------------------------------------------------------------------------------------

function get_supp_invoice_tax_items($supp_trans_type, $supp_trans_no)
{
	$sql = "SELECT supp_invoice_tax_items.*, tax_types.name AS tax_type_name
		FROM supp_invoice_tax_items,tax_types
		WHERE supp_trans_type = $supp_trans_type
		AND supp_trans_no = $supp_trans_no
		AND tax_types.id = supp_invoice_tax_items.tax_type_id";

	return db_query($sql, "The supplier transaction tax details could not be queried");
}

//----------------------------------------------------------------------------------------

function void_supp_invoice_tax_items($type, $type_no)
{
	$sql = "UPDATE supp_invoice_tax_items SET amount=0
		WHERE supp_trans_type = $type
		AND supp_trans_no=$type_no";

	db_query($sql, "The supplier transaction tax details could not be voided");
}

?>