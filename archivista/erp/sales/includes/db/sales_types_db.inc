<?php

function add_sales_type($name, $tax_included,$price_factor)
{
	$sql = "INSERT INTO sales_types ".
	       "(sales_type,tax_included,price_factor) VALUES (".
				 db_escape($name).",'$tax_included',$price_factor)";
		
	db_query($sql, "could not add sales type");		
}

function update_sales_type($id, $name, $tax_included,$price_factor)
{
	$sql = "UPDATE sales_types SET ".
	       "sales_type = ".db_escape($name).",".
	       "tax_included =$tax_included, price_factor=$price_factor ".
				 "WHERE id = $id";
	db_query($sql, "could not update sales type");			
}

function get_all_sales_types()
{
	$sql = "SELECT * FROM sales_types";
	
	return db_query($sql, "could not get all sales types");
} 

function get_sales_type($id)
{
	$sql = "SELECT * FROM sales_types WHERE id=$id";
	
	$result = db_query($sql, "could not get sales type");
	
	return db_fetch($result);
}

function get_sales_type_name($id)
{
	$sql = "SELECT sales_type FROM sales_types WHERE id=$id";
	
	$result = db_query($sql, "could not get sales type");
	
	$row = db_fetch_row($result);
	return $row[0];
}

function delete_sales_type($id)
{
	$sql="DELETE FROM sales_types WHERE id=$id";
	db_query($sql,"The Sales type record could not be deleted");

	$sql ="DELETE FROM prices WHERE sales_type_id='$id'";
	db_query($sql,"The Sales type prices could not be deleted");
}

?>
