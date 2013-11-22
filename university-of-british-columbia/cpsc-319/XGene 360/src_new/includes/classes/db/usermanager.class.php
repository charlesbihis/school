<?php

class UserManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;
  
	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function UserManager( $obj_user, $obj_db )
	{
		$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	function view_user( $str_user_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{				   
			case UP_TA:
				
				// TODO: view students
				
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
  			
				$str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "																			// updating User table
							   . "From User U "
							   . "WHERE U.UserId = '" . $this->m_obj_db->format_sql_string( $str_user_id ) . "'";
				break;			    
		}
		
		if ( $str_sql_query == null )
		{
			// TODO: fix up
			ErrorHandler::add_error( 101 );
		}
  
		return $this->m_obj_db->query_select( $str_sql_query );
	}

	function create_user( $str_user_id, $int_user_privilege, $str_first_name, $str_last_name, $str_password, $int_student_num )
	{
		$str_sql_query = null;
	
		switch ( $this->m_obj_user->int_privilege )
		{				   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:

				$str_sql_query = "INSERT INTO User(UserId, PrivilegeLvl, FirstName, LastName, Pwd, StudentNum) "		// inserting into User table
                               . "VALUES ('" . $this->m_obj_db->format_sql_string( $str_user_id ) . "', "					// UserId
							   . $int_user_privilege . ", '"															// PrivilegeLvl
							   . $this->m_obj_db->format_sql_string( $str_first_name ) . "', '"						// FirstName
							   . $this->m_obj_db->format_sql_string( $str_last_name ) . "', "							// LastName
							   . "Password('" . $this->m_obj_db->format_sql_string( $str_password ) . "'), "			// Pwd
							   . $this->m_obj_db->format_sql_string( $int_student_num ) . ")";																// StudentNum
				break;
		}
	
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			ErrorHandler::add_error( 101 );
	    
			return false;
		}

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			// TODO: fix up Error Handler or Message Handler
				  
			return false;
		}
	
		return true;
	}  // create_user
	
	function modify_user( $str_user_id, $str_first_name, $str_last_name, $int_student_number )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{				   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
  			
				$str_sql_query = "UPDATE User "																			// updating User table
						       . "SET FirstName = '". $this->m_obj_db->format_sql_string( $str_first_name ) ."', "		// FirstName
							   . "LastName = '". $this->m_obj_db->format_sql_string( $str_last_name ) . "', "		// LastName
							   . "StudentNum = ".  $this->m_obj_db->format_sql_string( $int_student_number ) . " "
							   . "WHERE UserId = '" . $this->m_obj_db->format_sql_string( $str_user_id ) . "'";
				break;			    
		}
		
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			ErrorHandler::add_error( 101 );
		}
  
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			// TODO: fix up Error Handler or Message Handler
			
			return false;
		}
	  
		return true;
	} // modify_user
	
	function modify_password( $str_user_id, $str_password )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{				   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
  			
				$str_sql_query = "UPDATE User "																			// updating User table
                               . "SET Pwd = Password('" . $this->m_obj_db->format_sql_string( $str_password ) . "') "	// Pwd
							   . "WHERE UserId = '" . $this->m_obj_db->format_sql_string( $str_user_id ) . "'";
				break;			    
		}
		
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			ErrorHandler::add_error( 101 );
		}
  
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			// TODO: fix up Error Handler or Message Handler
			
			return false;
		}
	  
		return true;
	} // modify_password
	
	function delete_user ( $str_user_id )
	{
		$str_sql_query = null;
		
		switch ( $this->m_obj_user->int_privilege )
		{				   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:

			   $str_sql_query = "DELETE FROM User "
//							  . "WHERE PrivilegeLvl = " . UP_PROFESSOR . " AND"
							  . "WHERE UserId = '" . $this->m_obj_db->format_sql_string( $str_user_id ) . "'";														// StudentNum
				break;
		}
	
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			ErrorHandler::add_error( 101 );
	    
			return false;
		}

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			// TODO: fix up Error Handler or Message Handler
				  
			return false;
		}
	
		return true;
	}
}
  
?>
