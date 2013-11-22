<?php

class GenerationManager
{
	var $m_obj_user = null;
	var $m_obj_db = null;

	/*
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function GenerationManager( $obj_user, $obj_db )
	{
	    $this->m_obj_user = $obj_user;
		$this->m_obj_db = $obj_db;
	}

	function get_number_of_generations( $int_problem_id )
	{
		$str_sql_query = null;
		
		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_ADMINISTRATOR:
			case UP_PROFESSOR:
			case UP_STUDENT:
			
			   $str_sql_query  = "SELECT MAX( P.generation_num ) AS generation_count "
									. "FROM XG_PlantGenerates P "
									. "WHERE P.user_id = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
									. "AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ); 
									
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
	 
	 // function insert all the entire generation
	 // function that gets all the previous stuffie
	function get_generation( $int_problem_id, $int_generation_id ) 
	{
		$str_sql_query = null;

		switch ( $this->m_obj_user->int_privilege )
		{
			case UP_STUDENT:
			
			   $str_sql_query  = "SELECT P.plant_id, P.generation_num, P.value_trait_A, "
			                   . "P.value_trait_B "
			                   . "FROM XG_PlantGenerates P " 
			                   . "WHERE P.user_id = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
			                   . "AND P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
			                   . "AND P.generation_num = " . $this->m_obj_db->format_sql_string( $int_generation_id ) . " "
			                   . "ORDER BY P.generation_num, P.plant_id";
			   
			   break;
			   
		}
	
		if ( $str_sql_query == null )
		{
			return null;
		}
	  
		return $this->m_obj_db->query_select( $str_sql_query );
	}
	
	function set_array_generation( $int_problem_id, $obj_trait_A, $obj_trait_B, $arr_generation, $int_generation_num ) 
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{ 
			case UP_ADMINISTRATOR:
			case UP_PROFESSOR:
			case UP_STUDENT:
				
				$str_sql_query = "INSERT INTO XG_PlantGenerates( user_id, problem_id, generation_num, "
			                      . "value_trait_A, value_trait_B, genotype_trait_A, genotype_trait_B ) "
			                      . "VALUES ";
			                      
			      for( $i = 0; $i < count( $arr_generation ); $i++)
			      {
					    $str_sql_query = $str_sql_query . "( '" 
					      . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "', "
							  . $this->m_obj_db->format_sql_string( $int_problem_id ) . ", "
                . $this->m_obj_db->format_sql_string( $int_generation_num ) . ", "
                . $this->m_obj_db->format_sql_string( $arr_generation[$i]->calculate_trait_A( $obj_trait_A ) ) . ", "
                . $this->m_obj_db->format_sql_string( $arr_generation[$i]->calculate_trait_B( $obj_trait_B ) ) . ", "
                . "'" . $this->m_obj_db->format_sql_string( $arr_generation[$i]->arr_gene[0]->encrypt() ) . "', "
                . "'" . $this->m_obj_db->format_sql_string( $arr_generation[$i]->arr_gene[1]->encrypt() ) . "' ) ";
                                      
                if ( $i != count( $arr_generation ) - 1 )
                {
						      $str_sql_query = $str_sql_query . ", ";
					      }
					  }
          
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
	
	function get_parents_genotypes( $int_problem_id, $arr_parents )
	{
		$str_sql_query = null;
		
		switch ($this->m_obj_user->int_privilege)
		{
			case UP_STUDENT:
			
			$arr_plants_genotype = array();
			
			for( $i = 0; $i < count($arr_parents); $i++ )
			{
			   $str_sql_query  = "SELECT P.genotype_trait_A, P.genotype_trait_B "
			                   . "FROM XG_PlantGenerates P " 
			                   . "WHERE P.plant_id = " . $this->m_obj_db->format_sql_string( $arr_parents[$i] ) . " "
			                   . "AND P.problem_id = ". $this->m_obj_db->format_sql_string( $int_problem_id );
			                   
			   $res_plants = $this->m_obj_db->query_select( $str_sql_query );
			   $res_row = $this->m_obj_db->fetch( $res_plants );
			   $str_genotype_trait_A = $res_row->genotype_trait_A;
			   $str_genotype_trait_B = $res_row->genotype_trait_B;
			   
			   $arr_genotype = array();
			   array_push($arr_genotype, $str_genotype_trait_A);
			   array_push($arr_genotype, $str_genotype_trait_B);
			   
			   array_push($arr_plants_genotype, $arr_genotype);
			}
		}
		
		if ( $str_sql_query == null )
		{
			return null;
		}
		
		return $arr_plants_genotype;
	}

	function set_parents( $int_problem_id, $arr_parents )
	{
		$str_sql_query = null;
	  
		switch ( $this->m_obj_user->int_privilege )
		{			   
		  case UP_STUDENT:
			
			  $str_sql_query = "SELECT MAX(P.generation_num) AS gen_num "
			                 . "FROM XG_PlantGenerates P "
			                 . "WHERE P.problem_id = " . $this->m_obj_db->format_sql_string( $int_problem_id ) . " "
			                 . "AND P.user_id = '" . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "' "
			                 . "GROUP BY P.generation_num ";
			                 
			  $res_gen_num = $this->m_obj_db->query_select( $str_sql_query );
			  $res_row = $this->m_obj_db->fetch( $res_gen_num );
			  $int_generation_num = (int)$res_row->gen_num + 1;

				$str_sql_query = "INSERT INTO XG_PlantParents( plant_id, user_id, problem_id, generation_num ) "
				               . "VALUES ";
			                      
			      for( $i = 0; $i < count( $arr_parents ); $i++)
			      {
					    $str_sql_query = $str_sql_query . "( " 
					  . $this->m_obj_db->format_sql_string( $arr_parents[$i] ) . ", '"
					  . $this->m_obj_db->format_sql_string( $this->m_obj_user->str_username ) . "', "
					  . $this->m_obj_db->format_sql_string( $int_problem_id ) . ", "
                      . $this->m_obj_db->format_sql_string( $int_generation_num ) . ") ";
                                      
				  if ( $i != count( $arr_parents ) - 1 )
				  {
				      $str_sql_query = $str_sql_query . ", ";
				  }
			  }
          
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
}

?>