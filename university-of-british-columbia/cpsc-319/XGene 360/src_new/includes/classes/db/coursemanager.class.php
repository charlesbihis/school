<?php

class CourseManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;
  
	/***
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function CourseManager( $obj_user, $obj_db )
	{
	    $this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* View Courses associated with user.
	 * PRE: $user_id is a valid userID
	 * POST: Course listing returned respective of $user_class and $user_id
	 * @param $user_id is that of the current logged in user
	 */
	function view_courses()
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_STUDENT:
			
			   $str_sql_query  = "SELECT C.CourseId, C.Name, C.Description 
							                  FROM Course C, XG_ProblemTraitMadeFor P, XG_Assigns A, User U
							                  WHERE C.CourseID = P.course_id
								                  AND P.problem_id = A.problem_id
								                  AND A.student_id = U.UserID
								                  AND U.PrivilegeLvl = " . UP_STUDENT . " 
								                  AND U.UserID = '". $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "'
							                  ORDER BY C.Name";
			   break;
			   
			case UP_TA:
			   
   			   $str_sql_query = "SELECT C.CourseId, C.Name, C.Description
							                  FROM Course C, XG_Assists A, User U
							                  WHERE C.CourseID = A.course_id
								                  AND A.ta_id = U.UserID
								                  AND U.PrivilegeLvl = " . UP_TA . " 
								                  AND U.UserID = '". $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "'
							                  ORDER BY C.Name";
			   break;
			   
			case UP_PROFESSOR:
			
			      $str_sql_query = "SELECT C.CourseId, C.Name, C.Description "
								 . "FROM Course C, XG_Teaches T, User U "
								 . "WHERE C.CourseId = T.course_id "
								 . "AND T.professor_id = U.UserID "
								 . "AND U.PrivilegeLvl = " . UP_PROFESSOR . " "
								 . "AND U.UserID = '". $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
								 . "ORDER BY C.Name";
				  break;
							
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT C.CourseId, C.Name, C.Description "
							    . "FROM Course C "
							    . "ORDER BY C.Name";
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	
	// course name and course decription
	function view_course_details( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT C.Name, C.Description "
			                   . "FROM Course C "
			                   . "WHERE C.CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id );
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}

	// professors that teach this course
	function view_course_professors( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName "
			                   . "FROM Course C, User U, XG_Teaches T "
			                   . "WHERE U.UserId = T.professor_id "
			                   . "AND T.course_id = C.CourseId "
			                   . "AND C.CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id );
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}	
	
	// tas that assist this course
	function view_course_tas( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT U.UserId, U.FirstName, U.LastName "
			                   . " FROM Course C, User U, XG_Assists A "
			                   . " WHERE U.UserId = A.ta_id "
			                   . " AND A.course_id = C.CourseId "
			                   . " AND C.CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id );
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}	
	
	// this course has problems
	function view_course_problems( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT P.problem_id, P.problem_name, "
							   . "UNIX_TIMESTAMP(P.start_date) AS start_date, "
							   . "UNIX_TIMESTAMP(P.due_date) AS due_date "
			                   . "FROM Course C, XG_ProblemTraitMadeFor P "
			                   . "WHERE P.course_id = C.CourseId "
			                   . "AND C.CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id );
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}		
	
	// this course has problems, each problem has students
	function view_course_students( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_TA:
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT DISTINCT U.UserId, U.FirstName, U.LastName
			                      FROM User U, XG_Assigns A
			                      WHERE U.UserId = A.student_id
			                      AND A.problem_id IN
			                      (
			                        SELECT P.problem_id
			                        FROM Course C, XG_ProblemTraitMadeFor P
			                        WHERE P.course_id = C.CourseId
			                        AND C.CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id ) ."
			                      );";
			   break;
		}
	
	  if ( $str_sql_query == null )
	  {
	    return null;
	  }
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}	
	
	function add_course( $str_course_name, $str_course_description )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "INSERT INTO Course(Name, Description)
							                VALUES ( '" . $this->m_obj_db->format_sql_string( $str_course_name ) . "', '" 
							                . $this->m_obj_db->format_sql_string( $str_course_description ) . "' );";
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

	function delete_course( $int_course_id )
	{
	  $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
			   $str_sql_query = "DELETE FROM Course
							                WHERE CourseId = ". $this->m_obj_db->format_sql_string( $int_course_id ) . ";";
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
		
		// ------------------------------------------------
		// need to clean associated database relations here		
		// ------------------------------------------------
		
		return true;
		
	}
	
	function modify_course( $int_course_id, $str_course_name, $str_course_description )
	{
	  $str_sql_query = null;
	  
	  switch ( $this->m_obj_user->int_privilege )
	  {				   
			  case UP_PROFESSOR:
			  case UP_ADMINISTRATOR:
  			
			    $str_sql_query = "UPDATE Course 
							                SET Name = '". $this->m_obj_db->format_sql_string( $str_course_name ) . "',
								                Description = '" . $this->m_obj_db->format_sql_string( $str_course_description ) . "'  
							                WHERE CourseId = " . $this->m_obj_db->format_sql_string( $int_course_id ) . ";";
			    break;			    
		}
		
		if ( $str_sql_query == null )
		{
		  ErrorHandler::add_error( 101 );
		}
  
    if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
    {
		  ErrorHandler::add_error( 101 );
		  
		  return false;
	  }
	  
	  return true;
  }
}
  
?>