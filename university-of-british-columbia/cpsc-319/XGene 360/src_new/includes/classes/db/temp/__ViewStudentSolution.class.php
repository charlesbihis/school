<?php

class Admin_ViewStudentSolution
{
	$user_class;

	/**
	 * Class Constructor
	 * PRE: $user_class is a valid user class enumerated in the id in the User table
	 * POST: TA object is constructed
	 * @param string $p_userId
	 */
	function Admin_ViewStudentSolution($user_class) {
		$GLOBALS['user_class'] = $user_class;
	}

	/* Function Description
	 * PRE: 
	 * POST: 
	 * @param 
	 */
	function viewStudentSolution() {
		global $user_class;

		switch ($user_class) {
			case UP_STUDENT:
				$sql_query = "";
				break;
			case UP_TA:
				$sql_query = "";
				break;
			case UP_PROFESSOR:
				$sql_query = "";
				break;
			case UP_ADMINISTRATOR:
				$sql_query = "";
				break;			   
			default:
				$sql_query = "";
				break;
		}
	
		return $user_class->querySelect($sql_query);
	}

}

?>