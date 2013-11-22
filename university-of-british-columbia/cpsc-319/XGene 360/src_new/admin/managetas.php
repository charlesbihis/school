<?php

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/tamanager.class.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/assigntamanager.class.php' );

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
$g_obj_assign_ta_manager = new AssignTAManager( $g_obj_user, $g_obj_db );

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage TAs";
$g_arr_scripts = array( 'manageta.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[$g_obj_user->int_privilege];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->
<div>
  <form method="post" action="<?= $_SERVER['REQUEST_URI'] ?>">

    Click on a TA to edit TA information, and select it for deletion.
    <br /><br />

    <table class="format" width="100%">
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createta'; return false;" />&nbsp;
          <input class="buttoninput" type="submit" value="Delete" name="Command" />
        </td>
        <td align="right">
           <select size="1" name="SelectedCourse" id="SelectedCourse">
              
<?php
  
  echo( '<option selected="selected">Assign selected to course:</option>' );
  echo( '<option>----------</option>' );
  echo( '<option>&nbsp;</option>' );
  
  $res_courses = $g_obj_course_manager->view_courses();
  
  for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
  {
    $res_row = $g_obj_db->fetch( $res_courses );
    
    echo( '<option value="' . htmlspecialchars( $res_row->CourseId ) . '">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' . htmlspecialchars( $res_row->Name ) . '</option>'."\n" );
  }

?>

           </select>
           &nbsp;
           <input align="right" class="buttoninput" type="submit" value="Assign" name="Command" />
        </td>
      </tr>
    </table>

    <table class="listing" id="ListOfTAs">
      <tr>
        <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'TAId[]' );" /></th>
        <th width="150">Username</th>
        <th width="200">Last Name</th>
        <th>First Name</th>
      </tr>
		
<?php

	$res_tas = $g_obj_ta_manager->view_tas();

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_tas ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_tas );

		echo( '<tr onclick="openTADetail( \'' . htmlspecialchars( $res_row->UserId ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="TAId[]" value="' . htmlspecialchars( $res_row->UserId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->UserId ) . '</td>' );
		echo( '<td>' . htmlspecialchars( $res_row->LastName ) . '</td>' );
		echo( '<td>' . htmlspecialchars( $res_row->FirstName ) . '</td>' );
		echo( '</tr>' );
	}
	
?>

    </table>

    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createta'; return false;" />&nbsp;
    <input class="buttoninput" type="submit" value="Assign To Course:" name="Command" />&nbsp;
    <input class="buttoninput" type="submit" value="Delete" name="Command" />

    <a name="createta"></a>
    <div id="create" style="display: none">

      <table class="box">
        <tr>
          <th>Create New TA</th>
        </tr>
        <tr>
          <td>

            <table>
              <tr>
                <td>Username:</td>
                <td><input class="textinput" type="text" name="Username" id="Username" value="<?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'Username' ) ) ?>" /></td>
              </tr>
              <tr>
                <td width="125">First Name:</td>
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
                <td>Confirm Password:</td>
                <td><input class="textinput" type="password" name="ConfirmPassword" id="ConfirmPassword" /></td>
              </tr>
              <tr>
                <td colspan="2" align="right">
                <input class="buttoninput" type="submit" name="Command" value="Create" onclick="return validateCreateTAForm();" />
                &nbsp;<input class="buttoninput" type="reset" name="Reset" value="Reset" onclick="return resetCreateTAForm();" />
                </td>
              </tr>
            </table>

          </td>
        </tr>
      </table>

      <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>" />

    </div>

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
	global $g_obj_ta_manager;
	
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
	
	// create a new ta
	if ( $obj_ta_manager->create_user( $str_user_name, UP_TA,  $str_first_name, $str_last_name, $str_password, 0 ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully created an account for TA "' . $str_first_name . ' ' . $str_last_name . '"' );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to create an account for TA "' . $str_first_name . ' ' . $str_last_name . '"' );
	}
}

function on_delete_handler()
{
	global $g_obj_ta_manager;
	
	$arr_ta_list = PageHandler::get_post_value( 'TAId' );
	
	if ( $arr_ta_list == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one professor" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_ta_list as $int_ta_id )
	{
		if( $g_obj_ta_manager->delete_user( $int_ta_id ) )
		{
			array_push( $arr_success, $int_ta_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_ta_id );
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
	global $g_obj_assign_ta_manager;
	
	$arr_ta_list = PageHandler::get_post_value( 'TAId' );	
	$int_selected_course_id = PageHandler::get_post_value( 'SelectedCourse' );
	
	if ( $arr_ta_list == null || strlen( $int_selected_course_id ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one TA and select a course" );
		return;
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_ta_list as $int_ta_id )
	{
		if ( $g_obj_assign_ta_manager->assign_TA( $str_ta_id, $int_selected_course_id ) )
		{
			array_push( $arr_success, $int_ta_id );
		}
		
		else
		{
			array_push( $arr_fail, $int_ta_id );
		}
	}
	
	if ( count( $arr_success ) != 0 )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully assigned ' . count( $arr_success ) . ' TA(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to assign' . count( $arr_fail ) . ' TA(s)' );
	}
}

?>