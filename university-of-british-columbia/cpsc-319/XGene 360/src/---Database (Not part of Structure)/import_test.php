<?php

// for mac compatibility
ini_set("auto_detect_line_endings", "1");

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/studentmanager.class.php' );

$obj_student_manager = new StudentManager( $obj_user, $obj_db );

$showStudentRecords = false;
$showBrowseBox = true;

$numStudentRecords = 0;
$numErrorRecords = 0;

echo "Begin<br>";
if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];
	echo "Command: " . $command . "<br>";

	switch ( $command )
	{
		
		case 'Import':
		{
			echo "Import Begin<br>";
			if (is_uploaded_file($_FILES['theFile']['tmp_name']))
			{
				$lines = file($_FILES['theFile']['tmp_name']);
				echo "Lines: " . $lines . "<br>";
			} else {
				die("Dies<br>"); // death error!!!!!!!!
			}
			
			$studentListArray = null;
			$studentErrorListArray = null;
			
			echo("Being Import<br>");
			importStudents($obj_student_manager, $lines,$studentListArray,$studentErrorListArray);
			$numStudentRecords = count($studentListArray);
			$numErrorRecords = count($studentErrorListArray);
			$showStudentRecords = true;
			$showBrowseBox = false;
		}
		
		break;
  }
}

	function importStudents($obj_student_manager, $p_lineArray, $p_studentListArray, $p_studentErrorListArray)
	{
		echo "importStudent()<br>";

		for ($tempCounter = 0; $tempCounter < count($p_lineArray); $tempCounter++)
		{
   			echo $tempCounter . "aaaaaaaaaa";
   			//$line = fgets($fhandle);
   			$line = $p_lineArray[$tempCounter];
   			list($userId, $firstName,$lastName) = explode(",",$line);

			// check for bad values
			if (empty($userId ) || empty($firstName) || empty($lastName))
			{
				echo " Error1> " . $userId . ":" . $firstName . ":" . $lastName . "<br>";
				$p_studentErrorListArray[] = array($userId,$firstName,$lastName);
			}
			else
			{	
				//echo " Success> " . $userId . ":" . $firstName . ":" . $lastName . "<br>";
				$p_studentListArray[] = array($userId,$firstName,$lastName);
				
				//                function create_user( $str_user_id, $int_user_privilege, $str_first_name, $str_last_name, $str_password, $int_student_num )
				if ( $obj_student_manager->create_user( $userId, UP_STUDENT, $firstName, $lastName, "student", 12345678 ) )
				// TODO: fix the above line, add student number field in UI field and change to $_POST
				{
					echo " Success> " . $userId . ":" . $firstName . ":" . $lastName . "<br>";
					//MessageHandler::add_message(MSG_SUCCESS, "Student \"" . $firstName . " " . $lastName . "\" created successfully!" );
				}  // if success
				
				else
				{
					echo " Error2> " . $userId . ":" . $firstName . ":" . $lastName . "<br>";
					//MessageHandler::add_message(MSG_FAIL, "Error creating student \"" . $firstName . " " . $lastName . "\"" );
				}  // else failed
				
			}
		}

	}

	
$str_page_title = "Import Students";
$arr_scripts = null;
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";


//require ( '../includes/header.inc.php' );

?>

<!-- Start Content -->
<p>Please browse for a CSV file that contain entries for User Id,
First Name, and Last Name on each line (with each entry separated by commas).
<p>
<form action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>" method="post" enctype="multipart/form-data">
<input type="hidden" name="Command" value="Import">
<input type="file" name="theFile" size="50" class="formtextfield">
<br>
<input type="submit" value="Load">
<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
</form>
<!-- end body -->


<!-- End Content -->

<?php 

//require_once('../includes/footer.inc.php'); 
  
$obj_db->disconnect();

?>