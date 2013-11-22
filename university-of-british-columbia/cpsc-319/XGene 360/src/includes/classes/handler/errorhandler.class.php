<?php

$g_arr_error_types = array(

  100 => 'You do not have permission to access this page',
  101 => 'You do not have permission to access this function',
  
  200 => 'Failed to add the course',
  201 => 'Failed to modify the the course',
  202 => 'Failed to delete the course',
  
  300 => 'Failed to add the professor account',
  301 => 'Failed to modify the professor account',
  302 => 'Failed to delete the professor account',
  303 => 'Failed to update the password for the professor',
  
  305 => 'Failed to assign course to the professor',

  400 => 'Failed to add the student account',
  401 => 'Failed to modify the student account',
  402 => 'Failed to delete the student account',

  500 => 'Failed to add the TA account',
  501 => 'Failed to modify the TA account',
  502 => 'Failed to delete the TA account',
  505 => 'Failed to assign course to TA account',
  
  
    
);

$g_arr_error_list = array();

class ErrorHandler
{
	/**
	 * 
	 * add an error to the error list
	 *
	 * @param int $int_error_id
	 */
	function add_error( $int_error_id )
	{
		global $g_arr_error_list;
		
		array_push( $g_arr_error_list, $int_error_id );
	}

	/**
	 * 
	 * check if the user has any error
	 *
	 * @return boolean whether the user has error in the lsit
	 */
	function has_error()
	{
		global $g_arr_error_list;
		
		return ( count( $g_arr_error_list ) > 0 );
	}

	/**
	 * 
	 * return the next error in the list
	 *
	 * @return string the error message
	 */
	function next_error()
	{
		global $g_arr_error_types, $g_arr_error_list;
		
		if ( count( $g_arr_error_list ) > 0 )
		{
		  return $g_arr_error_types[ array_pop( $g_arr_error_list ) ];
		}
		
		return null;
	}
}

?>