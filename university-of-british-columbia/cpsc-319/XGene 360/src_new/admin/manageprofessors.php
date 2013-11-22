<?php

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/professormanager.class.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/assignprofessormanager.class.php' );

/*
* initialize common stuff
*/

$g_obj_db = null;
$g_obj_lock = null;
$g_str_serial = null;
$g_obj_user = null;

PageHandler::initialize();
PageHandler::check_permission( array( UP_ADMINISTRATOR, UP_PROFESSOR, UP_TA ) );

$g_obj_professor_manager = new ProfessorManager( $g_obj_user, $g_obj_db );
$g_obj_course_manager = new CourseManager( $g_obj_user, $g_obj_db );
$g_obj_assign_professor_manager = new AssignProfessorManager( $g_obj_user, $g_obj_db );

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage Professors";
$g_arr_scripts = array( 'manageprofessors.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[$g_obj_user->int_privilege];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require ( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->
<div>

  <form method="post" action="<?= $_SERVER['REQUEST_URI'] ?>">

    <strong>Click on a professor to edit professor information, and select it for deletion.</strong>
    <br /><br />

    <table class="format" width="100%">
      
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createprofessor'; return false;" />&nbsp;
          <input class="buttoninput" type="submit" value="Delete" name="Command" />
        </td>
        <td align="right">
          <select name="SelectedCourse" id="SelectedCourse">
            
<?php
  
	echo( '<option selected="selected">&nbsp;Select a course:&nbsp;&nbsp;&nbsp;&nbsp;</option>' );
	echo( '<option>&nbsp;----------</option>' );   
	echo( '<option>&nbsp;</option>' );

	$res_courses = $g_obj_course_manager->view_courses();

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_courses );
		
		echo( '<option value="' . htmlspecialchars( $res_row->CourseId ) . '">&nbsp;' . htmlspecialchars( $res_row->Name ) . '&nbsp;</option>'."\n" );
	}

?>
          
          </select>&nbsp;
          <input class="buttoninput" type="submit" name="Command" value="Assign" onclick="return onAssignProfessorsToACourseButtonClickHandler( 'ProfessorId[]', 'SelectCourse' );" />
        </td>
      </tr>

    </table>

    <table class="listing" id="ListOfProfessors">

      <tr>
        <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProfessorId[]' );" /></th>
        <th width="150">Username</th>
        <th width="200">Last Name</th>
        <th>First Name</th>
      </tr>

<?php

	$res_professors = $g_obj_professor_manager->view_professors();
	
	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_professors ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_professors );
	  
		echo( '<tr onclick="openProfessorDetail( \'' . htmlspecialchars( $res_row->UserId, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="ProfessorId[]" value="' . htmlspecialchars( $res_row->UserId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->UserId ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->LastName ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->FirstName ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
    
?>

    </table>

    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createprofessor'; return false;" />&nbsp;
    <input class="buttoninput" type="submit" value="Delete" name="Command" />

    <div id="create" style="display: none">

      <a name="createprofessor"></a>

      <br /><br />

      <table class="box">

        <tr>
          <th>Create Professor</th>
        </tr>
        <tr>
          <td>

            <table>

              <tr>
                <td width="125">Username:</td>
                <td><input class="textinput" type="text" name="Username" id="Username" value="<?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'Username' ) ) ?>" /></td>
              </tr>

              <tr>
                <td>First Name:</td>
                <td><input class="textinput" type="text" name="FirstName" id="FirstName" value="<?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'FirstName' ) ) ?>" /></td>
              </tr>

              <tr>
                <td>Last Name:</td>
                <td><input class="textinput" type="text" name="LastName" id="LastName" value="<?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'LastName' ) ) ?>" /></td>
              </tr>

              <tr>
                <td>Password:</td>
                <td><input class="textinput" type="password" name="Password" id="Password" /></td>
              </tr>

              <tr>
                <td>Confirm Password:&nbsp;</td>
                <td><input class="textinput" type="password" name="ConfirmPassword" id="ConfirmPassword" /></td>
              </tr>

              <tr>
                <td colspan="2" align="right">
                  <input class="buttoninput" type="submit" name="Command" value="Create" onclick="return validateCreateProfessorForm();" />
                  &nbsp;<input class="buttoninput" type="reset" name="Reset" value="Reset" onclick="return resetCreateProfessorForm();" />
                </td>
              </tr>

            </table>

          </td>
        </tr>

      </table>

    </div>

    <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>" />

  </form>

</div>
<!-- End Content -->

<?php 
}

require_once( '../includes/footer.inc.php' ); 
  
$g_obj_db->disconnect();

function process_post()
{
	global $g_obj_lock;
	
	if ( isset( $_POST['Command'] ) && $g_obj_lock->page_lock( PageHandler::get_post_value( 'SerialId' ) ) )
	{
		$str_command = $_POST['Command'];
	  
		switch ( $str_command )
		{
			case 'Create':
			{
				on_create_handler();
			}
			break;
	    
			case 'Delete':
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

function on_create_handler()
{
	global $g_obj_professor_manager;
	
	$str_user_name = PageHandler::get_post_value( 'Username' );
	$str_first_name = PageHandler::get_post_value( 'FirstName' );
	$str_last_name = PageHandler::get_post_value( 'LastName' );
	$str_password = PageHandler::get_post_value( 'Password' );
	$str_password_confirm = PageHandler::get_post_value( 'ConfirmPassword' );
	
	// verify the input
	if ( strlen( $str_user_name ) == 0 || strlen( $str_first_name ) == 0 || strlen( $str_last_name ) == 0 || strlen( $str_password ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Please enter the necessary information' );
		return;
	}
	
	if ( $str_password != $str_password_confirm )
	{
		MessageHandler::add_message( MSG_FAIL, 'The password does not match' );
		return;
	}
	
	// create a new professor
	if ( $g_obj_professor_manager->create_user( $str_user_name, UP_PROFESSOR,  $str_first_name, $str_last_name, $str_password, 0 ) )
	{
			MessageHandler::add_message( MSG_SUCCESS, 'Successfully created an account for Professor "' . $str_first_name . ' ' . $str_last_name . '"' );
	}

	else
	{
			MessageHandler::add_message( MSG_FAIL, 'Failed to create an account for Professor "' . $str_first_name . ' ' . $str_last_name . '"' );
	}
}

function on_delete_handler()
{
	global $g_obj_professor_manager;
	
	$arr_professor_list = PageHandler::get_post_value( 'ProfessorId' );
	
	if ( $arr_professor_list == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one professor" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_professor_list as $int_professor_id )
	{
		if ( $g_obj_professor_manager->delete_user( $int_professor_id ) )
		{
			array_push( $arr_success, $int_professor_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_professor_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully deleted ' . count( $arr_success ) . ' account(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to delete ' . count( $arr_fail ) . ' account(s)' );
	}
}

function on_assign_handler()
{
	global $g_obj_assign_professor_manager;
	
	$arr_professor_list = PageHandler::get_post_value( 'ProfessorId' );	
	$int_selected_course_id = PageHandler::get_post_value( 'SelectedCourse' );
	
	if ( $arr_professor_list == null || strlen( $int_selected_course_id ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one professor and select a course" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_professor_list as $int_professor_id )
	{
		if ( $g_obj_assign_professor_manager->assign_professor( $int_professor_id, $int_selected_course_id ) )
		{
			array_push( $arr_success, $int_professor_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_professor_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully assigned ' . count( $arr_success ) . ' professor(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to assign' . count( $arr_fail ) . ' professor(s)' );
	}
}

?>
