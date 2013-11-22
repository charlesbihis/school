<?php

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/tamanager.class.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/assigntamanager.class.php' );

/*
* necessary id
*/

$g_str_parent_page = './managetas.php';

PageHandler::check_necessary_id( array( 'TAId' ), $g_str_parent_page );

/*
* initialize common stuff
*/

$g_obj_db = null;
$g_obj_lock = null;
$g_str_serial = null;
$g_obj_user = null;

PageHandler::initialize();
PageHandler::check_permission( array( UP_ADMINISTRATOR, UP_PROFESSOR, UP_TA ) );

$g_obj_ta_manager = new TAManager( $g_obj_user, $g_obj_db );
$g_obj_course_manager = new CourseManager( $g_obj_user, $g_obj_db );
$g_obj_assign_ta_manager = new AssigntaManager( $g_obj_user, $g_obj_db );

/*
* required info
*/

$g_str_ta_id = $_GET['TAId'];

verify_ta_exists();

process_post();

/*
* set header stuff
*/

$g_str_page_title = "View TA";
$g_arr_scripts = array( 'manageta.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[$g_obj_user->int_privilege];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->
<div>

  <form method="post" id="UpdateTAForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <input class="buttoninput" type="button" value="Back to TA Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <br /><br /><br />

    <table class="box">

      <tr>
        <th>Modify TA</th>
      </tr>

      <tr>
        <td>

          <table>

            <tr>
              <td width="150">First Name:</td>
              <td><input class="textinput" type="text" name="TAFirstName" value="<?= htmlspecialchars( $g_arr_ta_info->FirstName ) ?>" /></td>
            </tr>

            <tr>
              <td>Last Name:</td>
              <td><input class="textinput" type="text" name="TALastName" value="<?= htmlspecialchars( $g_arr_ta_info->LastName ) ?>"/></td>
            </tr>

            <tr>
              <td>New Password:</td>
              <td><input class="textinput" type="password" name="NewTAPassword" id="NewTAPassword" /></td>
            </tr>

            <tr>
              <td>Confirm New Password:&nbsp;</td>
              <td><input class="textinput" type="password" name="NewTAPasswordConfirm" id="NewTAPasswordConfirm" /></td>
            </tr>

            <tr>
              <td colspan="2" align="right">
                <input class="buttoninput" type="submit" name="Command" value="Update" onclick="return validateUpdateTAForm();" />
                &nbsp;<input class="buttoninput" type="reset" name="Command" value="Reset" onclick="return resetUpdateTAForm();" />
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
          <strong>The TA has access to the following courses:</strong>
        </td>

        <td align="right">

          <select name="SelectedCourse" id="SelectedCourse">
        
<?php

	echo( '<option selected="selected" value="">&nbsp;Select a course:&nbsp;&nbsp;</option>' );         
	echo( '<option value="">&nbsp;----------</option>' );   
	echo( '<option value="">&nbsp;</option>' );

	$res_courses = $g_obj_course_manager->view_courses();
	
	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_courses );
		
		echo( '<option value="' . htmlspecialchars( $res_row->CourseId ) . '">&nbsp;' . htmlspecialchars( $res_row->Name ) . '&nbsp;</option>' . "\n" );
	}

?>
         
          </select>

          &nbsp;<input class="buttoninput" type="submit" value="Assign" name="Command" onclick="return onAssignATAToACourseButtonClickHandler( 'SelectCourse' );" />
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

	$res_ta_courses = $g_obj_ta_manager->view_ta_courses( $g_str_ta_id );
	
	if ( $g_obj_db->get_number_of_rows( $res_ta_courses ) == 0 )
	{
		echo( '<tr>' . "\n" );
		echo( '<td colspan="3">This TA does not have any course assigned</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_ta_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_ta_courses );

		echo( '<tr onclick="openCourseDetail( \'' . htmlspecialchars( $res_row->CourseId ) . '\' );" onmouseover="xgene360_cu.useHandCursor( this );" onmouseout="xgene360_cu.useRegularCursor( this );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="CourseId[]" value="' . htmlspecialchars( $res_row->CourseId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->Name ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->Description ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}

?>

    </table>

	<input class="buttoninput" type="submit" value="Remove" name="Command" />
	
    <br /><br />

    <input class="buttoninput" type="button" value="Back to TA Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>"/>

  </form>

</div>
<!-- End Content -->

<?php
}

require_once( '../includes/footer.inc.php' );

$g_obj_db->disconnect();

function verify_ta_exists()
{
	global $g_obj_ta_manager, $g_obj_db, $g_str_ta_id, $g_arr_ta_info;
	
	$res_ta = $g_obj_ta_manager->view_user( $g_str_ta_id );
	
	if ( $g_obj_db->get_number_of_rows( $res_ta ) == 0 )
	{
		MessageHandler::add_message( MSG_ERROR, 'The TA does not exist' );
	}
	
	else
	{
		$g_arr_ta_info = $g_obj_db->fetch( $res_ta );
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
		  
			case 'Assign':
			{
				on_assign_handler();
			}
			break;
			
			case 'Remove':
			{
				on_remove_handler();
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
	global $g_obj_ta_manager, $g_str_ta_id;
	
	$str_first_name = PageHandler::get_post_value( 'TAFirstName' );
	$str_last_name = PageHandler::get_post_value( 'TALastName' );
	
	if ( strlen( $str_first_name ) == 0 || strlen( $str_last_name ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Please enter the necessary information' );
		return;
	}
	
	if ( $g_obj_ta_manager->modify_user( $g_str_ta_id, $str_first_name, $str_last_name, 0 ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully updated the account for TA "' . $str_first_name . ' ' . $str_last_name . '"' );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to update the account for TA "' . $str_first_name . ' ' . $str_last_name . '"' );
	}
	
	$str_password = PageHandler::get_post_value( 'TAPassword' );
	$str_password_confirm = PageHandler::get_post_value( 'TAPasswordConfirm' );
	
	if ( strlen( $str_password ) != 0 )
	{
		if ( $str_password != $str_password_confirm )
		{
			MessageHandler::add_message( MSG_FAIL, 'The password does not match' );
			return;
		}
		
		if ( $g_obj_ta_manager->modify_password( $g_str_ta_id, $str_password ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, 'Successfully changed the password' );
		}
		
		else
		{
			MessageHandler::add_message( MSG_FAIL, 'Failed to change the password' );
		}
	}
}

function on_assign_handler()
{
	global $g_obj_assign_ta_manager, $g_str_ta_id;
	
	$int_selected_course_id = PageHandler::get_post_value( 'SelectedCourse' );
	
	if ( strlen( $int_selected_course_id ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select a course" );
		return;
	}
	
	if ( $g_obj_assign_ta_manager->assign_TA( $g_str_ta_id, $int_selected_course_id ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully assigned the TA to the Course' );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to assign the TA to the Course' );
	}
}

function on_remove_handler()
{
	global $g_obj_assign_ta_manager, $g_str_ta_id;
	
	$arr_course_list = PageHandler::get_post_value( 'CourseId' );	
	
	if ( $arr_course_list == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one professor" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_course_list as $int_course_id )
	{
		if ( $g_obj_assign_ta_manager->unassign_TA( $g_str_ta_id, $int_course_id ) )
		{
			array_push( $arr_success, $int_course_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_course_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully removed the TA from ' . count( $arr_success ) . ' course(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to remove the TA from ' . count( $arr_fail ) . ' course(s)' );
	}
}

?>
