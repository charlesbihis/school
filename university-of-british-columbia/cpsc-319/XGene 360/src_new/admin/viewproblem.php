<?php 

/*
* include necessary files
*/

require_once( '../includes/global.inc.php' );
require_once( '../includes/classes/db/problemmanager.class.php' );
require_once( '../includes/classes/db/coursemanager.class.php' );
require_once( '../includes/classes/db/professormanager.class.php' );
require_once( '../includes/classes/db/assignproblemmanager.class.php' );

/*
* necessary id
*/

$g_str_parent_page = './manageproblems.php';

PageHandler::check_necessary_id( array( 'ProblemId' ), $g_str_parent_page );

/*
* initialize common stuff
*/

$g_obj_db = null;
$g_obj_lock = null;
$g_str_serial = null;
$g_obj_user = null;

PageHandler::initialize();
PageHandler::check_permission( array( UP_ADMINISTRATOR, UP_PROFESSOR, UP_TA ) );

$g_obj_problem_manager = new ProblemManager( $g_obj_user, $g_obj_db );
$g_obj_course_manager = new CourseManager( $g_obj_user, $g_obj_db );
$g_obj_professor_manager = new ProfessorManager( $g_obj_user, $g_obj_db );
$g_obj_assign_student_manager = new AssignProblemManager( $g_obj_user, $g_obj_db );

/*
* required info
*/

$g_int_problem_id = $_GET["ProblemId"];

verify_problem_exists();

process_post();

/*
* set header stuff
*/

$g_str_page_title = "Manage Problems &gt; View Problem";
$g_arr_scripts = array( 'manageproblem.js' );
$g_arr_nav_links = $g_arr_nav_defined_links[UP_ADMINISTRATOR];
$g_str_script_block = "xgene360_cu.using( 'sortabletable' )";

require_once( '../includes/header.inc.php' );

if ( $g_bln_display_content )
{
?>

<!-- Start Content -->

<div>

  <form method="post" action="<?= $_SERVER['REQUEST_URI'] ?>">

    <input class="buttonback" type="button" value="&lt;&nbsp;&nbsp;Back to Problem Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <br /><br /><br />

    <table class="format">
      
      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Update" name="Command" onclick="concatDate(); return validateProblemForm(); return " />&nbsp;
          <input class="buttoninput" type="reset" value="Reset To Saved" name="Command" />
        </td>
      </tr>

      <tr>
        <td>      
          
          <table class="box" style="width: 100%">
            
            <tr>
              <th>Modify Problem, id=<?= htmlspecialchars( $g_int_problem_id ) ?></th>
            </tr>
            
            <tr>
              <td>
                
                <table>
                  <tr>
                    <td width="170">Problem Name:</td>
                    <td><input class="longtextinput" type="text" name="ProblemName" id="ProblemName" onkeyup="displayTextFromInput( 'ATrait', 'ThATrait', 'Trait - ' );" value="<?= htmlspecialchars( $g_arr_problem_info->problem_name ) ?>" /></td>
                  </tr>
                  <tr>
                    <td style="vertical-align: top;">Problem Description:</td>
                    <td><textarea class="textareainput" name="ProblemDescription" id="ProblemDescription" cols="60" rows="10"><?= htmlspecialchars( $g_arr_problem_info->problem_desc ) ?></textarea></td>
                  </tr>
                  <tr>
                    <td>Course:</td>
                    <td>
										
<?php
	
	$res_courses = $g_obj_course_manager->view_courses();
		
	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_courses ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_courses );
		
		if ( $res_row->CourseId == $g_arr_problem_info->CourseId )
		{
			echo( $res_row->Name );
			
			break;
		}
	}
	
?>

                    </td>
                  </tr>
                  <tr>
                    <td>Author:</td>
                    <td>
									
<?php
	
	$res_professors = $g_obj_professor_manager->view_professors();

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_professors ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_professors );
		
		if ( $res_row->UserId == $g_arr_problem_info->UserId )
		{
			echo( $res_row->LastName . ',&nbsp' . $res_row->FirstName );
			
			break;
		}
	}
	
?>
                    </td>
                  </tr>
                  <tr>
                    <td colspan="2" height="10">&nbsp;</td>
                  </tr>
                  <tr>
                    <td>Start Date:</td>
                    <td>
                      <select name="StartDateMonth" id="StartDateMonth">

<?php
        	
	for ( $i = 0; $i < 12; $i++ ) 
	{
		if ( $i == ( date( 'n' ) - 1 ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.( $i+1 ).'">'.$g_arr_calendar_months[$i].'</option>' );
	}

?>

                      </select>
                      <select name="StartDateDay" id="StartDateDay">
              	      
<?php 

	for ( $i = 1; $i <= 31; $i++ ) 
	{
		if ( $i == date( 'j' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.$i.'">'.$i.'</option>' );
	}

?>
                      
                      </select>
                      <select name="StartDateYear" id="StartDateYear">
              	      
<?php 

	$tmp_int_start_year = date( 'Y' ) - 5;

	for ( $i = 0; $i <= 10; $i++ ) 
	{
		if ( $tmp_int_start_year == date( 'Y' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.$tmp_int_start_year.'">'.$tmp_int_start_year.'</option>' );

		$tmp_int_start_year++;
	}

?>
                      
                      </select>	
                    </td>
                  </tr>
                  <tr>
                    <td>Start Time:</td>
                    <td>
                      <select name="StartDateHour" id="StartDateHour">
              	      
<?php 

	for ( $i = 1; $i <= 12; $i++ ) 
	{
		if ( $i == date( 'g' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		if( $i <= 9 )
		{
			$i = '0'.$i;
		}

		echo( 'value="'.$i.'">'.$i.'</option>' );
	}

?>
                      
                      </select>:<select name="StartDateMinute" id="StartDateMinute">
              	      
<?php 

	for( $i = 0; $i <= 59; $i++ ) 
	{
		if ( $i == date('i') )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		if( $i <= 9 )
		{
			$i = '0'.$i;
		}

		echo( 'value="'.$i.'">'.$i.'</option>' );
	}

?>
                      
                      </select>
                      &nbsp;
                      <select name="StartDateAPM" id="StartDateAPM">
              	      
<?php 

	if( date( 'A' ) == 'AM' )
	{
		echo( '<option selected="selected" value="AM">AM</option>' );
		echo( '<option value="PM">PM</option>' );
	}

	else
	{
		echo( '<option value="AM">AM</option>' );
		echo( '<option selected="selected" value="PM">PM</option>' );
	}

?>
                      
                      </select>
                    </td>
                  </tr>
                  <tr>
                    <td>Due Date:</td>
                    <td>
                      <select name="EndDateMonth" id="EndDateMonth">

<?php 
              	    
	for( $i = 0; $i < 12; $i++ ) 
	{
		if ( $i == ( date( 'n' ) - 1 ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.($i+1).'">'.$g_arr_calendar_months[$i].'</option>' );
	}

?>

                      </select>
                      <select name="EndDateDay" id="EndDateDay">
              	      
<?php 

	for( $i = 1; $i <= 31; $i++ ) 
	{
		if ( $i == date('j') )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.$i.'">'.$i.'</option>' );

	}

?>
                      
                      </select>
                      <select name="EndDateYear" id="EndDateYear">
              	      
<?php 

	$tmp_int_end_year = date( 'Y' ) - 5;

	for( $i = 0; $i <= 10; $i++ ) 
	{
		if ( $tmp_int_end_year == date( 'Y' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		echo( 'value="'.$tmp_int_end_year.'">'.$tmp_int_end_year.'</option>' );

		$tmp_int_end_year++;
	}

?>
                      
                      </select>	
                    </td>
                  </tr>
                  <tr>
                    <td>Due Time:</td>
                    <td>
                      <select name="EndDateHour" id="EndDateHour">
              	      
<?php 

	for( $i = 1; $i <= 12; $i++ ) 
	{
		if ( $i == date( 'g' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		if ( $i <= 9 )
		{
			$i = '0'.$i;
		}

		echo( 'value="'.$i.'">'.$i.'</option>' );
	}

?>
                      
                      </select>:<select name="EndDateMinute" id="EndDateMinute">
              	      
<?php 

	for( $i = 0; $i <= 59; $i++ ) 
	{
		if ( $i == date( 'i' ) )
		{
			echo( '<option selected="selected" ' );
		}

		else
		{
			echo( '<option ' );
		}

		if ( $i <= 9 )
		{
			$i = '0'.$i;
		}                        	

		echo( 'value="'.$i.'">'.$i.'</option>' );
	}

?>
                      
                      </select>
                      &nbsp;
                      <select name="EndDateAPM" id="EndDateAPM">

<?php 

	if( date( 'A' ) == 'AM' )
	{
		echo( '<option selected="selected" value="AM">AM</option>' );
		echo( '<option value="PM">PM</option>' );
	}

	else
	{
		echo( '<option value="AM">AM</option>' );
		echo( '<option selected="selected" value="PM">PM</option>' );
	}

?>
                      </select>

                    </td>
                  </tr>

                  <tr>
                    <td colspan="2" height="10">&nbsp;</td>
                  </tr>
                  <tr>
                    <td>First Trait Name:</td>
                    <td><input class="longtextinput" type="text" name="TraitAName" id="TraitAName" onkeyup="displayTextFromInput( 'ATrait', 'ThATrait', 'Trait - ' );" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_name ) ?>" /></td>
                  </tr>
                  <tr>
                    <td>Second Trait Name:</td>
                    <td><input class="longtextinput" type="text" name="TraitBName" id="TraitBName" onkeyup="displayTextFromInput( 'BTrait', 'ThBTrait', 'Trait - ' );" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_name ) ?>" /></td>
                  </tr>     
                  <tr>
                    <td colspan="2" height="15">&nbsp;</td>
                  </tr>                               
                  <tr>
                    <td>Max # of Crosses:</td>
                    <td><input class="numberinput" type="text" name="PlantsGenerated" value="<?= htmlspecialchars( $g_arr_problem_info->max_cross ) ?>" />&nbsp;plants</td>
                  </tr>
                  <tr>
                    <td>Offspring per Cross:</td>
                    <td><input class="numberinput" type="text" name="OffspringPerCross" value="<?= htmlspecialchars( $g_arr_problem_info->number_of_progeny_per_cross ) ?>" />&nbsp;plants</td>
                  </tr>
                  <tr>
                    <td>Displayed Plants per Cross:</td>
                    <td><input class="numberinput" type="text" name="PlantsDisplayed" value="<?= htmlspecialchars( $g_arr_problem_info->number_of_displayed_plants ) ?>" />&nbsp;plants</td>
                  </tr>
                  <tr>
                    <td>Range of Acceptance:</td>
                    <td><input class="numberinput" type="text" name="RangeOfAcceptance" value="<?= htmlspecialchars( $g_arr_problem_info->range_of_acceptance ) ?>" />&nbsp;%</td>
                  </tr>
                  <tr>
                    <td height="8"></td>
                  </tr>
                </table>

              </td>
            </tr>
          </table>

        </td>
      </tr>

      <tr>
        <td>

	        <table class="box">
        	
		        <tr>
		          <th>Trait Information</th>
		        </tr>
        		      
		        <tr>  
		          <td>
        	
		            <table class="format">
        		                     
                  <tr>
                    <td id="TdATrait" colspan="2"><h3><?= htmlspecialchars( $g_arr_problem_info->trait_A_name ) ?></h3></td>
                    <td width="100">&nbsp;</td>
                    <td id="TdBTrait" colspan="2"><h3><?= htmlspecialchars( $g_arr_problem_info->trait_B_name ) ?></h3></td>
                    <td width="50">&nbsp;</td>
                  </tr>
                  
				          <tr>
					          <td>Parent 1 Mean:</td>
					          <td><input class="numberinput" type="text" name="TraitAParent1Mean" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_parent_A_mean ) ?>" /></td>
                    <td>&nbsp;</td>				    
					          <td>Parent 1 Mean:</td>
					          <td><input class="numberinput" type="text" name="TraitBParent1Mean" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_parent_A_mean ) ?>" /></td>		    
				            <td>&nbsp;</td>
				          </tr>
      				   
				          <tr>
					          <td>Parent 2 Mean:</td>
					          <td><input class="numberinput" type="text" name="TraitAParent2Mean" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_parent_B_mean ) ?>" /></td>
                    <td>&nbsp;</td>		
					          <td>Parent 2 Mean:</td>
					          <td><input class="numberinput" type="text" name="TraitBParent2Mean" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_parent_B_mean ) ?>" /></td>  
				            <td>&nbsp;</td>
				          </tr>		            
                  
				          <tr>
					          <td>Trait Variance:</td>
					          <td><input class="numberinput" type="text" name="TraitAVariance" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_var ) ?>" /></td>
                    <td>&nbsp;</td>				    
					          <td>Trait Variance:</td>
					          <td><input class="numberinput" type="text" name="TraitBVariance" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_var ) ?>" /></td>		    
				            <td>&nbsp;</td>
				          </tr>		
                  
				          <tr>
					          <td>h<sup>2</sup>:</td>
                    <td><input class="numberinput" type="text" name="TraitAHeritability" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_h2 ) ?>" /></td>
                    <td>&nbsp;</td>				      
					          <td>h<sup>2</sup>:</td>
					          <td><input class="numberinput" type="text" name="TraitBHeritability" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_h2 ) ?>" /></td>			    
				            <td>&nbsp;</td>
				          </tr>		
                  
                  <tr>
					          <td width="115">Number of Genes:</td>
					          <td><input class="numberinput" type="text" name="TraitANumberOfGenes" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_number_of_genes ) ?>" /></td>
                    <td>&nbsp;</td>
					          <td>Number of Genes:</td>
					          <td><input class="numberinput" type="text" name="TraitBNumberOfGenes" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_number_of_genes ) ?>" /></td>
				            <td>&nbsp;</td>
				          </tr>     
      				    
				          <tr>
                    <td>Unit:</td>
                    <td><input class="textinput" type="text" name="TraitAUnit" value="<?= htmlspecialchars( $g_arr_problem_info->trait_A_unit ) ?>" /></td>
                    <td>&nbsp;</td>				      
                    <td>Unit:</td>
                    <td><input class="textinput" type="text" name="TraitBUnit" value="<?= htmlspecialchars( $g_arr_problem_info->trait_B_unit ) ?>" /></td>
				            <td>&nbsp;</td>
				          </tr>	
                
                </table>
        		  
		          </td>
		        </tr>
        	
	        </table>

        </td>
      </tr>

      <tr>
        <td>
          <input class="buttoninput" type="submit" value="Update" name="Command" onclick="concatDate(); return validateProblemForm(); return " />&nbsp;
          <input class="buttoninput" type="reset" value="Reset To Saved" name="Command" />
        </td>
      </tr>

      <tr>
        <td>

          <br /><br />
          
          <strong>The following students have been assigned to this course:</strong>

          <table class="listing" id="ListOfStudents">

            <tr>
              <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'StudentId[]' );" /></th>
              <th width="150">Student Number</th>
              <th width="150">Last Name</th>
              <th width="150">First Name</th>
              <th>Username</th>
            </tr>
            
<?php

	$res_students = $g_obj_assign_student_manager->view_students_assigned_to_problem( $g_int_problem_id );

	for ( $i = 0; $i < $g_obj_db->get_number_of_rows( $res_students ); ++$i )
	{
		$res_row = $g_obj_db->fetch( $res_students );

		echo( '<tr onclick="openStudentDetail( \'' . htmlspecialchars( $res_row->UserId, ENT_QUOTES ) . '\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">' . "\n" );
		echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="StudentId[]" value="' . htmlspecialchars( $res_row->UserId ) . '" /></td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->StudentNum ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->LastName ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->FirstName ) . '</td>' . "\n" );
		echo( '<td>' . htmlspecialchars( $res_row->UserId ) . '</td>' . "\n" );
		echo( '</tr>' . "\n" );
	}
	
?>
						
          </table>
          
          <input class="buttoninput" type="submit" name="Command" value="Drop Selected Students" />
        </td>
      </tr>

    </table>
    
    <br /><br /><br />
    
    <input type="hidden" name="StartDate" id="StartDate" />
    <input type="hidden" name="DueDate" id="DueDate" />
    
    <input class="buttonback" type="button" value="&lt;&nbsp;&nbsp;Back to Problem Listing" onclick="window.location='<?= $g_str_parent_page ?>';" />
    <input type="hidden" name="SerialId" id="SerialId" value="<?= $g_str_serial ?>" />
    
  </form>

</div>
<!-- End Content -->

<?php
}

require_once( '../includes/footer.inc.php' );

$g_obj_db->disconnect();

function verify_problem_exists()
{
	global $g_obj_problem_manager, $g_obj_db, $g_int_problem_id, $g_arr_problem_info;
	
	$res_problem = $g_obj_problem_manager->view_problem_details( $g_int_problem_id );
	
	if ( $g_obj_db->get_number_of_rows( $res_problem ) == 0 )
	{
		MessageHandler::add_message( MSG_ERROR, 'The problem does not exist' );
	}
	
	else
	{
		$g_arr_problem_info = $g_obj_db->fetch( $res_problem );
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
	global $g_int_problem_id, $g_obj_problem_manager;
	
	$str_problem_name = PageHandler::get_post_value( 'ProblemName' );
	$str_problem_description = PageHandler::get_post_value( 'ProblemDescription' );
	$str_Trait_A_name = PageHandler::get_post_value( 'TraitAName' );
	$str_Trait_B_name = PageHandler::get_post_value( 'TraitBName' );
	$str_Trait_A_unit = PageHandler::get_post_value( 'TraitAUnit' );
	$str_Trait_B_unit = PageHandler::get_post_value( 'TraitBUnit' );
	$int_Trait_A_number_of_genes = PageHandler::get_post_value( 'TraitANumberOfGenes' );
	$int_Trait_B_number_of_genes = PageHandler::get_post_value( 'TraitBNumberOfGenes' );
	$dbl_Trait_A_heritability = PageHandler::get_post_value( 'TraitAHeritability' );
	$dbl_Trait_B_heritability = PageHandler::get_post_value( 'TraitBHeritability' );
	$dbl_Trait_A_variance = PageHandler::get_post_value( 'TraitAVariance' );
	$dbl_Trait_B_variance = PageHandler::get_post_value( 'TraitBVariance' );
	$dbl_Trait_A_Parent_A_Mean = PageHandler::get_post_value( 'TraitAParent1Mean' );
	$dbl_Trait_A_Parent_B_Mean = PageHandler::get_post_value( 'TraitAParent2Mean' );
	$dbl_Trait_B_Parent_A_Mean = PageHandler::get_post_value( 'TraitBParent1Mean' );
	$dbl_Trait_B_Parent_B_Mean = PageHandler::get_post_value( 'TraitBParent2Mean' );
	$int_offspring_per_cross = PageHandler::get_post_value( 'OffspringPerCross' );
	$int_plants_generated = PageHandler::get_post_value( 'PlantsGenerated' );
	$int_plants_displayed = PageHandler::get_post_value( 'PlantsDisplayed' );
	$dbl_range_of_acceptance = PageHandler::get_post_value( 'RangeOfAcceptance' );
	$dat_start_date = PageHandler::get_post_value( 'StartDate' );
	$date_due_date  = PageHandler::get_post_value( 'DueDate' );
	
	if ( strlen( $str_problem_name ) == 0 || strlen( $str_problem_description ) == 0 || strlen( $str_Trait_A_name ) == 0 ||
			strlen( $str_Trait_B_name ) == 0 || strlen( $str_Trait_A_unit ) == 0 || strlen( $str_Trait_B_unit ) == 0 ||
			strlen( $int_Trait_A_number_of_genes ) == 0 || strlen( $int_Trait_B_number_of_genes ) == 0 || 
			strlen( $dbl_Trait_A_heritability ) == 0 || strlen( $dbl_Trait_B_heritability ) == 0 || 
			strlen( $dbl_Trait_A_variance ) == 0 || strlen( $dbl_Trait_B_variance ) == 0 || 
			strlen( $dbl_Trait_A_Parent_A_Mean ) == 0 || strlen( $dbl_Trait_A_Parent_B_Mean ) == 0 || 
			strlen( $dbl_Trait_B_Parent_A_Mean ) == 0 || strlen( $dbl_Trait_B_Parent_B_Mean ) == 0 ||
			strlen( $int_offspring_per_cross ) == 0 || strlen( $int_plants_generated ) == 0 || strlen( $int_plants_displayed ) == 0 ||
			strlen( $dbl_range_of_acceptance ) == 0 || strlen( $dat_start_date ) == 0 || strlen( $date_due_date ) == 0 )
	{
		MessageHandler::add_message( MSG_FAIL, 'Please enter the necessary information' );
		return;
	}
	
	if ( $g_obj_problem_manager->modify_problem( $g_int_problem_id,
														$str_problem_name,
														$str_problem_description,
														$str_Trait_A_name,
														$str_Trait_B_name,
														$str_Trait_A_unit,
														$str_Trait_B_unit,
														$int_Trait_A_number_of_genes,
														$int_Trait_B_number_of_genes,
														$dbl_Trait_A_heritability,
														$dbl_Trait_B_heritability,
														$dbl_Trait_A_variance,
														$dbl_Trait_B_variance,
														$dbl_Trait_A_Parent_A_Mean,
														$dbl_Trait_A_Parent_B_Mean,
														$dbl_Trait_B_Parent_A_Mean,
														$dbl_Trait_B_Parent_B_Mean,
														$int_offspring_per_cross,
														$int_plants_generated,
														$int_plants_displayed,
														$dbl_range_of_acceptance,
														$dat_start_date,
														$date_due_date ) )
	{
		MessageHandler::add_message( MSG_SUCCESS, 'Successfully updated Problem "' . $str_problem_name . '"' );
	}
	
	else
	{
		MessageHandler::add_message( MSG_FAIL, 'Failed to update Problem "' . $str_problem_name . '"' );
	}
}

?>
