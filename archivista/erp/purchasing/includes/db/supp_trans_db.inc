<?php

//-------------------------------------------------------------------------------------------------------------

function add_supp_trans($type, $supplier_id, $date_, $due_date, $reference, $supp_reference, 
	$amount, $amount_tax, $discount, $err_msg="")
{
	$date = date2sql($date_);
	$due_date = date2sql($due_date);
	
	$trans_no = get_next_trans_no($type);	

	$curr = get_supplier_currency($supplier_id);
	$rate = get_exchange_rate_from_home_currency($curr, $date_);	


	$sql = "INSERT INTO supp_trans (trans_no, type, supplier_id, tran_date, due_date, 
		reference, supp_reference, ov_amount, ov_gst, rate, ov_discount) ";
	$sql .= "VALUES ($trans_no, $type, $supplier_id, '$date', '$due_date',
		".db_escape($reference).", ".db_escape($supp_reference).", $amount, $amount_tax, $rate, $discount)";
	
	if ($err_msg == "")
		$err_msg = "Cannot insert a supplier transaction record";
		
	db_query($sql, $err_msg);		

	return $trans_no;	
}

//-------------------------------------------------------------------------------------------------------------

function get_supp_trans($trans_no, $trans_type=-1)
{
	$sql = "SELECT supp_trans.*, (supp_trans.ov_amount+supp_trans.ov_gst+supp_trans.ov_discount) AS Total, 
		suppliers.supp_name AS supplier_name, suppliers.curr_code AS SupplierCurrCode ";
	
	if ($trans_type == 22) 
	{
		// it's a payment so also get the bank account
		$sql .= ", bank_accounts.bank_name, bank_accounts.bank_account_name, bank_accounts.bank_curr_code, 
			bank_trans_types.name AS BankTransType, bank_trans.amount AS BankAmount,
			bank_trans.ref ";  
	}  
	
	$sql .= " FROM supp_trans, suppliers "; 

	if ($trans_type == 22) 
	{
		// it's a payment so also get the bank account
		$sql .= ", bank_trans, bank_accounts, bank_trans_types ";  
	}	
	
	$sql .= " WHERE supp_trans.trans_no=$trans_no 
		AND supp_trans.supplier_id=suppliers.supplier_id";
					
	if ($trans_type > 0)
		$sql .= " AND supp_trans.type=$trans_type ";					
					
	if ($trans_type == 22) 
	{
		// it's a payment so also get the bank account
		$sql .= " AND bank_trans.trans_no =$trans_no
			AND bank_trans.type=$trans_type	
			AND bank_trans_types.id = bank_trans.bank_trans_type_id
			AND bank_accounts.account_code=bank_trans.bank_act ";  
	}						
	
	$result = db_query($sql, "Cannot retreive a supplier transaction");
	
    if (db_num_rows($result) == 0) 
    {
       // can't return nothing
       display_db_error("no supplier trans found for given params", $sql, true);
       exit;
    }
    
    if (db_num_rows($result) > 1) 
    {
       // can't return multiple
       display_db_error("duplicate supplier transactions found for given params", $sql, true);
       exit;
    }	
    
    return db_fetch($result);   	
}

//----------------------------------------------------------------------------------------

function get_supplier_transactions($extra_fields=null, $extra_conditions=null, $extra_tables=null)
{
	$sql = "SELECT supp_trans.*,
		ov_amount+ov_gst+ov_discount AS Total,   
		suppliers.supp_name, suppliers.address,
		suppliers.curr_code ";
				
	if ($extra_fields)
		$sql .= ", $extra_fields ";			
				
	$sql .= " FROM supp_trans, suppliers ";
	if ($extra_tables)
		$sql .= " ,$extra_tables ";
				
	$sql .= " WHERE supp_trans.supplier_id=suppliers.supplier_id";
				
	if ($extra_conditions)
		$sql .= " AND $extra_conditions ";	
		
	$sql .= " ORDER BY trans_no";	
	
	return db_query($sql, "Cannot retreive supplier transactions");
}

//----------------------------------------------------------------------------------------

function exists_supp_trans($type, $type_no)
{
	if ($type == 25)
		return exists_grn($type_no);
		
	$sql = "SELECT trans_no FROM supp_trans WHERE type=$type
		AND trans_no=$type_no";
	$result = db_query($sql, "Cannot retreive a supplier transaction");	
	
    return (db_num_rows($result) > 0);				
}

//----------------------------------------------------------------------------------------

function void_supp_trans($type, $type_no)
{
	$sql = "UPDATE supp_trans SET ov_amount=0, ov_discount=0, ov_gst=0, 
		alloc=0 WHERE type=$type AND trans_no=$type_no";
			
	db_query($sql, "could not void supp transactions for type=$type and trans_no=$type_no");
}

//----------------------------------------------------------------------------------------

function post_void_supp_trans($type, $type_no)
{
	if ($type == 22) 
	{
		void_supp_payment($type, $type_no);
		return true;
	}
	
	if ($type == 20 || $type == 21) 
	{
	 	void_supp_invoice($type, $type_no);
		return true;	 	
	}
	 
	if ($type == 25) 
	{
	 	return void_grn($type_no);
	}	 
	
	return false;	
}

//----------------------------------------------------------------------------------------

?>