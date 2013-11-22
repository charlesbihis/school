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

require( '../includes/classes/db/coursemanager.class.php' );

$obj_course_manager = new CourseManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{ 
  $command = $_POST['Command'];
  
  switch($command)
  { 
    case 'Create':
    {
		// create a new course
		if ( $obj_course_manager->add_course( $_POST['CourseName'], $_POST['CourseDescription'] ) )
		{
			MessageHandler::add_message(MSG_SUCCESS, "Course \"" . $_POST['CourseName'] . "\" created successfully!");
		}  // if success
		else
		{
			MessageHandler::add_message(MSG_FAIL, "Error creating course \"" . $_POST . "\"");
		}  // else failed
    }

    break;
  
    case 'Delete':
    {
	    // ErrorHandler::add_error( );
	    if ( isset( $_POST['CourseId'] ) )
	    {
		    // TODO: check error for delete course  
		    $arr_course_list = $_POST['CourseId'];
		    $count = 0;
		    
		    foreach( $arr_course_list as $str_course_id )
		    {
			    // echo( $selectedCourse )
				if ( $obj_course_manager->delete_course( $str_course_id ) )
				{
					//MessageHandler::add_message( MSG_SUCCESS, "Course \"" . $str_course_id . "\" deleted successfully!" );
					$count++;
				}  // if success
				else
				{
					MessageHandler::add_message( MSG_FAIL, "Error deleting course \"" . $str_course_id . "\"" );
				}  // else failed
			}
			
			MessageHandler::add_message( MSG_SUCCESS, $count . " courses successfully deleted!" );
	    }
    }
    
    break;
  }
}

$res_courses = $obj_course_manager->view_courses();

$str_page_title = "Manage Courses";
$arr_scripts = array( 'managecourse.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";

require ( '../includes/header.inc.php' );

?>

<script type="text/javascript">

  xgene360_cu.using( 'sortabletable' );
  
</script>

<!-- Start Content -->

<div>

  <form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <strong>Click on a course to edit, and select it for deletion.</strong>
    <br /><br />
    
    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createcourse'; return false;"/>
    &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
    
    <table class="listing" id="listOfCourses">
    
      <tr>
        <th width="50"><input type="checkbox" id="CourseIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'CourseId[]' );" /></th>
        <th width="200">Course Name</th>
        <th>Description</th>
      </tr>
      
      <?php
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_courses );
        
        echo( '<tr onclick="openCourseDetail( \''.$res_row->CourseId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
        echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="CourseId[]" value="'.$res_row->CourseId.'" /></td>'."\n" );
        echo( '<td>'.$res_row->Name.'</td>'."\n" );
        echo( '<td>'.$res_row->Description.'</td>'."\n" );
        echo( '</tr>'."\n" );
      }
          
      ?>
      
    </table>

    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createcourse'; return false;"/>
    &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />

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
                <td><input class="textinput" type="text" name="CourseName" id="CourseName" /></td>
              </tr>
              
              <tr>
                <td style="vertical-align: top">Description:</td>
                <td>
                  <textarea class="textareainput" name="CourseDescription" id="CourseDescription" cols="60" rows="10" onkeydown="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );" onkeyup="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );"></textarea><br />
                  <input readonly="readonly" class="smallnumberinput" type="text" name="CourseDescriptionLetterCount" size="3" maxlength="3" value="250" />&nbsp;characters left
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
    
    <input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
 
  </form>

</div>

<!-- End Content -->

<?php 

require_once( '../includes/footer.inc.php' ); 

$obj_db->disconnect();

?>
