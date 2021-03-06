<?php

//-------------------------------------------------------------------------------------------------------------

function stock_cost_update($stock_id, $material_cost, $labour_cost, $overhead_cost,
	$last_cost)
{
	$mb_flag = get_mb_flag($stock_id);
    
    if (is_service($mb_flag))
    {
    	display_db_error("Cannot do cost update for Service item : $stock_id", "");	
    }		
	
	$update_no = -1;
	
	begin_transaction();
	
	$sql = "UPDATE stock_master SET material_cost=$material_cost, 
		labour_cost=$labour_cost, 
		overhead_cost=$overhead_cost, 
		last_cost=$last_cost 
		WHERE stock_id='$stock_id'";
	db_query($sql,"The cost details for the inventory item could not be updated");

	$qoh = get_qoh_on_date($_POST['stock_id']);
	
	if ($qoh > 0)
	{
    
	   	$update_no = get_next_trans_no(systypes::cost_update());
	   	$date_ = Today();
		if (!is_date_in_fiscalyear($date_))
			$date_ = end_fiscalyear();
	   
		$stock_gl_code = get_stock_gl_code($stock_id);
	 
		$new_cost = $material_cost + $labour_cost + $overhead_cost;
	  
		$value_of_change = $qoh * ($new_cost - $last_cost);
	   
		$memo_ = "Cost was " . $last_cost . " changed to " . $new_cost . " x quantity on hand of $qoh";
		add_gl_trans_std_cost(systypes::cost_update(), $update_no, $date_, $stock_gl_code["adjustment_account"], 
			$stock_gl_code["dimension_id"], $stock_gl_code["dimension2_id"], $memo_, (-$value_of_change));	   

		add_gl_trans_std_cost(systypes::cost_update(), $update_no, $date_, $stock_gl_code["inventory_account"], 0, 0, $memo_, 
			$value_of_change);	   
   	}	   		   	

	commit_transaction();
	
	return $update_no;		
}

//-------------------------------------------------------------------------------------------------------------

?>