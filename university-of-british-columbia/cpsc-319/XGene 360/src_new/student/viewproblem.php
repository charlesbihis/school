<?php

require ('../includes/global.inc.php');

if ( !isset( $_GET['problemid'] ) )
{
  PageHandler::redirect( './viewproblems.php' );
}

$int_problem_id = $_GET["problemid"];

$obj_db = new DBManager();

$obj_user = CookieHandler::get_user( $obj_db );

if ( $obj_user == null || $obj_user->int_privilege != UP_STUDENT)
{
	PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/problemmanager.class.php' );
$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );

$res_problem = $obj_problem_manager->view_problem_details( $int_problem_id );

require( '../includes/classes/db/generationmanager.class.php' );
$obj_generation_manager = new GenerationManager( $obj_user, $obj_db );

if ( $obj_db->get_number_of_rows( $res_problem ) == 0 )
{
	MessageHandler::add_message( MSG_ERROR, "The problem does not exist" );	
}

else
{
	$arr_problem_info = $obj_db->fetch( $res_problem );
	
	$res_number_of_generations = $obj_generation_manager->get_number_of_generations( $int_problem_id );
}

$str_page_title = "Generation History";

require( '../includes/header.inc.php' );

?>
        <div>
          <table border="0" cellpadding="0" cellspacing="0" class="box">
            <tr>
              <td>Student:</td>
              <td><?php echo( $obj_user->str_first_name.' '.$obj_user->str_last_name ); ?></td>
            </tr>
            <tr>
              <td>Problem:</td>
              <td><?php echo( $arr_problem_info->ProblemId ); ?></td>
            </tr>
            <tr>
              <td>Due Date:</td>
              <td><?php echo( $arr_problem_info ->DueDate ); ?></td>
            </tr>
          </table>
        </div>
        
        <!-- Start Content -->
        <table border="0" cellpadding="0" cellspacing="0" class="listing">
          <tr>
            <th>Iteration</th>
            <th>Parents</th>
            <th>Histograms</th>            
          </tr>
          
          <!-- Start Listing -->
          <?php
          
			$res_row = $obj_db->fetch( $res_number_of_generations );
			$int_number_of_generations = (int)$res_row->generation_count;
			
			for ( $i = 1; $i < $int_number_of_generations + 1; ++$i )
			{
				$res_genration = $obj_generation_manager->get_generation( $int_problem_id, $i );
				
				echo( '<tr>' );
				echo( '<td><a href="./viewgeneration.php?problemid='.$int_problem_id.'&amp;generationid='.$i.'">'.$i.'&nbsp;/&nbsp;'.$arr_problem_info->MaxCross.'</a></td>' );
				echo( '<td>something here</td>' );
				echo( '<td>something else here </td>' );
				echo( '</tr>' );
			}
			
          ?>          
          <!-- End Listing -->
          
        </table>
        <!-- End Content -->
<?php

require( '../includes/footer.inc.php' );

?>
