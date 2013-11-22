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
require( '../includes/classes/db/generationmanager.class.php' );
require( '../includes/classes/db/problemmanager.class.php' );

$obj_course_manager = new CourseManager( $obj_user, $obj_db );
$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );
$res_courses = $obj_course_manager->view_courses();


if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  if ( $command == 'Create' )
  {
    // create a new problem
    
    /* function add_problem( $str_problem_name, $str_problem_desc, $int_course_id, $str_trait_A_name, 
	                      $str_trait_B_name, $str_trait_A_unit, $str_trait_B_unit, 
	                      $int_trait_A_number_of_genes, $int_trait_B_number_of_genes, $dbl_trait_A_h2,
	                      $dbl_trait_B_h2, $dbl_trait_A_var, $dbl_trait_B_var, $dbl_trait_A_parent_A_mean,
	                      $dbl_trait_A_parent_B_mean, $dbl_trait_B_parent_A_mean, $dbl_trait_B_parent_B_mean,
	                      $int_number_of_progeny_per_cross, $int_max_cross, $int_number_of_displayed_plants,
	                      $dbl_range_of_acceptance, $dat_start_date, $dat_due_date )
	                      
	                      THE ADD PROBLEM IN DB
	                      */
    if ( $obj_problem_manager->add_problem(            $_POST['ProblemName'],			// $str_problem_name
			                                            $_POST['ProblemDescription'],	// $str_problem_description
			                                            // $_POST['Author'],			// $str_professor_id
			                                            $_POST['Courses'],				// $int_course_id
			                                            $_POST['ATraitName'],			// $str_trait_A_name
			                                            $_POST['BTraitName'],			// $str_trait_B_name
			                                            $_POST['TraitAUnit'],			// $str_trait_A_unit
			                                            $_POST['TraitBUnit'],			// $str_trait_B_unit
			                                            $_POST['TraitANumberOfGenes'],	// $int_trait_A_number_of_genes
			                                            $_POST['TraitBNumberOfGenes'],	// $int_trait_B_number_of_genes
			                                            $_POST['TraitAHeritability'],	// $dbl_trait_A_h2
			                                            $_POST['TraitBHeritability'],	// $dbl_trait_B_h2
			                                            $_POST['TraitAVariance'],		// $dbl_trait_A_var
			                                            $_POST['TraitBVariance'],		// $dbl_trait_B_var
			                                            $_POST['TraitAParent1Mean'],	// $dbl_trait_A_parent_A_mean
			                                            $_POST['TraitAParent2Mean'],	// $dbl_trait_B_parent_A_mean
			                                            $_POST['TraitBParent1Mean'],	// $dbl_trait_A_parent_B_mean
			                                            $_POST['TraitBParent2Mean'],	// $dbl_trait_B_parent_B_mean
			                                            $_POST['OffspringPerCross'],	// $int_number_of_progeny_per_cross
			                                            $_POST['MaxCross'],				// $int_max_cross
			                                            $_POST['PlantsDisplayed'],		// $int_number_of_displayed_plants
			                                            $_POST['RangeOfAcceptance'],	// $dbl_range_of_acceptance
			                                            $_POST['dat_start_date'],		// $dat_start_date
			                                            $_POST['dat_due_date'] ) )		// $dat_due_date
    
    
    {
		MessageHandler::add_message(MSG_SUCCESS, "Problem \"" . $_POST['ProblemName'] . "\" created successfully!");
    }  // if success
    else
    {
		MessageHandler::add_message(MSG_FAIL, "Error creating problem \"" . $_POST['ProblemName'] . "\"");
	}  // else failed
  }
}

// $obj_problem_manager = new problemmanager( $obj_user, $obj_db );
$res_problems = $obj_problem_manager->view_problems();
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_page_title = "Create Problem";
$arr_scripts = array( 'createproblem.js' );
//$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];

require ('../includes/header.inc.php' );

?>

        <!-- Start Content -->

        <p><a href="manageproblems.php">Back</a></p>
        
        <form method="post" id="CreateProblemForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
        
        <div class="centered">

        <table class="format">
	        <tr>
		        <td>
		        
              <table class="box">
                
                <tr>
                  <th>General</th>
                </tr>
                <tr>
                  <td>        
                    
                    <table>    
				              <tr>
					              <td width="130">Problem Name:</td>
					              <td><input class="longtextinput" type="text" name="ProblemName" id="ProblemName" /></td>
				              </tr>
				              
				              <tr>
					              <td width="130">Trait A:</td>
					              <td><input class="longtextinput" type="text" name="ATraitName" id="ATraitName" /></td>
				              </tr>
				              <tr>
					              <td>Trait B:</td>
					              <td><input class="longtextinput" type="text" name="BTraitName" id="BTraitName" /></td>
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
                          <select name="Courses" id="Courses">
                            <?php
                            
                              for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_courses ); ++$i )
                              {
                                $res_row = $obj_db->fetch( $res_courses );
                                
                                echo( '<option value="'.$res_row->CourseId.'">'.$res_row->Name.'</option>'."\n" );
                              }
                              
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
												if ($res_row2->UserId == $arr_problem_info->prof_id)		// if current selected course as default option
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
						              &nbsp;
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
						              &nbsp;
						              <select name="StartDateYear" id="StartDateYear">
              	            
        	                  <?php 
              	            
        	                  $tmp_int_start_year = date( 'Y' )-5;
                        	  
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
						              &nbsp;&nbsp;&nbsp;
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
                            
						              </select>		
						              :
						              <select name="StartDateMinute" id="StartDateMinute">
              	            
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
					              <td>End Date:</td>
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
						              &nbsp;
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
						              &nbsp;
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
						              &nbsp;&nbsp;&nbsp;
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
                            
						              </select>		
						              :
						              <select name="EndDateMinute" id="EndDateMinute">
              	            
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
					              <td>Maximum Number of Cross:</td>
					              <td><input class="numberinput" type="text" name="MaxCross" id="MaxCross" />&nbsp;</td>
				              </tr>
				              <tr>
					              <td>Offspring per Cross:</td>
					              <td><input class="numberinput" type="text" name="OffspringPerCross" id="OffspringPerCross" />&nbsp;plants</td>
				              </tr>
				              <tr>
					              <td>Displayed Plants per Cross:</td>
					              <td><input class="numberinput" type="text" name="PlantsDisplayed" id="PlantsDisplayed" />&nbsp;plants</td>
				              </tr>
				              <tr>
					              <td>Range of Acceptance:</td>
					              <td><input class="numberinput" type="text" name="RangeOfAcceptance" id="RangeOfAcceptance" />&nbsp;%</td>
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
                  <th id="ThATrait">Trait A</th>
                </tr>
                <tr>
                  <td>        
                    
                    <table>
                      <tr>
					              <td>Number of Genes:</td>
					              <td><input class="numberinput" type="text" name="TraitANumberOfGenes" id="TraitANumberOfGenes" /></td>
				              </tr>
				              <tr>
					              <td>h<sup>2</sup>:</td>
					              <td><input class="numberinput" type="text" name="TraitAHeritability" id="TraitAHeritability" /></td>
				              </tr>
				              <tr>
					              <td>Parent 1 Mean:</td>
					              <td><input class="numberinput" type="text" name="TraitAParent1Mean" id="TraitAParent1Mean" /></td>
				              </tr>
				              <tr>
					              <td>Parent 2 Mean:</td>
					              <td><input class="numberinput" type="text" name="TraitAParent2Mean" id="TraitAParent2Mean" /></td>
				              </tr>			
				              <tr>
					              <td>Trait Variance:</td>
					              <td><input class="numberinput" type="text" name="TraitAVariance" id="TraitAVariance" /></td>
				              </tr>
				              <tr>
					              <td>Base Value:</td>
					              <td><input class="numberinput" type="text" name="TraitABaseValue" id="TraitABaseValue" /></td>
				              </tr>
				              <tr>
					              <td>Unit:</td>
					              <td><input class="textinput" type="text" name="TraitAUnit" id="TraitAUnit" /></td>
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
                  <th id="ThBTrait">Trait B</th>
                </tr>
                <tr>
                  <td>        
                    
                    <table>
                      <tr>
					              <td>Number of Genes:</td>
					              <td><input class="numberinput" type="text" name="TraitBNumberOfGenes" id="TraitBNumberOfGenes" /></td>
				              </tr>
				              <tr>
					              <td>h<sup>2</sup>:</td>
					              <td><input class="numberinput" type="text" name="TraitBHeritability" id="TraitBHeritability" /></td>
				              </tr>
				              <tr>
					              <td>Parent 1 Mean:</td>
					              <td><input class="numberinput" type="text" name="TraitBParent1Mean" id="TraitBParent1Mean" /></td>
				              </tr>
				              <tr>
					              <td>Parent 2 Mean:</td>
					              <td><input class="numberinput" type="text" name="TraitBParent2Mean" id="TraitBParent2Mean" /></td>
				              </tr>			
				              <tr>
					              <td>Trait Variance:</td>
					              <td><input class="numberinput" type="text" name="TraitBVariance" id="TraitBVariance" /></td>
				              </tr>
				              <tr>
					              <td>Base Value:</td>
					              <td><input class="numberinput" type="text" name="TraitBBaseValue" id="TraitBBaseValue" /></td>
				              </tr>
				              <tr>
					              <td>Unit:</td>
					              <td><input class="textinput" type="text" name="TraitBUnit" id="TraitBUnit" /></td>
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
				if (sapm == 'PM') {shour = shour + 12;}
				if (eapm == 'PM') {ehour = ehour + 12;}
				
				objFullStartDate.value = syear+'-'+smonth+'-'+sday+' '+shour.toString()+':'+smin+':00';
				objFullDueDate.value = eyear+'-'+emonth+'-'+eday+' '+ehour.toString()+':'+emin+':00';
				<!-- alert (objFullStartDate.value +'\n'+ objFullDueDate.value); -->
				return true;
		    }
            </script>
            
              <input class="buttoninput" type="submit" value="Create" name="Command" onclick="concatDate(); return validateCreateProblemForm();"/>
              &nbsp;<input class="buttoninput" type="reset" value="Reset" name="Command" />
		        </td>
	        </tr>
	        
        </table>
        </div>
        
<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
        </form>

        <!-- End Content -->

<?php

require( '../includes/footer.inc.php' );

?>