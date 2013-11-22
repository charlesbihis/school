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

require( '../includes/classes/db/problemmanager.class.php' );
require( '../includes/classes/db/assignproblemmanager.class.php' );

$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );
$obj_assign_problem_manager = new AssignProblemManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] )  && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];
  
	switch ( $command )
	{
		case 'Create':
		{
			// FIX: never called! (same case used in manageprofessors.php)
			if ( $obj_problem_manager->create_user( $_POST['UserId'], UP_PROFESSOR,  $_POST['FirstName'], $_POST['LastName'], $_POST['Password'], 0 ) )
			{
				MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" created successfully!" );
			}  // if success
			else
			{
				MessageHandler::add_message( MSG_SUCCESS, "Error creating professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\"");
			}  // else failed
		
			break;
		}  // case 'Create'
		
		case 'Delete':
		{
			// ErrorHandler::add_error( );
			if ( isset( $_POST['ProblemId'] ) )
			{
				// TODO: check error for delete problem
				$arr_problem_list = $_POST['ProblemId'];
	        
				foreach( $arr_problem_list as $str_problem_id )
				{
					// FIX: output problem name instead of problem id
					if ( $obj_problem_manager->delete_problem( $str_problem_id ) )
					{
						MessageHandler::add_message( MSG_SUCCESS, "Problem \"" . $_POST['ProblemId'] . "\" deleted successfully!" );
					}  // if success
					else
					{
						MessageHandler::add_message( MSG_FAIL, "Error deleting problem \"" . $_POST['ProblemId'] . "\"" );
					}  // else failed
				}
			}
		}
    
		break;
    
		case 'Assign':
		{
			if ( isset( $_POST['ProblemId'] ) )
			{
				// TODO: check error for delete problem
				$arr_problem_list = $_POST['ProblemId'];
        
				foreach( $arr_problem_list as $str_problem_id )
				{
					// FIX: output course name instead of course id
					if ( $obj_assign_problem_manager->assign_problem_to_course( $str_problem_id, $_POST['selectedCourse'] ) )
					{
						//MessageHandler::add_message( MSG_SUCCESS, "Selected problems successfully assigned to course \"" . $_POST['selectedCourse'] . "\"!" );
						MessageHandler::add_message( MSG_SUCCESS, "Selected problems successfully assigned to course!" );
					}  // if success
					else
					{
						//MessageHandler::add_message( MSG_FAIL, "Error assigning selected problems to course \"" . $_POST['selectedCourse'] . "\"" );
						MessageHandler::add_message( MSG_FAIL, "Error assigning selected problems to course" );
					}  // else failed
				}
			}		
		}
		break;
  }
}

$res_problems = $obj_problem_manager->view_problems();

$str_page_title = "Manage Problems";
$arr_scripts = array( 'manageproblems.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];

require ( '../includes/header.inc.php' );

?>


        <!-- Start Content -->
        
<div>
<form method="post" action="manageproblems.php">
        Click on a problem to edit problem information, and select it for deletion.
        <br /><br />     
        
        <table class="format" width="100%">
          <tr>
            <td>
              <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="window.location='createproblem.php'; return false;"/>       
              &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
            </td>
            <td align="right">
              <select size="1" name="selectedCourse">
              
              <?php
                
                echo( '<option selected="selected">Assign selected to course:</option>' );         
                echo( '<option>----------</option>' );   
                echo( '<option>&nbsp;</option>' );
                require( '../includes/classes/db/CourseManager.class.php' );
                $obj_course_manager = new CourseManager( $obj_user, $obj_db );
                $res_courses = $obj_course_manager->view_courses();
                
                for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
                {
                  $res_row2 = $obj_db->fetch( $res_courses );
                  echo( '<option value="'.$res_row2->CourseId.'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.$res_row2->Name.'</option>'."\n" );
                }
              
              ?>
              
	            <!-- option value="course_id">COURSE NAME</option -->
	            </select>
	            &nbsp;<input align="right" class="buttoninput" type="submit" value="Assign" name="Command" />            
            </td>             
          </tr>
        </table>     
        
        <table class="listing">
          <tr>
            <th width="50"><input type="checkbox" id="ProblemIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProblemId[]' );" /></th>
            <th width="250">Problem</th>
            <th width="125">Course</th>
            <th width="125">Start Date</th>
            <th width="125">Due Date</th>
            <th># Students (submitted/total)</th>
          </tr>
          
         <?php
          
              for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_problems ); ++$i )
              {
                $res_row = $obj_db->fetch( $res_problems );
                
                $arr_start_date = preg_split( "/\s{3}/", $res_row->start_date );
                $arr_due_date = preg_split( "/\s{3}/", $res_row->due_date );
               
                echo( '<tr onclick="openProblemDetail( \''.$res_row->problem_id.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
                echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="ProblemId[]" value="'.$res_row->problem_id.'" /></td>'."\n" );
                echo( '<td>'.$res_row->problem_name.'</td>'."\n" );
                echo( '<td>'.$res_row->Name.'</td>'."\n" );
                echo( '<td>'.join('<br />', $arr_start_date).'</td>'."\n" );
                echo( '<td>'.join('<br />', $arr_due_date).'</td>'."\n" );
                echo( '<td>'.$res_row->submit_count.'/'.$res_row->student_count.' &nbsp;<input class="buttoninput" type="button" value="View Submitted" onclick="xgene360_cu.stopPropagation( event ); window.location=\'viewsolutions.php?problemid='.$res_row->problem_id.'\';" /></td>'."\n" ); // submit count error?
                echo( '</tr>'."\n" );
              }
              
          ?>
                 
        </table>
        
        <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="window.location='createproblem.php'; return false;"/>
        &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />  
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>    
</form>
</div>

        <!-- End Content -->

<?php 

require_once('../includes/footer.inc.php'); 

?>