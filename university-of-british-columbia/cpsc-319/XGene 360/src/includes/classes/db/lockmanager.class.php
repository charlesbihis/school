<?php

class LockManager
{
	var $m_obj_db = null;
	
	function LockManager( $obj_db ) {
		$this->m_obj_db = $obj_db;
	}
	
	/*
	 * Generates a unique serial id for page locking purposes.
	 */
	function get_serial()
	{
		$serial  = null;
		$serial .= (isset($_SESSION[COOKIE_USERNAME]) ? $_SESSION[COOKIE_USERNAME] : "COOKIE_USERNAME");
		//$serial .= (isset($HTTP_SERVER_VARS["REMOTE_ADDR"]) ? $HTTP_SERVER_VARS["REMOTE_ADDR"] : "REMOTE_ADDR");
		//$serial .= (isset($_SERVER['REQUEST_URI']) ? $_SERVER['REQUEST_URI'] : "REQUEST_URI");
		$serial .= microtime();
		return md5($serial);
	}
	
	
	/*
	 * Page lock is used to prevent reposting of form data.
	 * 
	 * @param $str_serial_id. Unique page serial number.
	 * @return return true if allow post, false if do not allow post
	 */
	function page_lock( $str_serial_id )
	{

		$str_sql_query = "INSERT INTO XG_Locks(serial_id) VALUES('". $str_serial_id ."')";
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{	  
			// insert failed
			// page already been submitted once
			return false;
		}
		
		// insert suceeded
		// page has not been submitted previously
		return true;
	}
	
	/*
	 * Flushes old locks from database.
	 */
	function purge()
	{
		$str_sql_query = "DELETE FROM XG_Locks WHERE timestamp < DATE_SUB(NOW(), INTERVAL 1 HOUR)";
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{			
			return false;
		}
		
		return true;
	}
}

?>