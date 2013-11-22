<?php

require_once( '../includes/global.inc.php' ); 

if ( !isset( $_GET['professorid'] ) )
{
  PageHandler::redirect( './manageprofessors.php' );
}

$str_professor_id = $_GET['professorid'];

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/professormanager.class.php' );
require( '../includes/classes/db/coursemanager.class.php' );
require( '../includes/classes/db/assignprofessormanager.class.php' );

$obj_professor_manager = new professormanager( $obj_user, $obj_db );
$obj_course_manager = new coursemanager( $obj_user, $obj_db );
$obj_assign_professor_manager = new assignprofessormanager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];

	switch ( $command )
	{
		case 'Update':
		{
			if ( $obj_professor_manager->modify_user( $str_professor_id, $_POST['ProfessorFirstName'], $_POST['ProfessorLastName'], 0 ) )
			{
				MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $_POST['ProfessorFirstName'] . " " . $_POST['ProfessorLastName'] . "\" modified successfully!" );
			}  // if success
			else
			{
				MessageHandler::add_message( MSG_FAIL, "Error modifying professor \"" . $_POST['ProfessorFirstName'] . " " . $_POST['ProfessorLastName'] . "\"" );
			}  // else failed 

			if ( strlen( $_POST['NewProfessorPassword'] ) != 0 )
			{
				if ( $obj_professor_manager->modify_password( $str_professor_id, $_POST['NewProfessorPassword'] ) )
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
    
    case 'Assign':
    {
		if ( $obj_assign_professor_manager->assign_professor( $str_professor_id, $_POST['SelectCourse'] ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $str_professor_id . "\" successfully assigned to course!" );
		}  // if success
		else
		{
			MessageHandler::add_message( MSG_FAIL, "Error assigning professor \"" . $str_professor_id . "\" to course" );
		}  // else failed
    }  // case 'Assign'

    break;
    
    case 'Remove':
    {
      if ( isset( $_POST['CourseId'] ) )
      {
        // TODO: check error for delete professor
        $arr_course_list = $_POST['CourseId'];
        $count = 0;
        
        foreach( $arr_course_list as $int_course_id )
        {
			    if ( $obj_assign_professor_manager->unassign_professor( $str_professor_id, $int_course_id ) )
			    {
				    //MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $str_professor_id . "\" successfully removed from selected course!" );
				    $count++;
			    }  // if success
			    else
			    {
				    MessageHandler::add_message( MSG_FAIL, "Error removing professor \"" . $str_professor_id . "\" from course \"" . $int_course_id . "\"" );
			    }  // else failed
        }
        
        if ( $count == 1 )
			MessageHandler::add_message(MSG_SUCCESS, "Professor \"" . $str_professor_id . "\" successfully removed from selected course!" );
		else
			MessageHandler::add_message(MSG_SUCCESS, "Professor \"" . $str_professor_id . "\" successfully removed from " . $count . " courses!" );
      }
    }
	  
    break;
  }
}

$res_user = $obj_professor_manager->view_user( $str_professor_id );
$res_courses = $obj_course_manager->view_courses();
$res_professor_courses = $obj_professor_manager->view_professor_courses( $str_professor_id );

$bln_invalidCourse = false;

if ( $obj_db->get_number_of_rows( $res_user ) == 0 )
{
  // TODO: add error handler here
  $bln_invalidProfessor = true;
}

else
{
  $arr_professor_info = $obj_db->fetch( $res_user );
}

$str_page_title = "View Professor";
$arr_scripts = array( 'manageprofessors.js' );
$arr_nav_links = $g_arr_nav_links[UP_ADMINISTRATOR];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

?>

<!-- Start Content -->
<div>

  <form method="post" id="UpdateProfessorForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <input class="buttoninput" type="button" value="Back to Professor Listing" onclick="window.location='manageprofessors.php';" />
    <br /><br /><br />

    <table class="box">

      <tr>
        <th>Modify Professor</th>
      </tr>  
      
      <tr>
        <td>
      
          <table>
            
            <tr>
              <td width="150">First Name:</td>
              <td><input class="textinput" type="text" name="ProfessorFirstName" value="<?php if ( isset( $arr_professor_info ) ) { echo( $arr_professor_info->FirstName ); } ?>" /></td>
            </tr>
             
            <tr>
              <td>Last Name:</td>
              <td><input class="textinput" type="text" name="ProfessorLastName" value="<?php if ( isset( $arr_professor_info ) ) { echo( $arr_professor_info->LastName ); } ?>"/></td>
            </tr>
            
            <tr>
              <td>New Password:</td>
              <td><input class="textinput" type="password" name="NewProfessorPassword" id="NewProfessorPassword" /></td>
            </tr>
            
            <tr>
              <td>Confirm New Password:&nbsp;</td>
              <td><input class="textinput" type="password" name="NewProfessorPasswordConfirm" id="NewProfessorPasswordConfirm" /></td>
            </tr>          
            
            <tr>
              <td colspan="2" align="right">
                <input class="buttoninput" type="submit" name="Command" value="Update" onclick="return validateUpdateProfessorForm();" />
                &nbsp;<input class="buttoninput" type="reset" name="Command" value="Reset" onclick="return resetUpdateProfessorForm();" />
              </td>
            </tr>        
          
          </table> 

        </td>
      </tr>

    </table>
    
    <br /><br />
    
    <table class="format" width="100%">
      
      <tr>
        <td>
          <strong>The professor has access to the following courses:</strong>
        </td>
      
        <td align="right">
        
          <select name="SelectCourse" id="SelectCourse">
        
            <?php
            
            echo( '<option selected="selected">&nbsp;Select a course:&nbsp;&nbsp;</option>' );         
            echo( '<option>&nbsp;----------</option>' );   
            echo( '<option>&nbsp;</option>' );

            for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
            {
              $res_row2 = $obj_db->fetch( $res_courses );
              echo( '<option value="'.$res_row2->CourseId.'">&nbsp;'.$res_row2->Name.'&nbsp;</option>'."\n" );
            }
            
            ?>
         
	        </select>
         
          &nbsp;<input class="buttoninput" type="submit" value="Assign" name="Command" onclick="return onAssignAProfessorToACourseButtonClickHandler( 'SelectCourse' );" />
          &nbsp;<input class="buttoninput" type="submit" value="Remove" name="Command" />
        </td>             
      </tr>
    
    </table>   
    
    <table class="listing" id="listofCourses">
      
      <tr>
        <th width="50"><input type="checkbox" id="CourseIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'CourseId[]' );" /></th>
        <th width="150">Course Name</th>
        <th>Course Description</th>
      </tr>
      
      <?php

      if ( $obj_db->get_number_of_rows( $res_professor_courses ) == 0 )
      {
        echo( '<tr>'."\n" );
        echo( '<td colspan="3">This professor does not have any course assigned</td>'."\n" );
        echo( '</tr>'."\n" );
      }
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_professor_courses ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_professor_courses );
        
        echo( '<tr onclick="openCourseDetail( \''.$res_row->CourseId.'\' );" onmouseover="xgene360_cu.useHandCursor( this );" onmouseout="xgene360_cu.useRegularCursor( this );">'."\n" );
        echo( '<td><input type="checkbox" name="CourseId[]" value="'.$res_row->CourseId.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
        echo( '<td>'.$res_row->Name.'</td>'."\n" );
        echo( '<td>'.$res_row->Description.'</td>'."\n" );
        echo( '</tr>'."\n" );
      }
        
      ?>
      
    </table>

    <br /><br />
    <input class="buttoninput" type="button" value="Back to Professor Listing" onclick="window.location='manageprofessors.php';" />
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
  </form>

</div>

<!-- End Content -->

<?php 

require_once('../includes/footer.inc.php'); 

$obj_db->disconnect();

?>
