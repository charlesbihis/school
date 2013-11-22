<?php

class AssignProblemManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $obj_user is a valid user class enumerated in the globals and $obj_db is a valid connected databse object
	 * POST: assignproblemmanager object is constructed
	 * @param $obj_user. User object of the current logged in user
	 * @param $obj_db. Database object of the current database connection
	 */
	function AssignProblemManager( $obj_user, $obj_db )
	{
	  	$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/**
	 * View assigned problems for a given user class
	 * PRE: none
	 * POST: a  valid resource is returned, or null on error
	 * @return Resource containing database query results, or null on error
	 */
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
	
	/**
	 * Assigns a problem to a course
	 * PRE: $int_problem_id and $int_course_id are valid ids respectivly
	 * POST: Problem is assigned to all students in a given course
	 * @return True on sucess, false on failure
	 */
	function assign_problem_to_course( $int_problem_id, $int_course_id ) {
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

	/**
	 * Unassigns a problem to a course
	 * PRE: $int_problem_id is a valid problem id
	 * POST: Problem is unassigned from all students in a given course
	 * @return true on sucess, false on failure
	 */
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
	
	/**
	 * View students assigned to a problem
	 * PRE: a valid problem id is given
	 * POST: a  valid resource is returned, or null on error
	 * @return Resource containing database query results, or null on error
	 */
	function view_students_assigned_to_problem( $int_problem_id ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			    $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "
							   . "FROM User U, XG_Assigns A "
							   . "WHERE PrivilegeLvl = " . UP_STUDENT . " "
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