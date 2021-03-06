<?php

function add_item_tax_type($name, $exempt, $exempt_from)
{
	begin_transaction();
	
	$sql = "INSERT INTO item_tax_types (name, exempt) 
		VALUES (".db_escape($name).",$exempt)";
		
	db_query($sql, "could not add item tax type");	
	
	$id = db_insert_id();
	
	// add the exemptions
	add_item_tax_type_exemptions($id, $exempt_from);
	
	commit_transaction();
}

function update_item_tax_type($id, $name, $exempt, $exempt_from)
{
	begin_transaction();
	
	$sql = "UPDATE item_tax_types SET name=".db_escape($name).
	",	exempt=$exempt WHERE id=$id";
	
	db_query($sql, "could not update item tax type");	
	
	// readd the exemptions
	delete_item_tax_type_exemptions($id);
	add_item_tax_type_exemptions($id, $exempt_from);		
	
	commit_transaction();	
}

function get_all_item_tax_types()
{
	$sql = "SELECT * FROM item_tax_types";
	
	return db_query($sql, "could not get all item tax type");
} 

function get_item_tax_type($id)
{
	$sql = "SELECT * FROM item_tax_types WHERE id=$id";
	
	$result = db_query($sql, "could not get item tax type");
	
	return db_fetch($result);
}

function get_item_tax_type_for_item($stock_id)
{
	$sql = "SELECT item_tax_types.* FROM item_tax_types,stock_master WHERE stock_master.stock_id='$stock_id'
		AND item_tax_types.id=stock_master.tax_type_id";
	
	$result = db_query($sql, "could not get item tax type");
	
	return db_fetch($result);	
}

function delete_item_tax_type($id)
{
	begin_transaction();
		
	$sql = "DELETE FROM item_tax_types WHERE id=$id";
		
	db_query($sql, "could not delete item tax type");
	// also delete all exemptions
	delete_item_tax_type_exemptions($id);
	
	commit_transaction();	
}

function add_item_tax_type_exemptions($id, $exemptions)
{
	for ($i = 0; $i < count($exemptions); $i++) 
	{
		$sql = "INSERT INTO item_tax_type_exemptions (item_tax_type_id, tax_type_id)
			VALUES ($id,  " . $exemptions[$i] . ")";
		db_query($sql, "could not add item tax type exemptions");					
	}		
}

function delete_item_tax_type_exemptions($id)
{
	$sql = "DELETE FROM item_tax_type_exemptions WHERE item_tax_type_id=$id";
	
	db_query($sql, "could not delete item tax type exemptions");					
}

function get_item_tax_type_exemptions($id)
{
	$sql = "SELECT * FROM item_tax_type_exemptions WHERE item_tax_type_id=$id";
	
	return db_query($sql, "could not get item tax type exemptions");
}

?>