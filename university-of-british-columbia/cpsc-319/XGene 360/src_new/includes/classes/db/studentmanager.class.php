<?php

require_once( 'usermanager.class.php' );

class StudentManager extends UserManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function StudentManager( $obj_user, $obj_db )
	{
	    $this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function view_students() 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:				// TA sees only students which are assigned to courses he assists // need to check
			
				$str_sql_query = "SELECT student.UserId, student.FirstName, student.LastName "
							   . "FROM User TA, User student, XG_Assists Ast, Course C, "
							   . "XG_ProblemTraitMadeFor P, XG_Assigns Asn "
							   . "WHERE TA.PrivilegeLvl = " . UP_TA . " "
							   . "AND TA.UserId = Ast.ta_id "
							   . "AND Ast.course_id = C.CourseId "
							   . "AND C.CourseId = P.course_id "
							   . "AND Asn.problem_id = P.problem_id "
							   . "AND Asn.student_id = student.UserId "
							   . "AND TA.UserId = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->$str_username ) . "' "
							   . "ORDER BY student.LastName, student.FirstName, student.UserId"; 
				break;
				
			case UP_PROFESSOR:		// Professors and the admin see ALL students
			case UP_ADMINISTRATOR:
			
			    $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName, U.StudentNum "
							   . "FROM User U "
							   . "WHERE PrivilegeLvl = " . UP_STUDENT . " "
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
	
	function view_student_problems( $str_student_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:				// TA sees only students which are assigned to courses he assists
			case UP_PROFESSOR:		// Professors and the admin see ALL students
			case UP_ADMINISTRATOR:
			
			    $str_sql_query = "SELECT P.problem_id, P.problem_name, C.Name, "
							   . "UNIX_TIMESTAMP( P.start_date ) AS start_date, "
							   . "UNIX_TIMESTAMP( P.due_date ) AS due_date "
			                   . "FROM User U, XG_Assigns A, XG_ProblemTraitMadeFor P, Course C "
			                   . "WHERE P.problem_id = A.problem_id "
			                   . "AND C.CourseId = P.course_id "
			                   . "AND A.student_id = U.UserId "
			                   . "AND U.UserId = '" . $this->m_obj_db->format_sql_string( $str_student_id ) . "' "
			                   . "ORDER BY P.problem_name";
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