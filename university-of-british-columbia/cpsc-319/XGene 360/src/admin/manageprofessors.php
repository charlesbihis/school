<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/professormanager.class.php' );
require( '../includes/classes/db/coursemanager.class.php' );
require( '../includes/classes/db/assignprofessormanager.class.php' );

$obj_professor_manager = new professormanager( $obj_user, $obj_db );
$obj_course_manager = new coursemanager( $obj_user, $obj_db );
$obj_assign_professor_manager = new assignprofessormanager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
  {
    case 'Create':
    {
		  // create a new professor
		  if ( $obj_professor_manager->create_user( $_POST['UserId'], UP_PROFESSOR,  $_POST['FirstName'], $_POST['LastName'], $_POST['Password'], 0 ) )
		  {
				  MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" created successfully!" );
		  }  // if success
		  
		  else
		  {
				  MessageHandler::add_message( MSG_FAIL, "Error creating professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\"");
		  }  // else failed
    }
    
    break;
    
    case 'Delete':
    {
      if ( isset( $_POST['ProfessorId'] ) )
      {
        $arr_professor_list = $_POST['ProfessorId'];
        
        foreach( $arr_professor_list as $str_professor_id )
        {
			    if ( $obj_professor_manager->delete_user( $str_professor_id ) )
			    {
				    MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" deleted successfully!" );
			    }  // if success
			    else
			    {
				    MessageHandler::add_message( MSG_FAIL, "Error deleting professor \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\"");
			    }  // else failed
        }
      }
    }
    
    break;
 
    case 'Assign':
    {     
      if ( isset( $_POST['ProfessorId'] ) )
      {
        $arr_professor_list = $_POST['ProfessorId'];
        
        foreach( $arr_professor_list as $str_professor_id )
        {
			    // FIX: output professor name and course name and not just professor id and course id
			    if ( $obj_assign_professor_manager->assign_professor( $str_professor_id, $_POST['SelectCourse'] ) )
			    {
				    MessageHandler::add_message( MSG_SUCCESS, "Professor \"" . $str_professor_id . "\" successfully assigned to course" );
			    }  // if success
			    
			    else
			    {
				    MessageHandler::add_message( MSG_FAIL, "Error assigning professor \"" . $str_professor_id . "\" to course" );
			    }  // else failed
        }
      }		
	  }
	  
    break;
    
    default:
    {
      MessageHandler::add_message( MSG_ERROR, "Unknown Command" );
    }
  }
}

$res_professors = $obj_professor_manager->view_professors();
$res_courses = $obj_course_manager->view_courses();

$str_page_title = "Manage Professors";
$arr_scripts = array( 'manageprofessors.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";


require ( '../includes/header.inc.php' );

?>

<!-- Start Content -->

<div>

  <form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <strong>Click on a professor to edit professor information, and select it for deletion.</strong>
    <br /><br />

    <table class="format" width="100%">
      
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createprofessor'; return false;"/>
          &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
        </td>
        <td align="right">
          <select name="SelectCourse" id="SelectCourse">
            
            <?php
              
            echo( '<option selected >&nbsp;Select a course:&nbsp;&nbsp;&nbsp;&nbsp;</option>' );         
            echo( '<option>&nbsp;----------</option>' );   
            echo( '<option>&nbsp;</option>' );

            for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
            {
              $res_row2 = $obj_db->fetch( $res_courses );
              echo( '<option value="'.$res_row2->CourseId.'">&nbsp;'.$res_row2->Name.'&nbsp;</option>'."\n" );
            }
            
            ?>
          
	        </select>
	        &nbsp;<input class="buttoninput" type="submit" name="Command" value="Assign" onclick="return onAssignProfessorsToACourseButtonClickHandler( 'ProfessorId[]', 'SelectCourse' );" />
        </td>             
      </tr>
    
    </table>
  
    <table class="listing" id="listOfProfessors">
      
      <tr>
        <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProfessorId[]' );" /></th>
        <th width="150">Username</th>
        <th width="200">Last Name</th>
        <th>First Name</th>
      </tr>

      <?php
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_professors ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_professors );
        
        echo( '<tr onclick="openProfessorDetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
        echo( '<td><input type="checkbox" name="ProfessorId[]" value="'.$res_row->UserId.'" onclick="xgene360_cu.stopPropagation( event );" /></td>'."\n" );
        echo( '<td>'.$res_row->UserId.'</td>'."\n" );
        echo( '<td>'.$res_row->LastName.'</td>'."\n" );
        echo( '<td>'.$res_row->FirstName.'</td>'."\n" );
        echo( '</tr>'."\n" );
      }
          
      ?>  
              
    </table>

    <input class="buttoninput" type="submit" value="Create New" name="Command" onclick="xgene360_cu.toggleDisplay('create'); window.location='#createprofessor'; return false;"/>
    &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
     
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
                <td>Username:</td>
                <td><input class="textinput" type="text" name="UserId" id="UserId" /></td>
              </tr>
              
              <tr>
                <td width="125">First Name:</td>
                <td><input class="textinput" type="text" name="FirstName" id="FirstName" /></td>
              </tr>
              
              <tr>
                <td>Last Name:</td>
                <td><input class="textinput" type="text" name="LastName" id="LastName" /></td>
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
    <input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>    
  </form>    

</div>  

<!-- End Content -->

<?php 

require_once('../includes/footer.inc.php'); 
  
$obj_db->disconnect();

?>