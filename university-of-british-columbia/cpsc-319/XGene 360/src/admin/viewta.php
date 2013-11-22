<?php

require_once( '../includes/global.inc.php' ); 

if ( !isset( $_GET['taid'] ) )
{
  PageHandler::redirect( './managetas.php' );
}

$int_ta_id = $_GET['taid'];

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirect page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT)
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/tamanager.class.php' );
require( '../includes/classes/db/coursemanager.class.php' );
require( '../includes/classes/db/assigntamanager.class.php' );

$obj_ta_manager = new tamanager( $obj_user, $obj_db );
$obj_course_manager = new coursemanager( $obj_user, $obj_db );
$obj_assign_ta_manager = new assigntamanager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
  {
    case 'Update':
    {
		  if ( $obj_ta_manager->modify_user( $int_ta_id, $_POST['TAFirstName'], $_POST['TALastName'], 0 ) )
		  {
			  MessageHandler::add_message( MSG_SUCCESS, "TA \"" . $_POST['TAFirstName'] . " " . $_POST['TALastName'] . "\" updated successfully!" );
		  }  // if success
		  else
		  {
			  MessageHandler::add_message( MSG_FAIL, "Error modifying TA \"" . $_POST['TAFirstname'] . " " . $_POST['TALastName'] . "\"" );
		  }  // else failed

		  if ( strlen( $_POST['TAPassword'] ) != 0 )
		  {
			  if ( $obj_ta_manager->modify_password( $int_ta_manager, $_POST['TAPassword'] ) )
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
      // ErrorHandler::add_error( );
      if ( isset( $_POST['TAId'] ) )
      {
        // TODO: check error for delete TA
        $arr_ta_list = $_POST['TAId'];
        
        foreach( $arr_ta_list as $str_ta_id )
        {
			    if ( $obj_assign_ta_manager->assign_ta( $str_ta_id, $_POST['SelectCourse'] ) )
			    {
				    MessageHandler::add_message( MSG_SUCCESS, "TA \"" . $str_ta_id . "\" successfully assigned to course!" );
			    }  // if success
			    else
			    {
				    MessageHandler::add_message( MSG_FAIL, "Error assigning TA \"" . $str_ta_id . "\" to course" );
			    }  // else failed
        }
      }
    }  
  }
}

$res_user = $obj_ta_manager->view_user( $int_ta_id );
$res_courses = $obj_course_manager->view_courses();
$res_ta_courses = $obj_ta_manager->view_ta_courses( $int_ta_id );

$bln_invalidta = false;

if ( $obj_db->get_number_of_rows( $res_user ) == 0 )
{
  // TODO: add error handler here
  $bln_invalidta = true;
}

else
{
  $arr_ta_info = $obj_db->fetch( $res_user );
}

$str_page_title = "View TA";
$arr_scripts = array( 'manageta.js' );
$arr_nav_links = $g_arr_nav_links[UP_ADMINISTRATOR];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

?>

<!-- Start Content -->
<div>
  <form method="post" id="UpdateTAForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <input class="buttoninput" type="button" value="Back to TA Listing" onclick="window.location='managetas.php';" />
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
              <td><input class="textinput" type="text" name="TAFirstName" value="<?php if ( isset( $arr_ta_info ) ) { echo( $arr_ta_info->FirstName ); } ?>" /></td>
            </tr>
             
            <tr>
              <td>Last Name:</td>
              <td><input class="textinput" type="text" name="TALastName" value="<?php if ( isset( $arr_ta_info ) ) { echo( $arr_ta_info->LastName ); } ?>"/></td>
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
         
          &nbsp;<input class="buttoninput" type="submit" value="Assign" name="Command" onclick="return onAssignATAToACourseButtonClickHandler( 'SelectCourse' );" />
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

      if ( $obj_db->get_number_of_rows( $res_ta_courses ) == 0 )
      {
        echo( '<tr>'."\n" );
        echo( '<td colspan="3">This TA does not have any course assigned</td>'."\n" );
        echo( '</tr>'."\n" );
      }
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_ta_courses ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_ta_courses );
        
        echo( '<tr onclick="openCourseDetail( \''.$res_row->CourseId.'\' );" onmouseover="xgene360_cu.useHandCursor( this );" onmouseout="xgene360_cu.useRegularCursor( this );">'."\n" );
        echo( '<td><input type="checkbox" name="CourseId[]" value="'.$res_row->CourseId.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
        echo( '<td>'.$res_row->Name.'</td>'."\n" );
        echo( '<td>'.$res_row->Description.'</td>'."\n" );
        echo( '</tr>'."\n" );
      }
        
      ?>
      
    </table>

    <br /><br />
    <input class="buttoninput" type="button" value="Back to TA Listing" onclick="window.location='manageTAs.php';" />
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
  </form>

</div>

<!-- End Content -->

<?php require_once('../includes/footer.inc.php'); ?>
