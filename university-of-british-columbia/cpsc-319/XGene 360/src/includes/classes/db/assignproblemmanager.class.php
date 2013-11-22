<?php

class AssignProblemManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function AssignProblemManager( $obj_user, $obj_db )
	{
	  	$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 // function not called anywhere, can be axed?
	function view_assigned_problem() {
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			   
			case UP_PROFESSOR:
				
			
			
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT U.FirstName, U.LastName, U.UserId, P.problem_id
										FROM Users U, XG_Assigns A, XG_ProblemTraitMadeFor P
										WHERE U.UserId = A.student_id AND A.problem_id = P.problem_id AND 
											U.PrivilegeLvl = " . UP_STUDENT .";";
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	*/
	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 // as per discussion, the problem cannot be reassign when it has been created
	function assign_problem_to_course( $int_problem_id, $int_course_id ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "UPDATE XG_ProblemTraitMadeFor 
			                     SET course_id = " . $this->m_obj_db->format_sql_string( $int_course_id ) . " 
			                     WHERE problem_id = ". $this->m_obj_db->format_sql_string( $int_problem_id );
			   
			   break;
		}
	
		if ( $str_sql_query == null )
		{
			MessageHandler::add_message( MSG_FAIL, "Error assigning problem to course" );
	    
			return false;
		}

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
		  MessageHandler::add_message( MSG_SUCCESS, "Problem successfully assigned to course!" );
		  
		  return false;
	  }
	
	  return true;
		
	}
*/
	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 // as per discussion, you can't unassign problem from course no more -.-
	function unassign_problem_from_course( $int_problem_id ) {
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "UPDATE XG_ProblemTraitMadeFor 
			                     SET course_id = 0 
			                     WHERE problem_id = ". $this->m_obj_db->format_sql_string( $int_problem_id );
			   break;
		}
		
		if ( $str_sql_query == null )
		{
		  MessageHandler::add_message( MSG_FAIL, "Error removing problem from course" );
		  
		  return false;
		}
		
		if ( !$this->query_commit( $str_sql_query ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Problem successfully removed from course!" );
			
			return false;
		}

		return true;
		
		
		
	}
	*/
	
	function view_students_assigned_to_problem( $int_problem_id ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			
				$str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "
							   . "FROM User U, XG_Assigns A, XG_Assists Ass, User Current, XG_ProblemTraitMadeFor P "
							   . "WHERE U.PrivilegeLvl = " . UP_STUDENT . " "
							   . "AND A.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
							   . "AND P.problem_id = A.problem_id "
							   . "AND U.UserId = A.student_id "
							   . "AND P.course_id = Ass.course_id "
							   . "AND Current.UserId = Ass.ta_id "
							   . "AND Current.UserId = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
							   . "ORDER BY U.LastName, U.FirstName, U.StudentNum, U.UserId";
				break;
			
			
			case UP_PROFESSOR:
				
				$str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "
							   . "FROM User U, XG_Assigns A, XG_Teaches T, User Current, XG_ProblemTraitMadeFor P "
							   . "WHERE U.PrivilegeLvl = " . UP_STUDENT . " "
							   . "AND A.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
							   . "AND P.problem_id = A.problem_id "
							   . "AND U.UserId = A.student_id "
							   . "AND P.course_id = T.course_id "
							   . "AND Current.UserId = T.professor_id "
							   . "AND Current.UserId = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
							   . "ORDER BY U.LastName, U.FirstName, U.StudentNum, U.UserId";
				break;
			
			case UP_ADMINISTRATOR:
			
			    $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "
							   . "FROM User U, XG_Assigns A "
							   . "WHERE U.PrivilegeLvl = " . UP_STUDENT . " "
									. "AND " . $int_problem_id . " = A.problem_id "
									. "AND U.UserId = A.student_id "
							   . "ORDER BY U.LastName, U.FirstName, U.StudentNum, U.UserId";
				break;
		}
	
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	
	
}

?>