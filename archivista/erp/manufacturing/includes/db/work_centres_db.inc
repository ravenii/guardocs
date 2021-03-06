<?php

function add_work_centre($name, $description)
{
	$sql = "INSERT INTO workcentres (name, description)
		VALUES (".db_escape($name).",".db_escape($description).")";

	db_query($sql, "could not add work centre");
}

function update_work_centre($type_id, $name, $description)
{
	$sql = "UPDATE workcentres SET name=".db_escape($name).", description=".db_escape($description)."
		WHERE id=$type_id";

	db_query($sql, "could not update work centre");
}

function get_all_work_centres()
{
	$sql = "SELECT * FROM workcentres";

	return db_query($sql, "could not get all work centres");
}

function get_work_centre($type_id)
{
	$sql = "SELECT * FROM workcentres WHERE id=$type_id";

	$result = db_query($sql, "could not get work centre");

	return db_fetch($result);
}

function delete_work_centre($type_id)
{
	$sql="DELETE FROM workcentres WHERE id=$type_id";

	db_query($sql, "could not delete work centre");
}

?>