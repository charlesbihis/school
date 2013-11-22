<?php

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/problemmanager.class.php' );
require_once( '../includes/classes/db/assignproblemmanager.class.php' );

/*
* initialize common stuff
*/

$g_obj_db = null;
$g_obj_lock = null;
$g_str_serial = null;
$g_obj_user = null;

PageHandler::initialize();
PageHandler::check_permission( array( UP_ADMINISTRATOR, UP_PROFESSOR, UP_TA ) );

$g_obj_course_manager = new CourseManager( $g_obj_user, $g_obj_db );
$g_obj_problem_manager = new ProblemManager( $g_obj_user, $g_obj_db );
$g_obj_assign_problem_manager = new AssignProblemManager( $g_obj_user, $g_obj_db );
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage Problems";
$g_arr_scripts = array( 'manageproblems.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[$g_obj_user->int_privilege];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->
<div>

  <form method="post" action="<?= $_SERVER['REQUEST_URI'] ?>">

    <strong>
      Click on a problem to edit specific problem information. 
      <br />To delete a problem or several problems, click on the checkbox beside each problem to be deleted and press 'Delete Selected Problems'.
    </strong>
    <br /><br />

    <table class="format" width="100%">
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Create New Problem" name="Command" onclick="window.location='createproblem.php'; return false;"/>&nbsp;
          <input class="buttoninput" type="submit" value="Delete Selected Problems" name="Command" />
        </td>
        <td align="right">
          <select name="SelectedCourse" id="SelectedCourse">
              
<?php
  
	echo( '<option selected="selected" value="">&nbsp;Assign selected to course:&nbsp;&nbsp;&nbsp;&nbsp;</option>' );
	echo( '<option value="">&nbsp;----------</option>' );
	echo( '<option value="">&nbsp;</option>' );

	$res_courses = $g_obj_course_manager->view_courses();

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_courses );

		echo( '<option value="' . htmlspecialchars( $res_row->CourseId ) . '">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' . htmlspecialchars( $res_row->Name ) . '</option>'."\n" );
	}

?>

          </select>&nbsp;
          <input align="right" class="buttoninput" type="submit" value="Assign" name="Command" />
        </td>
      </tr>
    </table>

    <table class="listing" id="ListOfProblems">
      <tr>
        <th width="50"><input type="checkbox" id="ProblemIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProblemId[]' );" /></th>
        <th width="250">Problem</th>
        <th width="125">Course</th>
        <th width="125">Start Date</th>
        <th width="125">Due Date</th>
        <th># Students<br />(submitted/total)</th>
      </tr>
          
<?php

	$res_problems = $g_obj_problem_manager->view_problems();

  for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_problems ); ++$i )
  {
    $res_row = $g_obj_db->fetch( $res_problems );
    
    /*
    $arr_start_date = preg_split( "/\s{3}/", $res_row->start_date );
    $arr_due_date = preg_split( "/\s{3}/", $res_row->due_date );
    */
    
    echo( '<tr onclick="openProblemDetail( \'' . htmlspecialchars( $res_row->problem_id, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
    echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="ProblemId[]" value="' . htmlspecialchars( $res_row->problem_id ) . '" /></td>'."\n" );
    echo( '<td>' . htmlspecialchars( $res_row->problem_name ) . '</td>'."\n" );
    echo( '<td>' . htmlspecialchars( $res_row->Name ). '</td>'."\n" );
    echo( '<td>' . htmlspecialchars( PageHandler::format_date( $res_row->start_date ) ) . '</td>'."\n" );
    echo( '<td>' . htmlspecialchars( PageHandler::format_date( $res_row->due_date ) ) . '</td>'."\n" );
    echo( '<td>' . '0' . '/' . htmlspecialchars( $res_row->student_count ) . '</td>' . "\n" );
    echo( '</tr>' . "\n" );
  }
  
?>
                 
    </table>
    
    <input class="buttoninput" type="submit" value="Create New Problem" name="Command" onclick="window.location='createproblem.php'; return false;"/>&nbsp;
    <input class="buttoninput" type="submit" value="Delete Selected Problems" name="Command" />
    <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>"/>

  </form>

</div>
<!-- End Content -->

<?php 
}

require_once('../includes/footer.inc.php'); 

$g_obj_db->disconnect();

function process_post()
{
	global $g_obj_lock;
	
	if ( isset( $_POST['Command'] ) && $g_obj_lock->page_lock( PageHandler::get_post_value( 'SerialId' ) ) )
	{
		$str_command = $_POST['Command'];
	  
		switch ( $str_command )
		{		
			case 'Delete Selected Problems':
			{
				on_delete_handler();
			}
			break;
	    
			case 'Assign':
			{
				on_assign_handler();
			}
			break;
			
			default:
			{
				MessageHandler::add_message( MSG_ERROR, "Unknown Command" );
			}
			break;
		}
	}
}

function on_delete_handler()
{
	global $g_obj_problem_manager;
	
	$arr_problem_list = PageHandler::get_post_value( 'ProblemId' );
	
	if ( $arr_problem_list == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one problem" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_problem_list as $int_problem_id )
	{
		if ( $g_obj_problem_manager->delete_problem( $int_problem_id ) )
		{
			array_push( $arr_success, $int_problem_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_problem_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully deleted ' . count( $arr_success ) . ' problem(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to delete ' . count( $arr_fail ) . ' problem(s)' );
	}
}

function on_assign_handler()
{
	global $g_obj_assign_problem_manager;
	
	$arr_problem_list = PageHandler::get_post_value( 'ProblemId' );	
	$int_selected_course_id = PageHandler::get_post_value( 'SelectedCourse' );
	
	if ( $arr_problem_list == null || $int_selected_course_id == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one problem and select a course" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_problem_list as $int_problem_id )
	{
		if ( $g_obj_assign_problem_manager->assign_problem_to_course( $int_problem_id, $int_selected_course_id ) )
		{
			array_push( $arr_success, $int_problem_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_problem_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully assigned ' . count( $arr_success ) . ' problem(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to assign' . count( $arr_fail ) . ' problem(s)' );
	}
}

?>