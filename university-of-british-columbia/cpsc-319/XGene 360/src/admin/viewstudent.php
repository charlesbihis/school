<?php 

require_once( '../includes/global.inc.php' ); 

if ( !isset( $_GET['studentid'] ) )
{
  PageHandler::redirect( './managestudents.php' );
}

$int_student_id = $_GET['studentid'];

$obj_db = new DBManager();
$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

require( '../includes/classes/db/studentmanager.class.php' );

$obj_student_manager = new StudentManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
  {
    case 'Update':
    {
		if ( $obj_student_manager->modify_user( $int_student_id, $_POST['StudentFirstName'], $_POST['StudentLastName'], $_POST['StudentNumber'] ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Student \"" . $_POST['StudentFirstName'] . " " . $_POST['StudentLastName'] . "\" updated successfully!" );
		}  // if success
		else
		{
			MessageHandler::add_message( MSG_FAIL, "Error updating student \"" . $_POST['StudentFirstName'] . " " . $_POST['StudentLastName'] . "\"" );
		}  // else failed
      
		if ( strlen( $_POST['StudentPassword'] ) != 0 )
		{
			if ( $obj_student_manager->modify_password( $int_student_id, $_POST['StudentPassword'] ) )
			{
				MessageHandler::add_message( MSG_SUCCESS, "Password changed!" );
			}  // if success
			else
			{
				MessageHandler::add_message( MSG_FAIL, "Error changing password" );
			}  // else failed
		}
    }
    
    break;
  }
}

$res_user = $obj_student_manager->view_user( $int_student_id );

$bln_invalidCourse = false;

if ( $obj_db->get_number_of_rows( $res_user ) == 0 )
{
  // TODO: add error handler here
  $bln_invalidProfessor = true;
}

else
{
  $arr_student_info = $obj_db->fetch( $res_user );
}

$str_page_title = "View Student";
$arr_scripts = array( 'managestudent.js' );
$arr_nav_links = $g_arr_nav_links[UP_ADMINISTRATOR];

require_once( '../includes/header.inc.php' );
?>

<!-- START CONTENT -->

<div>

  <form method="POST" action="">

  <b>Modify Student</b>

  <table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse">
    <tr>
      <td>First Name&nbsp;</td>
      <td> <input type="text" name="StudentFirstName" size="30" value="<?php if ( isset( $arr_student_info ) ) { echo( $arr_student_info->FirstName ); } ?>" /></td>
    </tr>
    <tr>
      <td>Last Name&nbsp;</td>
      <td> <input type="text" name="StudentLastName" size="30" value="<?php if ( isset( $arr_student_info ) ) { echo( $arr_student_info->LastName ); } ?>" /></td>
    </tr>
    <tr>
      <td>Student Number&nbsp;</td>
      <td> <input type="text" name="StudentNumber" size="30" value="<?php if ( isset( $arr_student_info ) ) { echo( $arr_student_info->StudentNum ); } ?>" /></td>
    </tr>
    <tr>
      <td>Password&nbsp;</td>
      <td> <input type="password" name="StudentPassword" size="30" /></td>
    </tr>
    <tr>
      <td colspan="2">
        <input type="submit" value="Update" name="Command" onclick="return validateUpdateStudentForm();" />
        &nbsp;<input type="reset" value="Reset" name="Command" onclick="return resetUpdateStudentForm();" />
    </tr>
  </table>
  <input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
  </form>

  <hr />
  
  <b>The student has access to the following problems:</b>
  <form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

  <table class="listing" border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse">
    <tr>
      <th><input type="checkbox" id="ProblemIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProblemId[]' );" /></th>
      <th>Problem</th>
      <th>Course</th>
      <th>Start Date</th>
      <th>Due Date</th>
    </tr>
    
    <?php
    
      $res_problems = $obj_student_manager->view_student_problems( $int_student_id );
      
      if ( $obj_db->get_number_of_rows( $res_problems ) == 0 )
      {
        echo( '<tr>'."\n" );
        echo( '<td colspan="3">This student does not have any problem assigned</td>'."\n" );
        echo( '</tr>'."\n" );
      }
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_problems ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_problems );
        
        echo( '<tr onclick="openProblemDetail( \''.$res_row->problem_id.'\' );" onmouseover="xgene360_cu.useHandCursor( this );" onmouseout="xgene360_cu.useRegularCursor( this );">'."\n" );
        echo( '<td><input type="checkbox" name="ProblemId[]" value="'.$res_row->problem_id.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
        echo( '<td>'.$res_row->problem_name.'</td><td>'.$res_row->Name.'</td><td>'.$res_row->start_date.'</td><td>'.$res_row->due_date."\n" );
        echo( '</tr>'."\n" );
      }
      
    ?>
    
  </table>
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
  </form>

</div>

<!-- END CONTENT -->

<?php require_once('../includes/footer.inc.php'); ?>
