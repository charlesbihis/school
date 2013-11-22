<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// require( '../includes/classes/db/solutionmanager.class.php' );
// $obj_solution_manager = new SolutionManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  if ( $command == 'Submit' )
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
    
    $handintime; // TODO: fetch time and pass it into db!	                      
    if ( $obj_solution_manager->add_solution(           $_POST['TraitANumberOfGenes'],	// $int_trait_A_number_of_genes
			                                            $_POST['TraitBNumberOfGenes'],	// $int_trait_B_number_of_genes
			                                            $_POST['TraitAHeritability'],	// $dbl_trait_A_h2
			                                            $_POST['TraitBHeritability'],	// $dbl_trait_B_h2
			                                            $_POST['TraitAVariance'],		// $dbl_trait_A_var
			                                            $_POST['TraitBVariance'],		// $dbl_trait_B_var
			                                            $_POST['TraitAParent1Mean'],	// $dbl_trait_A_parent_A_mean
			                                            $_POST['TraitBParent1Mean'],	// $dbl_trait_A_parent_B_mean
			                                            $_POST['TraitAParent2Mean'],	// $dbl_trait_B_parent_A_mean
			                                            $_POST['TraitBParent2Mean'],
			                                            $handintime
			                                            
			                                            ) )	// $dbl_trait_B_parent_B_mean
														
    
    
    {
		MessageHandler::add_message(MSG_SUCCESS, "Problem \"" . $_POST['ProblemName'] . "\" created successfully!");
    }  // if success
    else
    {
		MessageHandler::add_message(MSG_FAIL, "Error creating problem \"" . $_POST['ProblemName'] . "\"");
	}  // else failed
  }
}

$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];
$str_page_title = "Submit Solution";
$arr_scripts = array( 'submitsolution.js' );
//$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];

require ('../includes/header.inc.php' );

?>

        <!-- Start Content -->

        <p><a href="#">Back</a></p>
        
        <form method="post" id="SubmitSolutionForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
        
        <div class="centered">

        <table class="format">
	        <tr>
		        <td>
		        
              <table class="box">
                
                <tr>
                  <th>Submit Solution</th>
                </tr>
                <tr>
                  <td>        
                    
                    <table>    
					<tr>
					<td>Due Date: [date here]<br />
					Trait A NAME and Trait B NAME HERE
					</td></tr>
					
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
                        <td height="8"></td>
                      </tr>
                    </table>
                    
                    
                    
                  </td>
                </tr>
              </table>

					  </td>
          </tr>
          
          <tr><td>
                        <table class="box" style="width: 100%">
                <tr>
                  <th id="ThBTrait">Problem Description</th>
                </tr>
                <tr>
                  <td>        

          <textarea class="textareainput" 
												  name="ProblemDescription" 
												  id="ProblemDescription" 
												  cols="60" 
												  rows="10"></textarea>
          
          </td></tr></table>
          
          </td></tr>
	        <tr>
            <td colspan="3">

            
              <input class="buttoninput" type="submit" value="Submit" name="Command" onclick="return validateSubmitSolutionForm();"/>
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