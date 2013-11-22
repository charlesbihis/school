<?php 

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/assignprofessormanager.class.php' );
require_once( '../includes/classes/db/assigntamanager.class.php' );

/*
* necessary id
*/

$g_str_parent_page = './managecourses.php';

PageHandler::check_necessary_id( array( 'CourseId' ), $g_str_parent_page );

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
$g_obj_assign_professor_manager = new AssignProfessorManager( $g_obj_user, $g_obj_db );
$g_obj_assign_ta_manager = new AssignTAManager( $g_obj_user, $g_obj_db );

/*
* required info
*/

$g_int_course_id = $_GET["CourseId"];

verify_course_exists();

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage Courses &gt; View Course";
$g_arr_scripts = array( 'managecourse.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[$g_obj_user->int_privilege];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->
<div>

  <form method="post" action="<?= $_SERVER['REQUEST_URI'] ?>">

    <input class="buttonback" type="button" value="&lt;&nbsp;&nbsp;Back to Course Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <br /><br /><br />

    <table class="box">
      <tr>
        <th>View Course</th>
      </tr>
      <tr>
        <td>
          <table>
            <tr>
              <td width="75">Name:</td>
              <td><input class="textinput" type="text" name="CourseName" id="CourseName" size="30" value="<?= htmlspecialchars( $g_arr_course_info->Name ) ?>" /></td>
            </tr>
            <tr>
              <td style="vertical-align: top">Description:</td>
              <td>
                <textarea class="textareainput" name="CourseDescription" id="CourseDescription" cols="60" rows="10" onkeydown="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );" onkeyup="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );"><?= htmlspecialchars( $g_arr_course_info->Description ) ?></textarea><br />
                <input class="smallnumberinput" readonly="readonly" type="text" name="CourseDescriptionLetterCount" size="3" maxlength="3" value="<?= 250 - strlen( $g_arr_course_info->Description ) ?>" /> characters left
              </td>
            </tr>
            <tr>
              <td colspan="2" align="right">
                <input class="buttoninput" type="submit" name="Command" value="Update" onclick="return validateCourseForm();" />&nbsp;
                <input class="buttoninput" type="reset" name="Command" value="Reset" onclick="return resetUpdateCourseForm();" />
              </td>
            </tr>
          </table>
        </td>
      </tr>
    </table>

    <br /><br />

    <strong>The following professors have access to this course:</strong>
    <table class="listing" id="ListOfProfessor">
      <tr>
        <th width="50"><input type="checkbox" id="ProfessorIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProfessorId[]' );" /></th>
        <th width="150">First Name</th>
        <th>Last Name</th>
      </tr>      </tr>
		
<?php

	$res_professors = $g_obj_course_manager->view_course_professors( $g_int_course_id );

	if ( $g_obj_db->get_number_of_rows( $res_professors ) == 0 )
	{
		echo( '<tr>'."\n" );
		echo( '<td colspan="3">There is no professor associated with this course</td>'."\n" );
		echo( '</tr>'."\n" );
	}

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_professors ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_professors );

		echo( '<tr onclick="openProfessorDetail( \'' . htmlspecialchars( $res_row->UserId, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="ProfessorId[]" value="' . htmlspecialchars( $res_row->UserId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->FirstName ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->LastName ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
?>
	
    </table>

    <input class="buttoninput" type="submit" name="Command" value="Drop Selected Professors" />

    <br /><br /><br />

    <strong>The following TAs have access to this course:</strong>
    <table class="listing" id="ListOfTA">
      <tr>
        <th width="50"><input type="checkbox" id="TAIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'TAId[]' );" /></th>
        <th width="150">First Name</th>
        <th>Last Name</th>
      </tr>
      
<?php

	$res_tas = $g_obj_course_manager->view_course_tas( $g_int_course_id );

	if ( $g_obj_db->get_number_of_rows( $res_tas ) == 0 )
	{
		echo( '<tr>' . "\n" );
		echo( '<td colspan="3">There is no TA associated with this course</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_tas ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_tas );

		echo( '<tr onclick="openTADetail( \'' . htmlspecialchars( $res_row->UserId, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );"">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="TAId[]" value="' . htmlspecialchars( $res_row->UserId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->FirstName ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->LastName ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
	
?>

    </table>

    <input class="buttoninput" type="submit" name="Command" value="Drop Selected TAs" />

    <br /><br /><br />

    <strong>The following problems are assigned to this course:</strong>
    <table class="listing" id="ListOfProblem">
      <tr>
        <th width="200">Problem</th>
        <th width="200">Start Date</th>
        <th>Due Date</th>
      </tr>
		
<?php
	
	$res_problems = $g_obj_course_manager->view_course_problems( $g_int_course_id );

	if ( $g_obj_db->get_number_of_rows( $res_problems ) == 0 )
	{
		echo( '<tr>'."\n" );
		echo( '<td colspan="3">There is no problem associated with this course</td>'."\n" );
		echo( '</tr>'."\n" );
	}

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_problems ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_problems );

		echo( '<tr onclick="openProblemDetail( \'' . htmlspecialchars( $res_row->problem_id, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->problem_name ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->start_date ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->due_date ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
?>

    </table>

    <br /><br />

    <input class="buttonback" type="button" value="&lt;&nbsp;&nbsp;Back to Course Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>" />

  </form>

</div>
<!-- End Content -->

<?php
}
	
require_once( '../includes/footer.inc.php' );

$g_obj_db->disconnect();

function verify_course_exists()
{
	global $g_obj_course_manager, $g_obj_db, $g_int_course_id, $g_arr_course_info;
	
	$res_course = $g_obj_course_manager->view_course_details( $g_int_course_id );
	
	if ( $g_obj_db->get_number_of_rows( $res_course ) == 0 )
	{
		MessageHandler::add_message( MSG_ERROR, 'The course does not exist' );
	}
	
	else
	{
		$g_arr_course_info = $g_obj_db->fetch( $res_course );
	}
}

function process_post()
{
	global $g_obj_lock;
	
	if ( isset( $_POST['Command'] ) && $g_obj_lock->page_lock( PageHandler::get_post_value( 'SerialId' ) ) )
	{
		$str_command = $_POST['Command'];
	  
		switch ( $str_command )
		{
			case 'Update':
			{
				on_update_handler();
			}
			break;

			case 'Drop Selected Professors':
			{
				// DO SOMETHING HERE PLEASE
			}
			break;

			case 'Drop Selected TAs':
			{
				// DO SOMETHING HERE PLEASE
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

function on_update_handler()
{
	global $g_obj_course_manager, $g_int_course_id, $g_str_parent_page;
	
	$str_course_name = PageHandler::get_post_value( 'CourseName' );
	$str_course_description = PageHandler::get_post_value( 'CourseDescription' );
	
	// verify the input
	if ( strlen( $str_course_name ) == 0 || strlen( $str_course_description ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Please enter the necessary information' );
		return;
	}
	
	if ( $g_obj_course_manager->modify_course( $g_int_course_id, $str_course_name, $str_course_description ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully updated Course "' . $str_course_name . '"' );
		
		PageHandler::redirect( $g_str_parent_page );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to update Course "' . $str_course_name . '"' );
	}
}

?>
