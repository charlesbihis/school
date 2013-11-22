<?php

require_once( 'usermanager.class.php' );

class TAManager extends UserManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;
	
	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function TAManager( $obj_user, $obj_db )
	{
	    $this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function view_tas() 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:

			   $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName "
                               . "FROM User U " 
                               . "WHERE U.PrivilegeLvl = " . UP_TA . " "
                               . "ORDER BY U.LastName, U.FirstName, U.UserId";
				break;
		}
	
        if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	
	function view_ta_courses( $str_ta_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:

			    $str_sql_query = "SELECT C.CourseId, C.Name, C.Description "
			                   . "FROM Course C, User U, XG_Assists A "
			                   . "WHERE A.course_id = C.CourseId "
			                   . "AND A.ta_id = U.UserId "
			                   . "AND U.UserId = '" . $this->m_obj_db->format_sql_string( $str_ta_id ) . "' "
			                   . "ORDER BY C.Name, C.Description";
				break;
		}
	
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
/* /* // have delete_user now
	function delete_ta( $str_ta_id )
	{
		$str_sql_query = null;
/*		$str_sql_query = "start transaction";
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			return false;
		}
		
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:

			$str_sql_query = "DELETE FROM User "
                           . "WHERE PrivilegeLvl = " . UP_TA . " "
                           . "AND UserId = '" . $this->m_obj_db->format_sql_string( $str_ta_id ) . "'";
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
*/
}

?>