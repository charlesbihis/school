<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/studentmanager.class.php' );
require( '../includes/classes/db/coursemanager.class.php' );
require( '../includes/classes/db/problemmanager.class.php' );
require( '../includes/classes/db/assignstudentmanager.class.php' );

$obj_student_manager = new StudentManager( $obj_user, $obj_db );
$obj_course_manager = new CourseManager( $obj_user, $obj_db );
$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );
$obj_assign_student_manager = new AssignStudentManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];
  
	switch ( $command )
	{
		case 'Create':
		{
			// create a new student
			if ( $obj_student_manager->create_user( $_POST['StudentId'], UP_STUDENT, $_POST['FirstName'], $_POST['LastName'], $_POST['Password'], $_POST['StudentNumber'] ) )
			// TODO: fix the above line, add student number field in UI field and change to $_POST
			{
				MessageHandler::add_message(MSG_SUCCESS, "Student \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" created successfully!" );
			}  // if success
			
			else
			{
				MessageHandler::add_message(MSG_FAIL, "Error creating student \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\"" );
			}  // else failed
		}	

		break;
		  	
		case 'Delete':
		{
			if ( isset( $_POST['UserId'] ) )
			{
				// TODO: check error for delete students
				$arr_student_list = $_POST['UserId'];
			  	
				foreach( $arr_student_list as $str_student_id )
				{
					// FIX: output user first name and last name instead of userid (maybe)
					if( $obj_student_manager->delete_user( $str_student_id ) )
					{
						MessageHandler::add_message(MSG_SUCCESS, "Student \"" . $_POST['UserId'] . "\" deleted successfully!");
					}  // if success

					else
					{
						MessageHandler::add_message(MSG_FAIL, "Error deleting student \"" . $_POST['UserId'] . "\"" );
					}  // else failed
				}
			}
		}

		break;
			
		case 'Assign':
		{     
			if ( isset( $_POST['SelectedStudentId'] ) )
			{
				// TODO: check error for delete problem
				$arr_student_list = $_POST['SelectedStudentId'];
				
				$str_selected_type = $_POST['SelectAssign'];
				$arr_selected_option = split('Td', $str_selected_type );
				$str_selected_option = $arr_selected_option[1];
				
				$str_selected_id = $_POST[$str_selected_option];
				
				foreach ( $arr_student_list as $str_selected_student_id )
				{
					if ( $str_selected_option == 'SelectProblem' )
					{
					  if ( $obj_assign_student_manager->assign_student_to_problem( $str_selected_id, $str_selected_student_id ) )
					  {
						  // TODO: Which error is it?
						  MessageHandler::add_message( MSG_SUCCESS, "Student \"" . $_POST['StudentId'] . "\" successfully assigned to problem" );
					  }  // if successful
  					
					  else
					  {
						  MessageHandler::add_message( MSG_FAIL, "Error assigning student \"" . $_POST['StudentId'] . "\" to problem" );
					  }  // else failed
					}
				
				  if ( $str_selected_option == 'SelectCourse' )
				  {
				      if ( $obj_assign_student_manager->assign_student_to_course( $str_selected_id, $str_selected_student_id ) )
					  {
						  // TODO: Which error is it?
						  MessageHandler::add_message( MSG_SUCCESS, "Student \"" . $_POST['StudentId'] . "\" successfully assigned to course" );
					  }  // if successful
  					
					  else
					  {
						  MessageHandler::add_message( MSG_FAIL, "Error assigning student \"" . $_POST['StudentId'] . "\" to course" );
					  }  // else failed
			  
				  }
				}
			}		
		}
			
		break; 

		case 'Unassign':
		{     
			if ( isset( $_POST['SelectedStudentId'] ) )
			{
				// TODO: check error for delete problem
				$arr_student_list = $_POST['SelectedStudentId'];
				
				$str_selected_type = $_POST['SelectAssign'];
				$arr_selected_option = split('Td', $str_selected_type );
				$str_selected_option = $arr_selected_option[1];
				
				$str_selected_id = $_POST[$str_selected_option];
				
				foreach ( $arr_student_list as $str_selected_student_id )
				{
					if ( $str_selected_option == 'SelectProblem' )
					{
					  if ( $obj_assign_student_manager->unassign_student_to_problem( $str_selected_id, $str_selected_student_id ) )
					  {
						  // TODO: Which error is it?
						  MessageHandler::add_message( MSG_SUCCESS, "Student \"" . $_POST['StudentId'] . "\" successfully unassigned to problem" );
					  }  // if successful
  					
					  else
					  {
						  MessageHandler::add_message( MSG_FAIL, "Error unassigning student \"" . $_POST['StudentId'] . "\" to problem" );
					  }  // else failed
					}
				
				  if ( $str_selected_option == 'SelectCourse' )
				  {
				    // IMPLEMENT THIS HAHAHA				  
				  }
				}
			}		
		}
			
		break; 

		case 'Import':
		{
			// OMG HI I IMPORT LIKE OMG!!
		}

		break;
	}
}

$res_students = $obj_student_manager->view_students();
$res_courses = $obj_course_manager->view_courses();
$res_problems = $obj_problem_manager->view_problems();

$str_page_title = "Manage Students";
$arr_scripts = array( 'managestudent.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";

require ( '../includes/header.inc.php' );

?>

<!-- Start Content -->

<div>

  <form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
          
    <strong>Click on a student to edit student information, and select it for deletion.</strong>
    <br /><br />

    <table class="format" width="100%">
    
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createstudent'; return false;"/>
          &nbsp;<input class="buttoninput" type="submit" value="Import List" name="Command" onclick="xgene360_cu.toggleDisplay('import'); window.location='#importstudents'; return false;"/>
          &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
        </td>
        <td align="right">
          
          <table class="format">
            
            <tr>
              <td>
                <select name="SelectAssign" id="SelectAssign" onchange="xgene360_cu.selectDisplay('SelectAssign', ['TdSelectCourse', 'TdSelectProblem', 'TdSelectNone']);">
                
                  <option selected="selected" value="TdSelectNone">&nbsp;Choose type:&nbsp;&nbsp;&nbsp;&nbsp;</option>
                  <option value="TdSelectNone">&nbsp;----------</option>
                  <option value="TdSelectNone">&nbsp;</option> 
                  <option value="TdSelectCourse">&nbsp;Course</option>
                  <option value="TdSelectProblem">&nbsp;Problem</option>
                
                </select>
                &nbsp;
              </td>
              
              <td id="TdSelectNone">
                <select name="SelectNone" id="SelectNone">
                
                  <option selected="selected" value="">&nbsp;Select type first&nbsp;</option>

                </select>
                &nbsp;
              </td>
              
              <td id="TdSelectCourse" style="display: none;">
                <select name="SelectCourse" id="SelectCourse">
                
                  <?php     
                  
                  echo( '<option selected="selected" value="">&nbsp;Assign to course:&nbsp;&nbsp;&nbsp;&nbsp;</option>' );
                  echo( '<option value="">&nbsp;----------</option>' );
                  echo( '<option value="">&nbsp;</option>' );
                  
                  for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
                  {
                    $res_row2 = $obj_db->fetch( $res_courses );
                    echo( '<option value="'.$res_row2->CourseId.'">&nbsp;&nbsp;&nbsp;&nbsp;'.$res_row2->Name.'</option>'."\n" );
                  }
                  
                  ?>

                </select>
                &nbsp;
              </td>
              
              <td id="TdSelectProblem" style="display: none;">
                <select name="SelectProblem" id="SelectProblem">
          
                  <?php

                  echo( '<option selected="selected">&nbsp;Assign to problem:&nbsp;&nbsp;&nbsp;&nbsp;</option>' );         
                  echo( '<option>&nbsp;----------</option>' );   
                  echo( '<option>&nbsp;</option>' );
                  
                  for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_problems ); ++$i )
                  {
                    $res_row2 = $obj_db->fetch( $res_problems );
                    echo( '<option value="'.$res_row2->problem_id.'">&nbsp;'.$res_row2->problem_name.'&nbsp;</option>'."\n" );
                  }

                  ?>

                </select>
                &nbsp;
              </td>            
            
              <td>
                <input class="buttoninput" type="submit" name="Command" value="Assign" />
                &nbsp;<input class="buttoninput" type="submit" name="Command" value="Unassign" /> 
              </td>
            </tr>
          
          </table>
          

        </td>             
      </tr>
    
    </table>

    <table class="listing" id="listOfStudents">
      
      <tr>
        <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'SelectedStudentId[]' );" /></th>
        <th width="150">Student Number</th>
        <th width="150">Last Name</th>
        <th width="150">First Name</th>
        <th>Username</th>
      </tr>

      <?php
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_students ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_students );
        
        echo( '<tr onclick="openStudentDetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
        echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="SelectedStudentId[]" value="'.$res_row->UserId.'" /></td>' );
        echo( '<td>'.$res_row->StudentNum.'</td>' );
        echo( '<td>'.$res_row->LastName.'</td>' );
        echo( '<td>'.$res_row->FirstName.'</td>' );
        echo( '<td>'.$res_row->UserId.'</td>' );
        echo( '</tr>' );
      }
          
      ?>  
              
    </table>

    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createstudent'; return false;"/>
    &nbsp;<input class="buttoninput" type="submit" value="Import List" name="Command" onclick="xgene360_cu.toggleDisplay('import'); window.location='#importstudents'; return false;"/>
    &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />

    <a name="createstudent"></a>
    <div id="create" style="display: none">

      <br /><br />
      
      <table class="box">

        <tr>
          <th>Create Student</th>
        </tr>
        
        <tr>
          <td>        
            
            <table>
            
              <tr>
                <td width="125">Username:</td>
                <td><input class="textinput" type="text" name="StudentId" id="StudentId" /></td>
              </tr>
            
              <tr>
                <td>First Name:</td>
                <td><input class="textinput" type="text" name="FirstName" id="FirstName" /></td>
              </tr>
            
              <tr>
                <td>Last Name:</td>
                <td><input class="textinput" type="text" name="LastName" id="LastName" /></td>
              </tr>
            
              <tr>
                <td>Student Number:</td>
                <td><input class="textinput" type="text" name="StudentNumber" id="StudentNumber" /></td>
              </tr>
            
              <tr>
                <td>Password:</td>
                <td><input class="textinput" type="password" name="Password" id="Password" /></td>
              </tr>
            
              <tr>
                <td>Confirm Password:</td>
                <td><input class="textinput" type="password" name="ConfirmPassword" id="ConfirmPassword" /></td>
              </tr>          
            
              <tr>
                <td colspan="2" align="right">
                  <input class="buttoninput" type="submit" name="Command" value="Create" onclick="return validateCreateStudentForm();" />
                  &nbsp;<input class="buttoninput" type="reset" name="Reset" value="Reset" onclick="return resetCreateStudentForm();" />
                </td>
              </tr>        
            
            </table>
            
          </td>
        </tr>
      
      </table>

    </div>

    <a name="importstudents"></a>
    <div id="import" style="display: none">

      <br /><br />
      
      <table class="box">
        
        <tr>
          <th>Import Students</th>
        </tr>
        
        <tr>
          <td>
            Upload File [<a href="">Help?</a>]<br />
            <input class="fileinput" type="file" name="file" />
            <br /><input class="buttoninput" type="submit" value="Submit" name="B1" />              
          </td>
        </tr>         
      
      </table>
    
    </div>
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>    
  </form>
  
</div>  

<!-- End Content -->

<?php 

require_once('../includes/footer.inc.php'); 

$obj_db->disconnect();

?>