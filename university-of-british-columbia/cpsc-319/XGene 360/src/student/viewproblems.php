<?php

require( '../includes/global.inc.php' );

$obj_db = new DBManager();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege != UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/problemmanager.class.php' );

$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
  {
 
    
  }
}

$res_problems = $obj_problem_manager->view_problems();

$str_page_title = "View Problems";
$arr_scripts = array( 'manageprofessors.js' );
$arr_nav_links = $g_arr_nav_links[$obj_user->int_privilege];

require ( '../includes/header.inc.php' );

?>
        <!-- Start Content -->

        <table border="0" cellpadding="0" cellspacing="0" class="listing">
          <tr>
            <th>Problem</th>
            <th>Course</th>
            <th>Start Date</th>
            <th>Due Date</th>
            <th>Recent Iteration</th>
            
          </tr>
          
          <!-- Start Listing -->
          <?php
          
              for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_problems ); ++$i )
              {
                $res_row = $obj_db->fetch( $res_problems );
                
                echo( '<tr onclick="openProblemDetail( \''.$res_row->problem_id.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
                echo( '<td>'.$res_row->problem_name.'</td>'."\n" );
                echo( '<td>'.$res_row->Name.'</td>'."\n" );
                echo( '<td>'.$res_row->start_date.'</td>'."\n" );
                echo( '<td>'.$res_row->due_date.'</td>'."\n" );
                echo( '<td>'.$res_row->iter_val.'/'.$res_row->max_cross.'</td>'."\n" );
                echo( '</tr>'."\n" );
              }
              
          ?>  
        </table>

        <!-- End Content -->
<?php

require( '../includes/footer.inc.php' );

?>
