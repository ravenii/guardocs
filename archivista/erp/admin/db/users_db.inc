<?php

function add_user($user_id, $real_name, $password, $phone, $email, $full_access, $language)
{
	$sql = "INSERT INTO users (user_id, real_name, password, phone, email, full_access, language)
		VALUES (".db_escape($user_id).", 
		".db_escape($real_name).", ".db_escape($password) .",".db_escape($phone).",
		 ".db_escape($email).", $full_access, ".db_escape($language).")";

	db_query($sql, "could not add user for $user_id");
}

//-----------------------------------------------------------------------------------------------

function update_user_password($user_id, $password)
{
	$sql = "UPDATE users SET password=".db_escape($password) . "
		WHERE user_id = ".db_escape($user_id);

	db_query($sql, "could not update user password for $user_id");
}

//-----------------------------------------------------------------------------------------------

function update_user($user_id, $real_name, $phone, $email, $full_access, $language)
{
	$sql = "UPDATE users SET real_name=".db_escape($real_name).
	", phone=".db_escape($phone).",
		email=".db_escape($email).",
		full_access=$full_access,
		language=".db_escape($language)."
		WHERE user_id = ".db_escape($user_id);

	db_query($sql, "could not update user for $user_id");
}

//-----------------------------------------------------------------------------------------------

function update_user_display_prefs($user_id, $price_dec, $qty_dec, $exrate_dec, $percent_dec, $showgl,
	$showcodes, $date_format, $date_sep, $tho_sep, $dec_sep, $theme, $pagesize)
{
	$sql = "UPDATE users SET
		prices_dec=".db_escape($price_dec).",
		qty_dec=".db_escape($qty_dec).",
		rates_dec=".db_escape($exrate_dec).",
		percent_dec=".db_escape($percent_dec).",
		show_gl=".db_escape($showgl).",
		show_codes=".db_escape($showcodes).",
		date_format=".db_escape($date_format).",
		date_sep=".db_escape($date_sep).",
		tho_sep=".db_escape($tho_sep).",
		dec_sep=".db_escape($dec_sep).",
		theme=".db_escape($theme).",
		page_size=".db_escape($pagesize)."
		WHERE user_id = ".db_escape($user_id);

	db_query($sql, "could not update user display prefs for $user_id");
}

//-----------------------------------------------------------------------------------------------


function get_users()
{
	$sql = "SELECT * FROM users";

	return db_query($sql, "could not get users");
}

//-----------------------------------------------------------------------------------------------

function get_user($user_id)
{
	$sql = "SELECT * FROM users WHERE user_id = '$user_id'";

	$result = db_query($sql, "could not get user for $user_id");

	return db_fetch($result);
}

//-----------------------------------------------------------------------------------------------

function delete_user($user_id)
{
	$sql="DELETE FROM users WHERE user_id='$user_id'";

	db_query($sql, "could not delete user $user_id");
}

//-----------------------------------------------------------------------------------------------

function get_user_for_login($user_id, $password)
{
	set_global_connection();

	$sql = "SELECT * FROM users WHERE user_id = '$user_id' AND password='$password'";

	return db_query($sql, "could not get validate user login for $user_id");
}

//-----------------------------------------------------------------------------------------------

function update_user_visitdate($user_id)
{
	$sql = "UPDATE users SET last_visit_date='". date("Y-m-d H:i:s") ."'
		WHERE user_id=".db_escape($user_id);

	db_query($sql, "could not update last visit date for user $user_id");
}

//-----------------------------------------------------------------------------------------------

?>