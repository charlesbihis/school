<?php

class Admin_CreateProblem
{
	$user_class;

	/**
	 * Class Constructor
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function Admin_CreateProblem($user_class) {
		$GLOBALS['user_class'] = $user_class;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function createProblem() {
		global $user_class;

		switch ($user_class) {
			case UP_STUDENT:
			   break;
			case UP_TA:
			   break;
			case UP_PROFESSOR:
				break;
			case UP_ADMINISTRATOR:
			   break;
			default:
			   break;
		}
	
		return NULL; // return SOMETHING here
	}
	
}

?>