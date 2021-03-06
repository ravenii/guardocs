<?php

function add_movement_type($name)
{
	$sql = "INSERT INTO movement_types (name)
		VALUES (".db_escape($name).")";

	db_query($sql, "could not add item movement type");
}

function update_movement_type($type_id, $name)
{
	$sql = "UPDATE movement_types SET name=".db_escape($name)."
			WHERE id=$type_id";

	db_query($sql, "could not update item movement type");
}

function get_all_movement_type()
{
	$sql = "SELECT * FROM movement_types";

	return db_query($sql, "could not get all item movement type");
}

function get_movement_type($type_id)
{
	$sql = "SELECT * FROM movement_types WHERE id=$type_id";

	$result = db_query($sql, "could not get item movement type");

	return db_fetch($result);
}

function delete_movement_type($type_id)
{
	$sql="DELETE FROM movement_types WHERE id=$type_id";

	db_query($sql, "could not delete item movement type");
}

?>