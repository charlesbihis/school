<?php

class AssignTAManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function AssignTAManager( $obj_user, $obj_db )
	{
	  	$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function view_assigned_TAs() 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
				$str_sql_query = "SELECT U.FirstName, U.LastName, U.UserId, C.Name, C.CourseId "
							   . "FROM User U, XG_Assists A, Course C "
							   . "WHERE A.ta_id = U.UserId AND A.course_id = C.CourseId "
							   . "AND U.PrivilegeLvl = " . UP_TA;
				break;
		}
	
		if ( $str_sql_query == null )
		{
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	
	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function assign_TA( $str_ta_id, $int_course_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "INSERT INTO XG_Assists(course_id, ta_id) "
							   . "VALUES ( " . $this->m_obj_db->format_sql_string( $int_course_id ) . ", '" 
							   . $this->m_obj_db->format_sql_string( $str_ta_id ) . "' )";
				break;
		}
	
		if ( $str_sql_query == null )
		{
			ErrorHandler::add_error( 101 );
	    
			return false;
		}

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			ErrorHandler::add_error( 200 );
		  
			return false;
		}
	
		return true;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function unassign_TA( $str_ta_id, $int_course_id ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "DELETE FROM XG_Assists " 
							   . "WHERE course_id = ". $this->m_obj_db->format_sql_string( $int_course_id ) . " "
							   . "AND ta_id = '" . $this->m_obj_db->format_sql_string( $str_ta_id ) . "'";
				break;
		}
		
		if ( $str_sql_query == null )
		{
			ErrorHandler::add_error( 101 );
		  
			return false;
		}
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			ErrorHandler::add_error( 202 );
			
			return false;
		}

		return true;
	}
}

?>