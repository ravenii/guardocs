<?php

//--------------------------------------------------------------------------------

// Base function for adding a GL transaction
// $date_ is display date (non-sql)
// $amount is in $currency currency
// if $currency is not set, then defaults to no conversion

function add_gl_trans($type, $trans_id, $date_, $account, $dimension, $dimension2, $memo_,
	$amount, $currency=null, $person_type_id=null, $person_id=null,	$err_msg="")
{
	global $use_audit_trail;

	$date = date2sql($date_);
	if ($currency != null)
		$amount_in_home_currency = to_home_currency($amount, $currency, $date_);
	else
		$amount_in_home_currency = $amount;
	if ($dimension == null || $dimension < 0)
		$dimension = 0;
	if ($dimension2 == null || $dimension2 < 0)
		$dimension2 = 0;
	if (isset($use_audit_trail) && $use_audit_trail)
	{
		if ($memo_ == "" || $memo_ == null)
			$memo_ = $_SESSION["wa_current_user"]->username;
		else
			$memo_ = $_SESSION["wa_current_user"]->username . " - " . $memo_;
	}
	$sql = "INSERT INTO gl_trans ( type, type_no, tran_date,
		account, dimension_id, dimension2_id, memo_, amount";

	if ($person_type_id != null)
		$sql .= ", person_type_id, person_id";

	$sql .= ") ";

	$sql .= "VALUES ($type, $trans_id, '$date',
		'$account', $dimension, $dimension2, ".db_escape($memo_).", $amount_in_home_currency";

	if ($person_type_id != null)
		$sql .= ", $person_type_id, '$person_id'";

	$sql .= ") ";

	if ($err_msg == "")
		$err_msg = "The GL transaction could not be inserted";

	return db_query($sql, $err_msg);
}

//--------------------------------------------------------------------------------

// GL Trans for standard costing, always home currency regardless of person
// $date_ is display date (non-sql)
// $amount is in HOME currency

function add_gl_trans_std_cost($type, $trans_id, $date_, $account, $dimension, $dimension2,
	$memo_,	$amount, $person_type_id=null, $person_id=null, $err_msg="")
{
	if ($amount != 0)
		return add_gl_trans($type, $trans_id, $date_, $account, $dimension, $dimension2, $memo_,
			$amount, null, $person_type_id, $person_id, $err_msg);
	else
		return null;
}

//--------------------------------------------------------------------------------

function get_gl_transactions($from_date, $to_date, $trans_no=0,
	$account=null, $dimension=0, $dimension2=0, $filter_type=null)
{
	$from = date2sql($from_date);
	$to = date2sql($to_date);

	$sql = "SELECT gl_trans.*, chart_master.account_name FROM gl_trans, chart_master
		WHERE chart_master.account_code=gl_trans.account
		AND tran_date >= '$from'
		AND tran_date <= '$to'";
	if ($trans_no > 0)
		$sql .= " AND gl_trans.type_no LIKE '%$trans_no'";

	if ($account != null)
		$sql .= " AND gl_trans.account = '$account'";

	if ($dimension > 0)
		$sql .= " AND gl_trans.dimension_id = $dimension";

	if ($dimension2 > 0)
		$sql .= " AND gl_trans.dimension2_id = $dimension2";

	if ($filter_type != null AND is_numeric($filter_type))
		$sql .= " AND gl_trans.type= $filter_type";

	$sql .= " ORDER BY tran_date";

	return db_query($sql, "The transactions for could not be retrieved");
}


//--------------------------------------------------------------------------------

function get_gl_trans($type, $trans_id)
{
	$sql = "SELECT gl_trans.*, chart_master.account_name FROM gl_trans, chart_master
		WHERE chart_master.account_code=gl_trans.account
		AND gl_trans.type=$type AND gl_trans.type_no=$trans_id";

	return db_query($sql, "The gl transactions could not be retrieved");
}

//--------------------------------------------------------------------------------

function get_gl_balance_from_to($from_date, $to_date, $account, $dimension=0, $dimension2=0)
{
	$from = date2sql($from_date);
	$to = date2sql($to_date);

    $sql = "SELECT SUM(amount) FROM gl_trans
		WHERE account='$account'";
	if ($from_date != "")
		$sql .= "  AND tran_date > '$from'";
	if ($to_date != "")
		$sql .= "  AND tran_date < '$to'";
	if ($dimension > 0)
		$sql .= " AND dimension_id = $dimension";
	if ($dimension2 > 0)
		$sql .= " AND dimension2_id = $dimension2";

	$result = db_query($sql, "The starting balance for account $account could not be calculated");

	$row = db_fetch_row($result);
	return $row[0];
}

//--------------------------------------------------------------------------------

function get_gl_trans_from_to($from_date, $to_date, $account, $dimension=0, $dimension2=0)
{
	$from = date2sql($from_date);
	$to = date2sql($to_date);

    $sql = "SELECT SUM(amount) FROM gl_trans
		WHERE account='$account'";
	if ($from_date != "")
		$sql .= " AND tran_date >= '$from'";
	if ($to_date != "")
		$sql .= " AND tran_date <= '$to'";
	if ($dimension > 0)
		$sql .= " AND dimension_id = $dimension";
	if ($dimension2 > 0)
		$sql .= " AND dimension2_id = $dimension2";

	$result = db_query($sql, "Transactions for account $account could not be calculated");

	$row = db_fetch_row($result);
	return $row[0];
}

//--------------------------------------------------------------------------------

function get_budget_trans_from_to($from_date, $to_date, $account, $dimension=0, $dimension2=0)
{

	$from = date2sql($from_date);
	$to = date2sql($to_date);

	$sql = "SELECT SUM(amount) FROM budget_trans
		WHERE account='$account' ";
	if ($from_date != "")
		$sql .= " AND tran_date >= '$from' ";
	if ($to_date != "")
		$sql .= " AND tran_date <= '$to' ";
	if ($dimension > 0)
		$sql .= " AND dimension_id = $dimension";
	if ($dimension2 > 0)
		$sql .= " AND dimension2_id = $dimension2";
	$result = db_query($sql,"No budget accounts were returned");

	$row = db_fetch_row($result);
	return $row[0];
}

//--------------------------------------------------------------------------------

function add_journal_entries($items, $date_, $ref, $reverse, $memo_=null)
{
	begin_transaction();

	$trans_type = systypes::journal_entry();
	$trans_id = get_next_trans_no($trans_type);

	foreach ($items as $journal_item)
	{
		$is_bank_to = is_bank_account($journal_item->code_id);

		add_gl_trans($trans_type, $trans_id, $date_, $journal_item->code_id,
			$journal_item->dimension_id, $journal_item->dimension2_id,
			$journal_item->reference, $journal_item->amount);
    	if ($is_bank_to)
    	{
    		add_bank_trans($trans_type, $trans_id, $journal_item->code_id, $ref,
    			$date_, 3, $journal_item->amount,
    			0, "", get_company_currency(),
    			"Cannot insert a destination bank transaction");
    	}
	}

	add_comments($trans_type, $trans_id, $date_, $memo_);

	references::save($trans_type, $trans_id, $ref);

	if ($reverse)
	{

    	//$reversingDate = date(user_date_display(),
    	//	Mktime(0,0,0,get_month($date_)+1,1,get_year($date_)));
    	$reversingDate = begin_month(add_months($date_, 1));

    	$trans_id_reverse = get_next_trans_no($trans_type);

    	foreach ($items as $journal_item)
    	{
			$is_bank_to = is_bank_account($journal_item->code_id);

    		add_gl_trans($trans_type, $trans_id_reverse, $reversingDate,
    			$journal_item->code_id, $journal_item->dimension_id, $journal_item->dimension2_id,
    			$journal_item->reference, -$journal_item->amount);
    		if ($is_bank_to)
    		{
    			add_bank_trans($trans_type, $trans_id_reverse, $journal_item->code_id, $ref,
    				$reversingDate, 3, $journal_item->amount,
    				0, "", get_company_currency(),
    				"Cannot insert a destination bank transaction");
    		}
    	}

    	add_comments($trans_type, $trans_id_reverse, $reversingDate, $memo_);

    	references::save($trans_type, $trans_id_reverse, $ref);
	}

	commit_transaction();

	return $trans_id;
}

//--------------------------------------------------------------------------------------------------

function exists_gl_trans($type, $trans_id)
{
	$sql = "SELECT type_no FROM gl_trans WHERE type=$type AND type_no=$trans_id";
	$result = db_query($sql, "Cannot retreive a gl transaction");

    return (db_num_rows($result) > 0);
}

//--------------------------------------------------------------------------------------------------

function void_gl_trans($type, $trans_id, $nested=false)
{
	if (!$nested)
		begin_transaction();

	$sql = "UPDATE gl_trans SET amount=0	WHERE type=$type AND type_no=$trans_id";

	db_query($sql, "could not void gl transactions for type=$type and trans_no=$trans_id");

	if (!$nested)
		commit_transaction();
}

//--------------------------------------------------------------------------------------------------

?>
