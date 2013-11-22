<?php

class AssignProfessorManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function AssignProfessorManager( $obj_user, $obj_db ) 
	{
	  	$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	
	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function view_assigned_professor() {
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT U.FirstName, U.LastName, U.UserId, C.Name, C.CourseId
								  FROM User U, XG_Teaches T, Course C															  WHERE T.prof_id = U.UserId AND C.courseId = T.course_id 
									AND U.PrivilegeLvl = " . UP_PROFESSOR .";";
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
	function assign_professor( $str_prof_id, $int_course_id ) {
  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "INSERT INTO XG_Teaches( professor_id, course_id)
							                VALUES ( '" . $this->m_obj_db->format_sql_string( $str_prof_id ) . "', " 
							                . $this->m_obj_db->format_sql_string( $int_course_id ) . " )";
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    MessageHandler::add_message( MSG_FAIL, "Error assigning professor to course" );
	    
	    return false;
	  }

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
		  MessageHandler::add_message( MSG_SUCCESS, "Professer successfully assigned to course!" );
		  
		  return false;
	  }
	
	  return true;
		
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function unassign_professor( $str_prof_id, $int_course_id ) {
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "DELETE FROM XG_Teaches
							                WHERE professor_id = '" . $this->m_obj_db->format_sql_string( $str_prof_id ) . "'  AND
												course_id = " . $this->m_obj_db->format_sql_string( $int_course_id );
			   break;
		}
		
		if ( $str_sql_query == null )
		{
		  MessageHandler::add_message( MSG_FAIL, "Error removing professor from course" );
		  
		  return false;
		}
		
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Professor successfully removed from course!" );
			
			return false;
		}

		return true;
		
		
		
	}
	
}

?>