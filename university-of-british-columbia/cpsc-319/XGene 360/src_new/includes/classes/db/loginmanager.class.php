<?php

class LoginManager
{
	function authenticate( $str_username, $str_password, $obj_db )
	{
		$str_sql_query = "SELECT U.UserId, U.Pwd, U.PrivilegeLvl, U.FirstName, U.LastName, U.PrivilegeLvl
							          FROM User U
							          WHERE U.UserId = '" . $obj_db->format_sql_string( $str_username ) . "'
								          AND STRCMP(U.Pwd, Password('" . $obj_db->format_sql_string( $str_password ) . "')) = 0";

		return LoginManager::query_credentials( $str_sql_query, $obj_db );
	}
	
	
	function authenticate_hash( $str_username, $str_password_hash, $obj_db )
	{
		$str_sql_query = "SELECT U.UserId, U.Pwd, U.PrivilegeLvl, U.FirstName, U.LastName, U.PrivilegeLvl
							          FROM User U
							          WHERE U.UserId = '" . $obj_db->format_sql_string( $str_username ) . "'
								          AND STRCMP(U.Pwd, '" . $obj_db->format_sql_string( $str_password_hash ) . "') = 0";
	  
		return LoginManager::query_credentials( $str_sql_query, $obj_db );
	}
	
	
	function query_credentials( $str_sql_query, $obj_db )
	{
		
		// perform query
		$res_query = $obj_db->query_select( $str_sql_query );

		// check if authenticated
		if ($obj_db->get_number_of_rows( $res_query ) != 1 )
		{
			return null;
		}
		
		// fetch user information
		$res_row = $obj_db->fetch( $res_query );
		
		// create return object
		$obj_user = new User;
		
		// fill object fields
		$obj_user->str_first_name = $res_row->FirstName;
		$obj_user->str_last_name  = $res_row->LastName;
		$obj_user->str_username = $res_row->UserId;
		$obj_user->str_password = $res_row->Pwd;
		$obj_user->int_privilege  = $res_row->PrivilegeLvl;
		
		return $obj_user;
	}
}

?>