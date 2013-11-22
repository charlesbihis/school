<?php 

require_once( '../includes/global.inc.php' ); 

if ( !isset( $_GET['problemid'] ) )
{
	PageHandler::redirect( './manageproblems.php' );
}

$int_problem_id = $_GET["problemid"];

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT)
{
	PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/problemmanager.class.php' );

$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];
  
	switch ( $command )
	{
		case 'Submit':
		{
			if ( $obj_problem_manager->modify_problem( $int_problem_id,				// $int_problem_id
			                                            $_POST['ProblemName'],			// $str_problem_name
			                                            $_POST['ProblemDescription'],	// $str_problem_description
			                                            $_POST['Author'],				// $str_professor_id
			                                            $_POST['Course'],				// $int_course_id
			                                            $_POST['ATraitName'],			// $str_trait_A_name
			                                            $_POST['BTraitName'],			// $str_trait_B_name
			                                            $_POST['aunit'],				// $str_trait_A_unit
			                                            $_POST['bunit'],				// $str_trait_B_unit
			                                            $_POST['anumgenes'],			// $int_trait_A_number_of_genes
			                                            $_POST['bnumgenes'],			// $int_trait_B_number_of_genes
			                                            $_POST['ah2'],					// $dbl_trait_A_h2
			                                            $_POST['bh2'],					// $dbl_trait_B_h2
			                                            $_POST['ap1sd'],				// $dbl_trait_A_var
			                                            $_POST['bp1sd'],				// $dbl_trait_B_var
			                                            $_POST['ap1mean'],				// $dbl_trait_A_parent_A_mean
			                                            $_POST['ap2mean'],				// $dbl_trait_A_parent_B_mean
			                                            $_POST['bp1mean'],				// $dbl_trait_B_parent_A_mean
			                                            $_POST['bp2mean'],				// $dbl_trait_B_parent_B_mean
			                                            $_POST['OffspringPerCross'],	// $int_number_of_progeny_per_cross
			                                            $_POST['PlantsGenerated'],		// $int_max_cross
			                                            $_POST['PlantsDisplayed'],		// $int_number_of_displayed_plants
			                                            $_POST['RangeOfAcceptance'],	// $dbl_range_of_acceptance
			                                            $_POST['dat_start_date'],						// $dat_start_date
			                                            $_POST['dat_due_date'] ) )					// $dat_due_date
		    {
				MessageHandler::add_message(MSG_SUCCESS, "Problem \"" . $_POST['ProblemName'] . "\" modified successfully!" );
			}  // if success
			else
			{
				MessageHandler::add_message(MSG_FAIL, "Error modifying problem \"" . $_POST['ProblemName'] . "\"" );
			}  // else failed
		}  // case 'Submit'
		
        break;
	}  // switch statement
}  // if statement

$res_problem = $obj_problem_manager->view_problem_details( $int_problem_id );

$bln_invalidProblem = false;

if ( $obj_db->get_number_of_rows( $res_problem ) == 0 )
{
	// TODO: add error handler here
	$bln_invalidProblem = true;
}
else
{
	$arr_problem_info = $obj_db->fetch( $res_problem );
}

$str_page_title = "View Problem";
$arr_scripts = array( 'manageproblem.js' );
$arr_nav_links = $g_arr_nav_links[UP_ADMINISTRATOR];

require_once( '../includes/header.inc.php' );

?>

<!-- START CONTENT -->
<script language="javascript">

displayTextFromInput = function( objIdOrElement, objIdOrElement2, strPrepend )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  var objElement2 = xgene360_cu.Element( objIdOrElement2 );
  var strNewName = strPrepend;
  
  if( objElement.type == 'text' )
  {
    strNewName += objElement.value;
    objElement2.innerHTML = strNewName; 
  } 
}
  
</script>

	<!-- Start Content -->

	<p><a href="javascript: history.go(-1)">Back</a></p>
        
	<div> 
	<form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">

	<table class="format">
		<tr>
			<td>  
				<table class="box">
					<tr>
						<th>Modify Problem, id=<?php echo( $int_problem_id ); ?></th>
					</tr>
					<tr>
						<td>        
							<table>    
								<tr>
									<td width="130">Problem Name:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->problem_name ); } ?>" 
									           class="longtextinput" 
									           type="text" 
									           name="ProblemName" 
									           id="ProblemName" 
					                           onkeyup="displayTextFromInput( 'ATrait', 'ThATrait', 'Trait - ' );" />
									</td>
								</tr>
								<tr>
									<td width="130">Trait A:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_name ); } ?>" 
											   class="longtextinput" 
											   type="text" 
											   name="ATraitName" 
											   id="ATraitName" 
											   onkeyup="displayTextFromInput( 'ATrait', 'ThATrait', 'Trait - ' );" />
									</td>
								</tr>
								<tr>
									<td>Trait B:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_name ); } ?>" 
											   class="longtextinput" 
											   type="text" 
											   name="BTraitName" 
											   id="BTraitName" 
											   onkeyup="displayTextFromInput( 'BTrait', 'ThBTrait', 'Trait - ' );" />
									</td>
								</tr>			
								<tr>
									<td style="vertical-align: top;">Problem Description:</td>
									<td><textarea class="textareainput" 
												  name="ProblemDescription" 
												  id="ProblemDescription" 
												  cols="60" 
												  rows="10"><?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->problem_desc ); } ?></textarea>
									</td>
								</tr>
								<tr>
									<td>Course:</td>
									<td>
										<!-- course selection -->
										<select name="Course" id="Course">
											<?php
												require( '../includes/classes/db/CourseManager.class.php' );
												$obj_course_manager = new CourseManager( $obj_user, $obj_db );
												$res_courses = $obj_course_manager->view_courses();
					                
												for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
												{
													$res_row2 = $obj_db->fetch( $res_courses );
													if ($res_row2->CourseId == $arr_problem_info->CourseId)		// if current selected course as default option
														echo( '<option selected value="'.$res_row2->CourseId.'">'.$res_row2->Name.'</option>'."\n" );
													else
														echo( '<option value="'.$res_row2->CourseId.'">'.$res_row2->Name.'</option>'."\n" );
												}  // for loop
											?>
										</select>
									</td>
								</tr>
								<tr>
									<td>Author:</td>
									<td>
										<!-- problem owner selection -->
										<select name="Author" id="Author">
											<?php
												require( '../includes/classes/db/ProfessorManager.class.php' );
												$obj_professor_manager = new ProfessorManager( $obj_user, $obj_db );
												$res_professors = $obj_professor_manager->view_professors();

												for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_professors ); ++$i )
												{
													$res_row2 = $obj_db->fetch( $res_professors );
													if ($res_row2->UserId == $arr_problem_info->UserId)		// if current selected course as default option
														echo( '<option selected value="'.$res_row2->UserId.'">'.$res_row2->LastName.',&nbsp'.$res_row2->FirstName.'</option>'."\n" );
													else
														echo( '<option value="'.$res_row2->UserId.'">'.$res_row2->LastName.',&nbsp'.$res_row2->FirstName.'</option>'."\n" );
												}
											?>
										</select>
										*NOTE: changing author means previous author may no longer have access to problem
									</td>
								</tr>
				              <tr>
					              <td>Start Date:</td>
					              <td>
					              
					              <?php if ( isset( $arr_problem_info ) )  // To grab the pieces of date/time from DB. - JW
					              { 
					                $startdate = $arr_problem_info->start_date;

    								preg_match('/(\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})/',$startdate,$pieces);
									// echo("Y$pieces[1], M$pieces[2], D$pieces[3],H$pieces[4], m$pieces[5], s$pieces[6]");
								  }
									?> 
					              
			              
						              <select name="StartDateMonth" id="StartDateMonth">

        	                  <?php 
              	                             	  
        	                  for ( $i = 0; $i < 12; $i++ ) 
        	                  {
        	                    if ( $i == ( $pieces[2] - 1 ) )
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
						              &nbsp;
						              <select name="StartDateDay" id="StartDateDay">
              	            
        	                  <?php 
                        	  
        	                  for ( $i = 1; $i <= 31; $i++ ) 
        	                  {
        	                    if ( $i == $pieces[3] )
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
						              &nbsp;
						              <select name="StartDateYear" id="StartDateYear">
              	            
        	                  <?php 
              	            
        	                  $tmp_int_start_year = date( 'Y' )-5;
                        	  
        	                  for ( $i = 0; $i <= 10; $i++ ) 
        	                  {
        	                    if ( $tmp_int_start_year == $pieces[1] )
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
						              &nbsp;&nbsp;&nbsp;
						              <select name="StartDateHour" id="StartDateHour">
              	            
        	                  <?php 
                        	  
        	                  for ( $i = 1; $i <= 12; $i++ ) 
        	                  {
        						if ($pieces[4] > 12) {$pieces[4] = $pieces[4]-12;} // minus 12 if PM
        						
        	                    if ( $i == $pieces[4] || (($pieces[4] == 0) && $i == 12) )
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
						              :
						              <select name="StartDateMinute" id="StartDateMinute">
              	            
        	                  <?php 
                        	  
        	                  for( $i = 0; $i <= 59; $i++ ) 
        	                  {
        	                    if ( $i == $pieces[5] )
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
                        	  
        	                  if( $pieces[4] < 12 )
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
				              
				              
				              					              <?php if ( isset( $arr_problem_info ) ) 
					              { 
					                $enddate = $arr_problem_info->due_date;

    								preg_match('/(\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})/',$enddate,$pieces);
									echo("Y$pieces[1], M$pieces[2], D$pieces[3],H$pieces[4], m$pieces[5], s$pieces[6]");
								  }
									?> 
									
									
				              
				              
					              <td>End Date:</td>
					              <td>
						              <select name="EndDateMonth" id="EndDateMonth">

        	                  <?php 
              	                             	  
        	                  for( $i = 0; $i < 12; $i++ ) 
        	                  {
        	                    if ( $i == ( $pieces[2] - 1 ) )
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
						              &nbsp;
						              <select name="EndDateDay" id="EndDateDay">
              	            
        	                  <?php 
                        	  
        	                  for( $i = 1; $i <= 31; $i++ ) 
        	                  {
        	                    if ( $i == $pieces[3] )
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
						              &nbsp;
						              <select name="EndDateYear" id="EndDateYear">
              	            
        	                  <?php 
              	            
        	                  $tmp_int_end_year = date( 'Y' ) - 5;
                        	  
        	                  for( $i = 0; $i <= 10; $i++ ) 
        	                  {
        	                    if ( $tmp_int_end_year == $pieces[1] )
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
						              &nbsp;&nbsp;&nbsp;
						              <select name="EndDateHour" id="EndDateHour">
              	            
        	                  <?php 
                        	  
        	                  for( $i = 1; $i <= 12; $i++ ) 
        	                  {
        						if ($pieces[4] > 12) {$pieces[4] = $pieces[4] - 12; } // subtract 12 from 24 hour standard
        						
        	                    if ( $i == $pieces[4] || (($pieces[4] == 0) && $i == 12) )
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
						              :
						              <select name="EndDateMinute" id="EndDateMinute">
              	            
        	                  <?php 
                        	  
        	                  for( $i = 0; $i <= 59; $i++ ) 
        	                  {
        	                    if ( $i == $pieces[5] )
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
                        	  
        	                  if( $pieces[4] < 12 )
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
									<td>Maximum Number of Cross:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->max_cross ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="PlantsGenerated" />&nbsp;plants
									</td>
								</tr>
								<tr>
									<td>Offspring per Cross:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->number_of_progeny_per_cross ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="OffspringPerCross" />&nbsp;plants
									</td>
								</tr>
								<tr>
									<td>Displayed Plants per Cross:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->number_of_displayed_plants ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="PlantsDisplayed" />&nbsp;plants
									</td>
								</tr>
								<tr>
									<td>Range of Acceptance:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->range_of_acceptance ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="RangeOfAcceptance" />&nbsp;%
									</td>
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
				<table class="box" style="width: 100%">
					<tr>
						<th id="ThATrait">Trait - <?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_name ); } ?></th>
					</tr>
					<tr>
						<td>        
							<table>
								<tr>
									<td width = "130">Number of Genes:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_number_of_genes ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="anumgenes" 
											   maxlen="3" />
									</td>
								</tr>
								<tr>
									<td>h<sup>2</sup>:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_h2 ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="ah2" />
									</td>
								</tr>
								<tr>
									<td>Parent 1 Mean:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_parent_A_mean ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="ap1mean" />
									</td>
								</tr>
								<tr>
									<td>Parent 2 Mean:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_parent_B_mean ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="ap2mean" />
									</td>
								</tr>			
								<tr>
									<td>Trait Variance:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_var ); } ?>" 
											   class="numberinput" 
											   type="text" 
											   name="ap1sd" />
									</td>
								</tr>
					<!--
								<tr>
									<td>Parent 2 SD:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->parent_B_trait_A_SD ); } ?>" class="numberinput" type="text" name="ap2sd" /></td>
								</tr> 
								<tr>
									<td>Base Value:</td>
									<td><input class="numberinput" type="text" name="abasevalue" /></td>
								</tr>
					-->
								<tr>
									<td>Unit:</td>
									<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_A_unit ); } ?>" 
											   class="textinput" 
											   type="text" 
											   name="aunit" />
									</td>
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
			<table class="box" style="width: 100%">
				<tr>
					<th id="ThBTrait">Trait - <?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_name ); } ?></th>
				</tr>
				<tr>
					<td>        
						<table>
							<tr>
								<td width="130">Number of Genes:</td>
								<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_number_of_genes ); } ?>" class="numberinput" type="text" name="bnumgenes"  maxlen="3" /></td>
							</tr>
							<tr>
								<td>h<sup>2</sup>:</td>
								<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_h2 ); } ?>" class="numberinput" type="text" name="bh2" /></td>
							</tr>
							<tr>
								<td width="130">Parent 1 Mean:</td>
								<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_parent_A_mean ); } ?>" class="numberinput" type="text" name="bp1mean" /></td>
							</tr>
							<tr>
								<td>Parent 2 Mean:</td>
								<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_parent_B_mean ); } ?>" class="numberinput" type="text" name="bp2mean" /></td>
							</tr>			
							<tr>
								<td>Trait Variance:</td>
								<td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_var ); } ?>" class="numberinput" type="text" name="bp1sd" /></td>
							</tr>
							
							
							
							
							
<!--				              <tr>
					              <td>Parent 2 SD:</td>
					              <td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->parent_B_trait_B_SD ); } ?>" class="numberinput" type="text" name="bp2sd" /></td>
				              </tr>
				              <tr>
					              <td>Base Value:</td>
					              <td><input class="numberinput" type="text" name="bbasevalue" /></td>
				              </tr> -->
				              <tr>
					              <td>Unit:</td>
					              <td><input value="<?php if ( isset( $arr_problem_info ) ) { echo( $arr_problem_info->trait_B_unit ); } ?>" class="textinput" type="text" name="bunit" /></td>
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
	        <tr>
            <td colspan="3">
            
            <input type="hidden" name="dat_start_date" id="dat_start_date" value="">
            <input type="hidden" name="dat_due_date" id="dat_due_date" value="">
            <script language="Javascript">
            
            function concatDate() {
	var objstartDateDay = xgene360_cu.Element( 'StartDateDay' );
	var sday = objstartDateDay.value;

	var objstartDateMonth = xgene360_cu.Element( 'StartDateMonth' );
	var smonth = objstartDateMonth.value;

	var objstartDateYear = xgene360_cu.Element( 'StartDateYear' );
	var syear = objstartDateYear.value;

	var objstartDateMinute = xgene360_cu.Element( 'StartDateMinute' );
	var smin = objstartDateMinute.value;

	var objstartDateHour = xgene360_cu.Element( 'StartDateHour' );
	var shour = parseInt(objstartDateHour.value);

	var objstartDateAPM = xgene360_cu.Element( 'StartDateAPM' );
	var sapm = objstartDateAPM.value;

	var objendDateDay = xgene360_cu.Element( 'EndDateDay' );
	var eday = objendDateDay.value;

	var objendDateMonth = xgene360_cu.Element( 'EndDateMonth' );
	var emonth = objendDateMonth.value;    

	var objendDateYear = xgene360_cu.Element( 'EndDateYear' );
	var eyear = objendDateYear.value;

	var objEndDateMinute = xgene360_cu.Element( 'EndDateMinute' );
	var emin = objEndDateMinute.value;

	var objEndDateHour = xgene360_cu.Element( 'EndDateHour' );
	var ehour = parseInt(objEndDateHour.value);

	var objEndDateAPM = xgene360_cu.Element( 'EndDateAPM' );
	var eapm = objEndDateAPM.value;

	var objFullStartDate = xgene360_cu.Element( 'dat_start_date' );
	var objFullDueDate = xgene360_cu.Element( 'dat_due_date' );
	<!-- format: 2006-03-21 00:00:00 -->
	if (sapm == 'PM') {if (shour != 12) {shour = shour + 12;}}
	if (eapm == 'PM') {if (ehour != 12) {ehour = ehour + 12;}}

	if (sapm == 'AM') {if (shour == 12) {shour = 0;}}
	if (eapm == 'AM') {if (ehour == 12) {ehour = 0;}}
	
	objFullStartDate.value = syear+'-'+smonth+'-'+sday+' '+shour.toString()+':'+smin+':00';
	objFullDueDate.value = eyear+'-'+emonth+'-'+eday+' '+ehour.toString()+':'+emin+':00';
	alert (objFullStartDate.value +'\n'+ objFullDueDate.value);
	return true;
	}
            </script>
            
            
              <input class="buttoninput" type="submit" value="Submit" name="Command" onclick="concatDate(); return validateProblemForm(); return " />&nbsp;
              <input class="buttoninput" type="reset" value="Reset" name="Command" />
		        </td>
	        </tr>
	        
        </table>
		<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
        </form>
        </div>

    This problem is assigned to the following students: (is this right?)
	
	<table class="listing" id="listOfStudents">
      
      <tr>
        <th width="50"><input type="checkbox" id="UserIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'SelectedStudentId[]' );" /></th>
        <th width="150">Student Number</th>
        <th width="150">Last Name</th>
        <th width="150">First Name</th>
        <th>Username</th>
      </tr>

      <?php
      
      require( '../includes/classes/db/assignproblemmanager.class.php' );
	  $obj_student_manager = new AssignProblemManager( $obj_user, $obj_db );
	  $res_students = $obj_student_manager->view_students_assigned_to_problem( $int_problem_id );
     
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_students ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_students );
        
        echo( '<tr onclick="openStudentDetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
        echo( '<td onmouseover="xgene360_cu.stopPropagation( event );" onclick="xgene360_cu.stopPropagation( event );"><input type="checkbox" name="SelectedStudentId[]" value="'.$res_row->UserId.'" /></td>' );
        echo( '<td>'.$res_row->StudentNum.'</td>' );
        echo( '<td>'.$res_row->LastName.'</td>' );
        echo( '<td>'.$res_row->FirstName.'</td>' );
        echo( '<td>'.$res_row->UserId.'</td>' );
        echo( '</tr>' );
      }
          
      ?>
              
    </table>


<!-- END CONTENT -->

<?php

require_once( '../includes/footer.inc.php' );

$obj_db->disconnect();

?>
