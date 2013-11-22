<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

$int_problem_id = 72;//$_GET["problemid"];

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

 require( '../includes/classes/db/solutionmanager.class.php' );
 $obj_solution_manager = new SolutionManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] )  && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
    // would anything be posted to this page?
}

$res_student_solutions = $obj_solution_manager->view_student_solutions( $int_problem_id );

$str_page_title = "View Student Solutions";
// $arr_scripts = array( 'manageproblems.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];

require ( '../includes/header.inc.php' );

?>

<!-- Start Content -->

<table class="box">
  
  <tr>
    <th>Problem Answers</th>
  </tr>
  
  <tr>
    <td>
    
      <table class="format">

        <tr>
          <td width="150">&nbsp;</td>
          <td align="center"><strong>TRAIT A</strong></td>
          <td width="30">&nbsp;</td>
          <td align="center"><strong>TRAIT B</strong></td>
        </tr>
        
        <tr>
          <td><strong>Parent 1 Mean:</strong></td>
          <td>Blah</td>
          <td>&nbsp;</td>
          <td>Blah</td>
        </tr>
        
        <tr>
          <td><strong>Parent 2 Mean:</strong></td>
          <td>Blah</td>
          <td>&nbsp;</td>
          <td>Blah</td>
        </tr>
        
        <tr>
          <td><strong>Variance:</strong></td>
          <td>Blah</td>
          <td>&nbsp;</td>
          <td>Blah</td>
        </tr>
        
        <tr>
          <td><strong>Number of Genes:</strong></td>
          <td>Blah</td>
          <td>&nbsp;</td>
          <td>Blah</td>
        </tr>
        
      </table>
    
    </td>
  </tr>

</table>

<p>&nbsp;</p>

<table class="listing" id="listOfSolutions">
  
  <tr>
    <td>&nbsp;</td>
    <td colspan="4" align="center"><h4>Trait A</h4></td>
    <td width="45">&nbsp;</td>
    <td colspan="4" align="center"><h4>Trait B</h4></td>
    <td>&nbsp;</td>
  </tr>

  <tr>
    <th width="100">Student Number</th>
    
    <th width="75">Mean 1</th>
    <th width="75">Mean 2</th>
    <th width="75">Var</th>
    <th width="75"># Genes</th>
    
    <th>&nbsp;</th>
    
    <th width="75">Mean 1</th>
    <th width="75">Mean 2</th>
    <th width="75">Var</th>
    <th width="120"># Genes</th>
    
    <th>Handin Date</th>
  </tr>

  <tr>
    <td>12345678</td>

    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>
    
    <td>&nbsp;</td>
    
    <td>1</td>
    <td>1</td>
    <td>1</td>
    <td>1</td>

    <td>Mar 22, 06 12:00AM</td>
  </tr>  
  
  <?php
      
      for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_student_solutions ); ++$i )
      {
        $res_row = $obj_db->fetch( $res_student_solutions );
        
        echo( '<tr>' );
        echo( '<td>'.$res_row->StudentNum.'</td>' );
        echo( '<td>'.$res_row->LastName.'</td>' );
        echo( '<td>'.$res_row->FirstName.'</td>' );
        echo( '<td>'.$res_row->trait_A_parent_A_mean.'</td>' );
        echo( '<td>'.$res_row->trait_A_parent_B_mean.'</td>' );
        echo( '<td>'.$res_row->trait_A_var.'</td>' );
        echo( '<td>'.$res_row->trait_A_number_of_genes.'</td>' );
        echo( '<td>'.$res_row->trait_B_parent_A_mean.'</td>' );
        echo( '<td>'.$res_row->trait_B_parent_B_mean.'</td>' );
        echo( '<td>'.$res_row->trait_B_var.'</td>' );
        echo( '<td>'.$res_row->trait_B_number_of_genes.'</td>' );
        echo( '<td>'.$res_row->hand_in_date.'</td>' );
        
        echo( '</tr>' );
      }
          
      ?>
          
</table>

<!-- End Content -->

<?php

require_once( '../includes/footer.inc.php' );

$obj_db->disconnect();

?>
