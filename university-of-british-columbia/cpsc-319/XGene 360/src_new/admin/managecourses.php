<?php

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );

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

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage Courses";
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

    <strong>
      Click on a course to edit specific course information. 
      <br />To delete a course or several course, click on the checkbox beside each course to be deleted and press 'Delete Selected Courses'.
    </strong>
    <br /><br />

    <input class="buttoninput" type="submit" value="Create New Course" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createcourse'; return false;"/>&nbsp;
    <input class="buttoninput" type="submit" value="Delete Selected Courses" name="Command" />

    <table class="listing" id="ListOfCourses">

      <tr>
        <th width="50"><input type="checkbox" id="CourseIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'CourseId[]' );" /></th>
        <th width="150">Course Name</th>
        <th>Description</th>
      </tr>
      
<?php

	$res_courses = $g_obj_course_manager->view_courses();
	
	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_courses );
		
		echo( '<tr onclick="openCourseDetail( \'' . htmlspecialchars( $res_row->CourseId, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="CourseId[]" value="' . htmlspecialchars( $res_row->CourseId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->Name ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->Description ) .'</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
    
?>
      
    </table>

    <input class="buttoninput" type="submit" value="Create New Course" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createcourse'; return false;" />&nbsp;
    <input class="buttoninput" type="submit" value="Delete Selected Courses" name="Command" />

    <a name="createcourse"></a>
    <div id="create" style="display: none">

      <br /><br />

      <table class="box">

        <tr>
          <th>Create Course</th>
        </tr>
        
        <tr>
          <td>    
              
            <table>
            
              <tr>
                <td width="75">Name:</td>
                <td><input class="textinput" type="text" name="CourseName" id="CourseName" value="<?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'CourseName' ) ) ?>"/></td>
              </tr>
              
              <tr>
                <td style="vertical-align: top">Description:</td>
                <td>
                  <textarea class="textareainput" name="CourseDescription" id="CourseDescription" cols="60" rows="10" onkeydown="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );" onkeyup="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );"><?= htmlspecialchars( PageHandler::write_post_value_if_failed( 'Username' ) ) ?></textarea><br />
                  <input readonly="readonly" class="smallnumberinput" type="text" name="CourseDescriptionLetterCount" size="3" value="<?= 250 - strlen( PageHandler::write_post_value_if_failed( 'CourseName' ) ) ?>" />&nbsp;characters left
                </td>
              </tr>
              
              <tr>
                <td colspan="2" align="right">
                  <input class="buttoninput" type="submit" name="Command" value="Create" onclick="return validateCourseForm();" />
                  &nbsp;<input class="buttoninput" type="reset" name="Reset" value="Reset" onclick="return resetCreateCourseForm();" />
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

		switch( $str_command )
		{ 
			case 'Create':
			{
				on_create_handler();
			}
			break;

			case 'Delete Selected Courses':
			{
				on_delete_handler();
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
	global $g_obj_course_manager;
	
	// create a new course
	$str_course_name = PageHandler::get_post_value( 'CourseName' );
	$str_course_description = PageHandler::get_post_value( 'CourseDescription' );
	
	// verify the input
	if ( strlen( $str_course_name ) == 0 || strlen( $str_course_description ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Please enter the necessary information' );
		return;
	}
	 
	// process the input
	if ( $g_obj_course_manager->add_course( $str_course_name, $str_course_description ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully created Course "' . $str_course_name . '"' );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to create Course "' . $str_course_name . '"' );
	}
}

function on_delete_handler()
{
	global $g_obj_course_manager;
	
	$arr_course_list = PageHandler::get_post_value( 'CourseId' );
	
	if ( $arr_course_list == null )
	{
		MessageHandler::add_message( MSG_FAIL, "Please select at least one course" );
		return;	
	}
	
	$arr_success = array();
	$arr_fail = array();
	
	foreach( $arr_course_list as $int_course_id )
	{
		if ( $g_obj_course_manager->delete_course( $int_course_id ) )
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
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully deleted ' . count( $arr_success ) . ' course(s)' );
	}
	
	if ( count( $arr_fail ) != 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to delete ' . count( $arr_fail ) . ' course(s)' );
	}
}

?>
