<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT)
{
  PageHandler::redirect( UP_INVALID );
}

require( '../includes/classes/db/tamanager.class.php' );
require( '../includes/classes/db/CourseManager.class.php' );
require( '../includes/classes/db/AssignTAManager.class.php' );

$obj_ta_manager = new tamanager( $obj_user, $obj_db );
$obj_course_manager = new coursemanager( $obj_user, $obj_db );
$obj_assign_ta_manager = new assigntamanager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
	{
		case 'Create':
		{
			// create a new ta
			if ( $obj_ta_manager->create_user( $_POST['UserId'], UP_TA,  $_POST['FirstName'], $_POST['LastName'], $_POST['Password'], 0 ) )
			{
				MessageHandler::add_message(MSG_SUCCESS, "TA \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" created successfully!" );
			}  // if success
			else
			{
				MessageHandler::add_message(MSG_FAIL, "Error creating TA \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\"" );
			}  // else failed
		}  // 'Create'
		
		break;
		
		case 'Delete':
		{
			// delete tas
			// TODO: check error for delete TA
			$arr_ta_list = $_POST['TAId'];
			$count = 0;
			
			foreach( $arr_ta_list as $str_ta_id )
			{
				// FIX: output ta name instead of ta id
				if( $obj_ta_manager->delete_user( $str_ta_id ) )
				{
					//MessageHandler::add_message(MSG_SUCCESS, "TA \"" . $_POST['FirstName'] . " " . $_POST['LastName'] . "\" deleted successfully!" );
					$count++;
				}  // if success
				else
				{
					MessageHandler::add_message(MSG_FAIL, "Error deleting TA \"" . $_POST['TAId'] . "\"" );
				}  // else failed
			}
			
			MessageHandler::add_message( MSG_SUCCESS, $count . " TAs successfully deleted" );
		}  // case 'Delete'
		
		break;
		
		case 'Assign':
		{	
			if ( isset( $_POST['TAId'] ) )
			{
				// TODO: check error for delete problem
				$arr_ta_list = $_POST['TAId'];
				$course = 0;

				foreach( $arr_ta_list as $str_ta_id )
				{
					// FIX: output ta name instead of ta id
					if ( $obj_assign_ta_manager->assign_TA( $_POST['selectedCourse'], $str_ta_id ) )
					{
						MessageHandler::add_message(MSG_SUCCESS, "TA \"" . $_POST['TAId'] . "\" successfully assigned to course" );
						$course++;
					}  // if success
					else
					{
						MessageHandler::add_message(MSG_FAIL, "Error assigning TA \"" . $_POST['TAId'] . "\" to course" );
					}  // else failed
				}  // foreach
				
				$count = count($arr_ta_list);
				MessageHandler::add_message(MSG_SUCCESS, $count . " TAs successfully assigned to course" );
			}  // outer if
		}  // case 'Assign'

		break;
	}  // switch statement
}

$res_tas = $obj_ta_manager->view_tas();
$res_courses = $obj_course_manager->view_courses();

$str_page_title = "Manage TAs";
$arr_scripts = array( 'manageta.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_script_block = "xgene360_cu.using( 'sortabletable' )";

require ( '../includes/header.inc.php' );

?>

<!-- Start Content -->   

<div>
	
	<form method="POST" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

    <strong>Click on a TA to edit TA information, and select it for deletion.</strong>
	  <br /><br />
      
    <table class="format" width="100%">
  		
		  <tr>
			  <td>
				  <input class="buttoninput" type="submit" value="Create New" name="Command" onClick="xgene360_cu.toggleDisplay('create'); window.location='#createta'; return false;"/>
				  &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />
			  </td>
			  <td align="right">
				  <select name="selectedCourse">
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
  					
					  <!-- option value="course_id">COURSE NAME</option -->
				  </select>
  				
				  &nbsp;<input alignk="right" class="buttoninput" type="submit" value="Assign" name="Command" />            
			  </td>             
		  </tr>
  		
	  </table>
  	
    <table class="listing" id="listOfTAs">
  	
		  <tr>
			  <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'TAId[]' );" /></th>
			  <th width="150">Username</th>
			  <th width="200">Last Name</th>
			  <th>First Name</th>
		  </tr>
  	
		  <?php
			  for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_tas ); ++$i )
			  {
				  $res_row = $obj_db->fetch( $res_tas );

				  echo( '<tr onclick="openTADetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
				  echo( '<td><input type="checkbox" name="TAId[]" value="'.$res_row->UserId.'" onclick="xgene360_cu.stopPropagation( event );" /></td>' );
				  echo( '<td>'.$res_row->UserId.'</td>' );
				  echo( '<td>'.$res_row->LastName.'</td>' );
				  echo( '<td>'.$res_row->FirstName.'</td>' );
				  echo( '</tr>' );
			  }
		  ?>
  	
	  </table>

	  <input class="buttoninput" type="submit" value="Create New" name="Command" onClick="xgene360_cu.toggleDisplay('create'); window.location='#createta'; return false;"/>
	  &nbsp;<input class="buttoninput" type="submit" value="Delete" name="Command" />

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
  	  
	    <input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>    
	  
	  </div>
	
	</form>

</div>

<!-- End Content -->

<?php 

require_once('../includes/footer.inc.php'); 

?>