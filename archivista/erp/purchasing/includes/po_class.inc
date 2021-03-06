<?php

/* Definition of the purch_order class to hold all the information for a purchase order and delivery
*/

class purch_order 
{

	var $supplier_id;
	
	var $line_items; /*array of objects of class line_details using the product id as the pointer */
	var $curr_code;
	var $requisition_no;
	var $delivery_address;
	var $Comments;
	var $Location;
	var $supplier_name;
	var $orig_order_date;
	var $order_no; /*Only used for modification of existing orders otherwise only established when order committed */
	var $lines_on_order;
	
	var $reference;
	
	function purch_order()
	{
		/*Constructor function initialises a new purchase order object */
		$this->line_items = array();
		$this->lines_on_order = $this->order_no = $this->supplier_id = 0;
	}

	function add_to_order($line_no, $stock_id, $qty, $item_descr, $price, $uom, $req_del_date, $qty_inv, $qty_recd)
	{
		if ($qty != 0 && isset($qty))
		{
			$this->line_items[$line_no] = new line_details($line_no, $stock_id, $item_descr, $qty, $price, $uom, $req_del_date, $qty_inv, $qty_recd);
			$this->lines_on_order++;
			Return 1;
		}
		Return 0;
	}

	function update_order_item($line_no, $qty, $price, $req_del_date)
	{
		$this->line_items[$line_no]->quantity = $qty;
		$this->line_items[$line_no]->price = $price;
		$this->line_items[$line_no]->req_del_date = $req_del_date;
		$this->line_items[$line_no]->price = $price;
	}

	function remove_from_order($line_no)
	{
		 $this->line_items[$line_no]->Deleted = true;
	}
	
	function order_has_items() 
	{
		if (count($this->line_items) > 0)
		{
		   	foreach ($this->line_items as $ordered_items) 
		   	{
				if ($ordered_items->Deleted == false)
				{
					return true;
				}
		   	}
		}
		return false;		
	}
	
	function clear_items() 
	{
    	unset($this->line_items);
		$this->line_items = array();
		
		$this->lines_on_order = 0;  
		$this->order_no = 0;
	}

	
	function any_already_received()
	{
		/* Checks if there have been deliveries or invoiced entered against any of the line items */
		if (count($this->line_items) > 0)
		{
		   	foreach ($this->line_items as $ordered_items) 
		   	{
				if ($ordered_items->qty_received != 0 || $ordered_items->qty_inv != 0)
				{
					return 1;
				}
		   	}
		}
		return 0;
	}

	function some_already_received($line_no)
	{
		/* Checks if there have been deliveries or amounts invoiced against a specific line item */
		if (count($this->line_items) > 0)
		{
		   	if ($this->line_items[$line_no]->qty_received != 0 || 
		   		$this->line_items[$line_no]->qty_inv != 0)
		 	{
				return 1;
		   	}
		}
		return 0;
	}
} /* end of class defintion */

class line_details 
{

	Var $line_no;
	Var $po_detail_rec;
	Var $stock_id;
	Var $item_description;
	Var $quantity;
	Var $price;
	Var $units;
	Var $req_del_date;
	Var $qty_inv;
	Var $qty_received;
	Var $standard_cost;
	Var $receive_qty;
	Var $Deleted;	
	
	function line_details($line_no, $stock_item, $item_descr, $qty, $prc, $uom, $req_del_date, $qty_inv, $qty_recd)
	{

		/* Constructor function to add a new LineDetail object with passed params */
		$this->line_no = $line_no;
		$this->stock_id = $stock_item;
		$this->item_description = $item_descr;
		$this->quantity = $qty;
		$this->req_del_date = $req_del_date;
		$this->price = $prc;
		$this->units = $uom;
		$this->qty_received = $qty_recd;
		$this->qty_inv = $qty_inv;
		$this->receive_qty = 0;	/*initialise these last two only */
		$this->standard_cost =0;
		$this->Deleted = false;
	}
}

?>
