<?php

class ProblemManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function ProblemManager( $obj_user, $obj_db )
	{
	    $this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function view_problems() 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_STUDENT:
			
				$str_sql_query  = "SELECT P.problem_name, 
										P.problem_id, 
										UNIX_TIMESTAMP(P.start_date) AS start_date, 
										UNIX_TIMESTAMP(P.due_date) AS due_date, 
										C.Name, 
										Gen.iter_val,
										P.max_cross
									FROM XG_ProblemTraitMadeFor P, 
										XG_Assigns A, 
										User U, 
										Course C, 
										(SELECT MAX( G.generation_num ) AS iter_val,
												 G.user_id, 
												 G.problem_id
											FROM XG_PlantGenerates G
											GROUP BY G.problem_id) AS Gen
									WHERE U.UserId = A.student_id 
										AND A.problem_id = P.problem_id 
										AND P.course_id = C.CourseId 
										AND Gen.problem_id = P.problem_id
										AND U.PrivilegeLvl = " . UP_STUDENT . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "';";
				break;
			   
			case UP_TA:
			   
				$str_sql_query  = "SELECT P.problem_name, P.problem_id
									FROM XG_ProblemTraitMadeFor P, XG_Assists A, User U
									WHERE P.problem_id = A.problem_id 
										AND A.ta_id = U.UserId 
										AND U.PrivilegeLvl = " . UP_TA . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "';";
				break;
			   
			case UP_PROFESSOR:
			
			    $str_sql_query  = "SELECT P.problem_name, P.problem_id
									FROM XG_ProblemTraitMadeFor P, User U
									WHERE P.prof_id = U.UserId
										AND U.PrivilegeLvl = " . UP_PROFESSOR . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "';";
										
				break;
							
			case UP_ADMINISTRATOR:

				$str_sql_query = "SELECT P.problem_id, P.problem_name, C.Name, "
							   . "UNIX_TIMESTAMP( P.start_date ) AS start_date, "
							   . "UNIX_TIMESTAMP( P.due_date ) AS due_date, "
							   . "S.student_count "
							   . "FROM Course C, XG_ProblemTraitMadeFor P, "
							   . "( SELECT COUNT( A.student_id ) AS student_count, P.problem_id "
							   . "FROM XG_ProblemTraitMadeFor P LEFT OUTER JOIN XG_Assigns A "
							   . "ON P.problem_id = A.problem_id "
							   . "GROUP BY P.problem_id ) AS S "
							   . "WHERE C.CourseId = P.course_id "
							   . "AND P.problem_id = S.problem_id "
							   . "GROUP BY P.problem_id "
							   . "ORDER BY P.problem_name, C.Name ";
			   break;
		}
	
		if ( $str_sql_query == null )
		{ 
			// TODO: fix up Error Handler or Message Handler
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}


	
	function view_problem_details( $int_problem_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_STUDENT:
			
				$str_sql_query  = "SELECT P.problem_name, P.problem_id AS ProblemId, P.due_date as DueDate, P.max_cross as MaxCross, P.number_of_displayed_plants, 
												P.trait_A_name, P.trait_B_name, P.trait_A_number_of_genes, P.trait_B_number_of_genes, P.trait_A_parent_A_mean, P.trait_A_parent_B_mean,
												P.trait_B_parent_A_mean, P.trait_B_parent_B_mean 
									FROM XG_ProblemTraitMadeFor P, XG_Assigns A, User U
									WHERE P.problem_id = A.problem_id
										AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . "
										AND A.student_id = U.UserId
										AND U.PrivilegeLvl = " . UP_STUDENT . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "';";
			   
			   
			   break;
			   
			case UP_TA:
			   
				$str_sql_query = "SELECT *
									FROM XG_ProblemTraitMadeFor P, XG_Assists A, User U
									WHERE P.problem_id = A.problem_id
										AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " 
										AND A.ta_id = U.UserId 
										AND U.PrivilegeLvl = " . UP_TA . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "';";
			   break;
			   
			case UP_PROFESSOR:
			
				$str_sql_query = "SELECT *
									FROM XG_ProblemTraitMadeFor P, User U
									WHERE P.prof_id = U.UserId
										AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . "
										AND U.PrivilegeLvl = " . UP_PROFESSOR . "
										AND U.UserId = '" . $this->m_obj_db->format_sql_string(  $this->m_obj_user->str_username ) . "';";
				break;
							
			case UP_ADMINISTRATOR:
			   
			    $str_sql_query = "SELECT P.problem_name, P.problem_desc, U.UserId, U.FirstName, " 
			                   . "U.LastName, C.CourseId, C.Name, P.trait_A_name, P.trait_B_name, "
			                   . "P.trait_A_unit, P.trait_B_unit, P.trait_A_number_of_genes, "
			                   . "P.trait_B_number_of_genes, P.trait_A_h2, P.trait_B_h2, P.trait_A_var, "
			                   . "P.trait_B_var, P.trait_A_parent_A_mean, P.trait_A_parent_B_mean, "
			                   . "P.trait_B_parent_A_mean, P.trait_B_parent_B_mean, P.number_of_progeny_per_cross, "
			                   . "P.max_cross, P.number_of_displayed_plants, P.range_of_acceptance, "
			                   . "P.start_date, P.due_date "
			                   . "FROM XG_ProblemTraitMadeFor P, Course C, User U "
			                   . "WHERE P.professor_id = U.UserId "
			                   . "AND C.CourseId = P.course_id "
			                   . "AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id );

				break;
		}
	
		if ( $str_sql_query == null )
		{
			// TODO: fix up Error Handler or Message Handler
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
		
	}
	
	
	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function add_problem( $str_problem_name, $str_problem_desc, $int_course_id, $str_trait_A_name, 
	                      $str_trait_B_name, $str_trait_A_unit, $str_trait_B_unit, 
	                      $int_trait_A_number_of_genes, $int_trait_B_number_of_genes, $dbl_trait_A_h2,
	                      $dbl_trait_B_h2, $dbl_trait_A_var, $dbl_trait_B_var, $dbl_trait_A_parent_A_mean,
	                      $dbl_trait_A_parent_B_mean, $dbl_trait_B_parent_A_mean, $dbl_trait_B_parent_B_mean,
	                      $int_number_of_progeny_per_cross, $int_max_cross, $int_number_of_displayed_plants,
	                      $dbl_range_of_acceptance, $dat_start_date, $dat_due_date )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			// allow admin create? some queries elsewhere verifies user class is a prof in queries
			
				$str_sql_query = "INSERT INTO XG_ProblemTraitMadeFor ( problem_name, problem_desc, professor_id, " 
							   . "course_id, trait_A_name, trait_B_name, trait_A_unit, trait_B_unit, "
							   . "trait_A_number_of_genes, trait_B_number_of_genes, trait_A_h2, trait_B_h2, "
							   . "trait_A_var, trait_B_var, trait_A_parent_A_mean, trait_A_parent_B_mean, "
							   . "trait_B_parent_A_mean, trait_B_parent_B_mean, number_of_progeny_per_cross, "
							   . "max_cross, number_of_displayed_plants, range_of_acceptance, start_date, due_date ) "
							   . "VALUES ('" . $this->m_obj_db->format_sql_string( $str_problem_name ) . "', '"
							   . $this->m_obj_db->format_sql_string( $str_problem_desc ) . "', '"
							   . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "', "
							   . $this->m_obj_db->format_sql_string( $int_course_id ) . ", '"
							   . $this->m_obj_db->format_sql_string( $str_trait_A_name ) . "', '"
							   . $this->m_obj_db->format_sql_string( $str_trait_B_name ) . "', '"
							   . $this->m_obj_db->format_sql_string( $str_trait_A_unit ) . "', '"
							   . $this->m_obj_db->format_sql_string( $str_trait_B_unit ) . "', "
							   . $this->m_obj_db->format_sql_string( $int_trait_A_number_of_genes ) . ", "
							   . $this->m_obj_db->format_sql_string( $int_trait_B_number_of_genes ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_A_h2 ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_B_h2 ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_A_var ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_B_var ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_A_parent_A_mean ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_A_parent_B_mean ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_B_parent_A_mean ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_trait_B_parent_B_mean ) . ", "
							   . $this->m_obj_db->format_sql_string( $int_number_of_progeny_per_cross ) . ", "
							   . $this->m_obj_db->format_sql_string( $int_max_cross ) . ", "
							   . $this->m_obj_db->format_sql_string( $int_number_of_displayed_plants ) . ", "
							   . $this->m_obj_db->format_sql_string( $dbl_range_of_acceptance ) . ", '"
							   . $this->m_obj_db->format_sql_string( $dat_start_date ) . "', '"
							   . $this->m_obj_db->format_sql_string( $dat_due_date ) . "'); ";

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
			ErrorHandler::add_error( 200 );
		  
			return false;
		}

		$int_trait_A_number_of_genes = (int)$int_trait_A_number_of_genes;
		$int_trait_B_number_of_genes = (int)$int_trait_B_number_of_genes;
		$dbl_trait_A_parent_A_mean = (double)$dbl_trait_A_parent_A_mean;
		$dbl_trait_A_parent_B_mean = (double)$dbl_trait_A_parent_B_mean;
		$dbl_trait_B_parent_A_mean = (double)$dbl_trait_B_parent_A_mean;
		$dbl_trait_B_parent_B_mean = (double)$dbl_trait_B_parent_B_mean;
		$int_number_of_progeny_per_cross = (int)$int_number_of_progeny_per_cross;


		// create the initial plants
		$obj_trait_A = $this->create_trait( $str_trait_A_name, $int_trait_A_number_of_genes, $dbl_trait_A_parent_A_mean, $dbl_trait_A_parent_B_mean );
		$obj_trait_B = $this->create_trait( $str_trait_B_name, $int_trait_B_number_of_genes, $dbl_trait_B_parent_A_mean, $dbl_trait_B_parent_B_mean );

		$bln_stronger_gene_A = ( $dbl_trait_A_parent_A_mean > $dbl_trait_A_parent_B_mean );
		$bln_stronger_gene_B = ( $dbl_trait_B_parent_A_mean > $dbl_trait_B_parent_B_mean );

		$obj_plant_A = new Plant;
		$obj_plant_A->create( $int_trait_A_number_of_genes, $bln_stronger_gene_A, $int_trait_B_number_of_genes, $bln_stronger_gene_B );
		$obj_plant_B = new Plant;
		$obj_plant_B->create( $int_trait_A_number_of_genes, !$bln_stronger_gene_A, $int_trait_B_number_of_genes, !$bln_stronger_gene_B );

		// create F1 generation
		$arr_new_generation = Simulation::cross_plants( array( $obj_plant_A, $obj_plant_B ), $int_number_of_progeny_per_cross );

		// create F2 generation
		$arr_new_generation = Simulation::cross_plants( array( $arr_new_generation[0] ), $int_number_of_progeny_per_cross );

		$obj_generation_manager = new GenerationManager( $this->m_obj_user, $this->m_obj_db );

		$int_problem_id = $this->m_obj_db->get_last_inserted_id();

		if ( !$obj_generation_manager->set_array_generation( $int_problem_id, $obj_trait_A, $obj_trait_B, $arr_new_generation, 0 ) )
		{
			MessageHandler::add_message( MSG_ERROR, "Problem has been added correctly; however, the system failed to create the initial plants" );
		    
			return false;
		}

		return true;
	}

	function create_trait( $str_name, $int_number_of_genes, $dbl_parent_A_mean, $dbl_parent_B_mean )
	{
		// create the trait
		$obj_trait = new Trait;
		$obj_trait->create( $str_name, $int_number_of_genes, min( $dbl_parent_A_mean, $dbl_parent_B_mean ), max( $dbl_parent_A_mean, $dbl_parent_B_mean ) );
		
		return $obj_trait;
	}
	
	function view_problem_displayed_plants( $int_problem_id )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "SELECT P.number_of_displayed_plants " 
							   . "FROM XG_ProblemTraitMadeFor P"
							   . "WHERE P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id );

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
	function delete_problem( $int_problem_id ) {
		 $str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
			case UP_PROFESSOR:
			
				$str_sql_query = "SELECT COUNT(*) AS num FROM User U, XG_ProblemTraitMadeFor P WHERE U.UserId = P.prof_id AND P.problem_id = ". $this->m_obj_db->format_sql_string( $int_problem_id );
			
				$res = $this->m_obj_db->query_select( $str_sql_query );
				
				if ( $obj_db->get_number_of_rows( $res ) == 1 )
				{
					$res_row = $obj_db->fetch( $res );
					if ($res_row->num <= 1) // in case something went wrong and there is no association
					{					
						return false;
					}
				}
			
			// continue to delete problem if the problem DOES belong to that prof
			
			case UP_ADMINISTRATOR:
			
				$str_sql_query = "DELETE FROM XG_ProblemTraitMadeFor "
							   . "WHERE problem_id = ". $this->m_obj_db->format_sql_string( $int_problem_id );
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
			
			ErrorHandler::add_error( 202 );
			
			return false;
		}
		
		// ------------------------------------------------
		// need to clean associated database relations here		
		// ------------------------------------------------
		
		return true;
		
	}
	
	function modify_problem( $int_problem_id, $str_problem_name, $str_problem_description, 
							 $str_trait_A_name, $str_trait_B_name, $str_trait_A_unit, 
	                         $str_trait_B_unit, $int_trait_A_number_of_genes, $int_trait_B_number_of_genes, 
	                         $dbl_trait_A_h2, $dbl_trait_B_h2, $dbl_trait_A_var, $dbl_trait_B_var, $dbl_trait_A_parent_A_mean, 
	                         $dbl_trait_A_parent_B_mean, $dbl_trait_B_parent_A_mean, $dbl_trait_B_parent_B_mean,
	                         $int_number_of_progeny_per_cross, $int_max_cross, $int_number_of_displayed_plants,
	                         $dbl_range_of_acceptance, $dat_start_date, $dat_due_date )
	{
	  $str_sql_query = null;
	  
	  switch ( $this->m_obj_user->int_privilege )
	  {				   
			case UP_PROFESSOR:
			case UP_ADMINISTRATOR:
  			
				$str_sql_query = "UPDATE XG_ProblemTraitMadeFor " 
							   . "SET problem_name = '" . $this->m_obj_db->format_sql_string( $str_problem_name ) . "', "
							   . "problem_desc = '" . $this->m_obj_db->format_sql_string( $str_problem_description ) . "', '"
							   . "trait_A_name = '" . $this->m_obj_db->format_sql_string( $str_trait_A_name ) . "', "
							   . "trait_B_name = '" . $this->m_obj_db->format_sql_string( $str_trait_B_name ) . "', "
							   . "trait_A_unit = '" . $this->m_obj_db->format_sql_string( $str_trait_A_unit ) . "', "
							   . "trait_B_unit = '" . $this->m_obj_db->format_sql_string( $str_trait_B_unit ) . "', "
							   . "trait_A_number_of_genes = " . $this->m_obj_db->format_sql_string( $int_trait_A_number_of_genes ) . ", "
							   . "trait_B_number_of_genes = " . $this->m_obj_db->format_sql_string( $int_trait_B_number_of_genes ) . ", "
							   . "trait_A_h2 = " . $this->m_obj_db->format_sql_string( $dbl_trait_A_h2 ) . ", "
							   . "trait_B_h2 = " . $this->m_obj_db->format_sql_string( $dbl_trait_B_h2 ) . ", "
							   . "trait_A_var = " . $this->m_obj_db->format_sql_string( $dbl_trait_A_var ) . ", "
							   . "trait_B_var = " . $this->m_obj_db->format_sql_string( $dbl_trait_B_var ) . ", "
							   . "trait_A_parent_A_mean = " . $this->m_obj_db->format_sql_string( $dbl_trait_A_parent_A_mean ) . ", "
							   . "trait_A_parent_B_mean = " . $this->m_obj_db->format_sql_string( $dbl_trait_A_parent_B_mean ) . ", "
							   . "trait_B_parent_A_mean = " . $this->m_obj_db->format_sql_string( $dbl_trait_B_parent_A_mean ) . ", "
							   . "trait_B_parent_B_mean = " . $this->m_obj_db->format_sql_string( $dbl_trait_B_parent_B_mean ) . ", "
							   . "number_of_progeny_per_cross = " . $this->m_obj_db->format_sql_string( $int_number_of_progeny_per_cross ) . ", "
							   . "max_cross = " . $this->m_obj_db->format_sql_string( $int_max_cross ) . ", "
							   . "number_of_displayed_plants = " . $this->m_obj_db->format_sql_string( $int_number_of_displayed_plants ) . ", "
							   . "range_of_acceptance = " . $this->m_obj_db->format_sql_string( $dbl_range_of_acceptance ) . ", "
							   . "start_date = '" . $this->m_obj_db->format_sql_string( $dat_start_date ) . "', "
							   . "due_date = '" . $this->m_obj_db->format_sql_string( $dat_due_date ) . "' "
							   . "WHERE problem_id = " . $this->m_obj_db->format_sql_string(  $int_problem_id );
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

			ErrorHandler::add_error( 101 );
		  
			return false;
		}
	  
	  return true;

	}
}

?>