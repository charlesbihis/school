<?php

class AssignStudentManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function AssignStudentManager( $obj_user, $obj_db )
	{
	  	$this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	function view_assigned_problems() 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT P.problem_id, P.problem_name "
							   . "FROM XG_ProblemTraitMadeFor P, XG_Assigns A, User U "							   . "WHERE A.problem_id = P.problem_id "
							   . "AND A.student_id = U.UserId "
							   . "AND U.UserId = '". $this->m_obj_db->format_sql_string( $this->m_obj_user->$str_username ) . "'";
			   break;
		}
	
		if ( $str_sql_query == null )
		{
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
 
	function assign_student_to_problem( $str_student_id, $int_problem_id )
	{
		$str_sql_query = null;

		// assign the problem	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "INSERT INTO XG_Assigns(problem_id, student_id) "
				               . "VALUES ( " . $this->m_obj_db->format_sql_string( $int_problem_id ) . ", '"
				               . $this->m_obj_db->format_sql_string( $str_student_id ) . "') ";
				
				// FIX: is this error message redundant? (see line 117)
				if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
				{
					MessageHandler::add_message( MSG_FAIL, "Error assigning student to problem" );
				  
					return false;
				}  // if failed
				else
				{
					MessageHandler::add_message( MSG_SUCCESS, "Student successfully assigned to problem!" ); 
				}  // else success
				
				$str_sql_query = "SELECT P.plant_id, Problem.number_of_displayed_plants, "
				               . "P.value_trait_A, P.value_trait_B, P.genotype_trait_A, "
				               . "P.genotype_trait_B "
				               . "FROM XG_PlantGenerates P, XG_ProblemTraitMadeFor Problem "
				               . "WHERE P.generation_num = 0 "
				               . "AND P.problem_id = Problem.problem_id "
				               . "AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " ";
				               
				$res_plants = $this->m_obj_db->query_select( $str_sql_query ); 
				$arr_initial_plants = array();
				
				for ( $i = 0; $i < $this->m_obj_db->get_number_of_rows( $res_plants ); ++$i )
				{
					$res_row = $this->m_obj_db->fetch( $res_plants );
					array_push( $arr_initial_plants, $res_row );
				}

			    $str_sql_query = "INSERT INTO XG_PlantGenerates( user_id, problem_id, generation_num, "
			                   . "value_trait_A, value_trait_B, genotype_trait_A, genotype_trait_B ) VALUES ";
			                    
			    $int_number_of_displayed_plants = $arr_initial_plants[0]->number_of_displayed_plants;
				
				for ( $i = 0; $i < $int_number_of_displayed_plants; ++$i ) 
				{
					$obj_selected_row = $arr_initial_plants[rand( 0, count( $arr_initial_plants ) - 1 )];

					$str_sql_query = $str_sql_query . "( '"  
			                       . $this->m_obj_db->format_sql_string( $str_student_id ) . "', "
			                       . $this->m_obj_db->format_sql_string( $int_problem_id ) . ", 1, "
			                       . $this->m_obj_db->format_sql_string( $obj_selected_row->value_trait_A ) . ", "
			                       . $this->m_obj_db->format_sql_string( $obj_selected_row->value_trait_B ) . ", '"
			                       . $this->m_obj_db->format_sql_string( $obj_selected_row->genotype_trait_A ) . "', '"
			                       . $this->m_obj_db->format_sql_string( $obj_selected_row->genotype_trait_B ) . "') ";
			                       
					if ( $i != $int_number_of_displayed_plants - 1 )
					{
					     $str_sql_query = $str_sql_query . ", ";
				    }
				}
		
				break;
		}
	
		if ( $str_sql_query == null )
		{
			MessageHandler::add_message( MSG_FAIL, "Error assigning student to problem" );
	    
			return false;
		}

		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Student successfully assigned to problem" );
		  
			return false;
		}

	  return true;
	}
	
	function unassign_student_from_problem( $str_student_id, $int_problem_id ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "DELETE FROM XG_Assigns "
				               . "WHERE problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
				               . "AND student_id = '" . $this->m_obj_db->format_sql_string( $str_student_id ) . "'";
				
				// FIX: is this error message redundant? (see line 160)
				if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
				{
					MessageHandler::add_message( MSG_FAIL, "Error removing student from problem" );
					
					return false;
				}
								
				$str_sql_query = "DELETE FROM XG_PlantGenerates "
				               . "WHERE problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
				               . "AND user_id = '" . $this->m_obj_db->format_sql_string( $str_student_id ) . "'";
			   break;
		}
		
		if ( $str_sql_query == null )
		{
		  MessageHandler::add_message( MSG_FAIL, "Error removing student from problem" );
		  
		  return false;
		}
		
		if ( !$this->m_obj_db->query_commit( $str_sql_query ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Student successfully removed from problem" );
			
			return false;
		}

		return true;
	}
}

?>