<?php 

require_once('../includes/global.inc.php'); 

if ( !isset( $_GET['problemid'] ) )
{
	PageHandler::redirect( 'viewproblems.php' );
}

$int_problem_id = $_GET['problemid'];

if ( !isset( $_GET['generationid'] ) )
{
	$int_generation_id = 0;
}

else
{
	$int_generation_id = $_GET['generationid'];
}

$isPlantsImageLoaded = ( CookieHandler::get_cookie_value( 'PlantsImageLoaded' ) == null );
CookieHandler::set_cookie_value( 'PlantsImageLoaded', true );

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege != UP_STUDENT )
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/problemmanager.class.php' );
$obj_problem_manager = new ProblemManager( $obj_user, $obj_db );

require( '../includes/classes/db/generationmanager.class.php' );
$obj_generation_manager = new GenerationManager( $obj_user, $obj_db );

$res_problem = $obj_problem_manager->view_problem_details( $int_problem_id );

if ( $obj_db->get_number_of_rows( $res_problem ) == 0 )
{
	MessageHandler::add_message( MSG_ERROR, "The problem does not exist" );	
}

else
{
	$arr_problem_info = $obj_db->fetch( $res_problem );
	
	$res_number_of_generations = $obj_generation_manager->get_number_of_generations( $int_problem_id );
}

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
	$command = $_POST['Command'];
  
	switch ( $command )
	{
		case 'Cross':
		{
			if ( isset( $_POST['SelectedPlants'] ) )
			{
				$str_selected_plants = $_POST['SelectedPlants'];
				
				$arr_plant_ids = split( ';', $str_selected_plants );
				
				// save the parents for later use
				$obj_generation_manager->set_parents( $int_problem_id, $arr_plant_ids );
				
				// retrieve the data regarding the parents
				$arr_parents_genotypes = $obj_generation_manager->get_parents_genotypes( $int_problem_id, $arr_plant_ids );
				
				// create all parent plants
				$arr_parent_plants = array();
				
				for ( $i = 0; $i < count( $arr_parents_genotypes ); ++$i )
				{
					$obj_plant = new Plant;
					$obj_plant->arr_gene[0] = new Gene;
					$obj_plant->arr_gene[1] = new Gene;
					
					$obj_plant->arr_gene[0]->decrypt( $arr_parents_genotypes[$i][0] );
					$obj_plant->arr_gene[1]->decrypt( $arr_parents_genotypes[$i][1] );
					
					array_push( $arr_parent_plants, $obj_plant );
				}
				
				$arr_new_generation = Simulation::cross_plants( $arr_parent_plants, (int)$arr_problem_info->number_of_displayed_plants );
				
				$obj_trait_A = $obj_problem_manager->create_trait( $arr_problem_info->trait_A_name, (int)$arr_problem_info->trait_A_number_of_genes, 
																		(double)$arr_problem_info->trait_A_parent_A_mean, (double)$arr_problem_info->trait_A_parent_B_mean );
				$obj_trait_B = $obj_problem_manager->create_trait( $arr_problem_info->trait_B_name, (int)$arr_problem_info->trait_B_number_of_genes, 
																		(double)$arr_problem_info->trait_B_parent_A_mean, (double)$arr_problem_info->trait_B_parent_B_mean );
				
				
				$res_number_of_generations = $obj_generation_manager->get_number_of_generations( $int_problem_id );
				$res_row = $obj_db->fetch( $res_number_of_generations );
				
				$int_generation_num = (int)$res_row->generation_count + 1;
			  
				$obj_generation_manager->set_array_generation( $int_problem_id, $obj_trait_A, $obj_trait_B, $arr_new_generation, $int_generation_num );
				
				$int_generation_id = $int_generation_num;
			}
			
			else
			{
				MessageHandler::add_message( MSG_ERROR, 'Please select at least one plant' );
			}
		}	

		break;
		
		default:
		{
			MessageHandler::add_message( MSG_ERROR, "Unknown Command" );
		}
		
		break;
	}
}

$str_page_title = "View Generation";
$arr_nav_links = $g_arr_nav_links[UP_STUDENT];
$arr_styles = array( 'histogram.css' );
$arr_scripts = array( 'histogram.js', 'plant.js', 'viewgeneration.js' );

$str_script_block = "
 
  var objPlants = new Array();
";

// query for number of generations we have
$res_number_of_generations = $obj_generation_manager->get_number_of_generations( $int_problem_id );
$res_row = $obj_db->fetch( $res_number_of_generations );
$int_number_of_generations = $res_row->generation_count;

// get all the generations
for ( $i = 1; $i < $int_number_of_generations + 1; ++$i )
{
	$res_generation = $obj_generation_manager->get_generation( $int_problem_id, $i );
	
	$str_script_block = $str_script_block . ' objPlants[' . $i . '] = new Array(';
	
	for ( $j = 0; $j < $obj_db->get_number_of_rows( $res_generation ); ++$j )
	{
		$res_plant = $obj_db->fetch( $res_generation );
		$str_script_block = $str_script_block . 'new xgene360_plant( \'' . $res_plant->plant_id . '\', ' . $res_plant->value_trait_A . ', ' . $res_plant->value_trait_B . ' )';
		
		if ( $j != $obj_db->get_number_of_rows( $res_generation ) - 1 )
		{
			$str_script_block = $str_script_block . ", ";
		}
	}
	
	$str_script_block = $str_script_block . ');' . "\n";
}

require_once('../includes/header.inc.php');

//$problemid = $_GET["problemid"];
//$generationid = $GET["generationid"];

?>

<!-- START CONTENT -->

<?php

  if ( $isPlantsImageLoaded )
  {
    // first time visit, reader all images
    $str_image_base = './images/';
    
    $arr_images = array( 'spin.gif', 'pots/pot_a.gif', 'pots/pot_b.gif', 'pots/pot_ab.gif', 'pots_alpha/pot_a.gif',
                            'pots_alpha/pot_b.gif', 'pots_alpha/pot_ab.gif', 'shelf/shelf_bottomleft.gif', 'shelf/shelf_bottomright.gif',
                            'shelf/shelf_level.gif', 'shelf/shelf_sideleft.gif', 'shelf/shelf_sideleft.gif', 'shelf/shelf_topleft.gif', 'shelf/shelf_topright.gif' );

    echo( '<!-- Hack for IE -->' );
    echo( '<div style="display: none;">' );
    
    for ( $i = 0; $i < count( $arr_images ); ++$i )
    {
      echo( '<img src="'.$str_image_base.$arr_images[$i].'" />' );
    }
    
    for ( $i = 1; $i < 11; ++$i )
    {
      $index = '00'.$i;
      $index = substr( $index, strlen( $index ) - 2 );
            
      echo( '<img src="'.$str_image_base.'leaf/left/leaf'.$index.'_a.gif" />' );
      echo( '<img src="'.$str_image_base.'leaf/right/leaf'.$index.'_b.gif" />' );
      echo( '<img src="'.$str_image_base.'leaf_alpha/left/leaf'.$index.'_a.gif" />' );
      echo( '<img src="'.$str_image_base.'leaf_alpha/right/leaf'.$index.'_b.gif" />' );
    }
    
    echo( '</div>' );
  }
  
?>
  <div style="padding-bottom: 10px;">Generation:
  <select name="selectGeneration" id="selectGeneration" onchange="changeGeneration( this );">
  <?php
    
    for ( $i = 1; $i  < $int_number_of_generations + 1; ++$i )
    {
      echo( '<option value="'.$i.'"' );
      
      if ( $i == $int_generation_id )
      {
		echo( ' selected="selected"' );
	  }
	  
	  echo( '>'.$i.'</option>' );
    }
    
  ?>
  </select>
  </div>
  <div style="width: 650px; overflow: hidden;">
    <div id="shelf" style="float: left;"></div><br />
    <div style="float: right;">
      <div id="histogramA"></div>
      <!--
      <table class="listing" cellpadding="0" cellspacing="0" border="0" style="width: 284px;">
        <tr>
          <th>Mean</th>
          <th>Variance</th>
        </tr>
        <tr>
          <td>1.20</td>
          <td>1.43</td>
        </tr>
      </table>-->
      <div id="histogramB"></div>
      <!--
      <table class="listing" cellpadding="0" cellspacing="0" border="0" style="width: 284px;">
        <tr>
          <th>Mean</th>
          <th>Variance</th>
        </tr>
        <tr>
          <td>1.20</td>
          <td>1.43</td>
        </tr>
      </table>-->
    </div>
  </div>
  
  <div style="width: 650px; overflow: hidden;">
    <div style="float: left;">
      <form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
        <span>Selected Plants</span>
        <table class="listing" style="width: 320px; overflow: hidden;" id="SelectedPlantsTable">
          <tr>
            <th>Generation</th>
            <th>Trait A</th>
            <th>Trait B</th>
          </tr>
          <tr>
            <td colspan="3">None</td>
          </tr>
        </table>
		
		<input type="hidden" name="SelectedPlants" id="SelectedPlants" value="" />
		<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>    
		<input type="submit" name="Command" value="Cross" onclick="return onCrossButtonClickHandler();"/>
      </form> 
    </div>
    
    <div style="float: right;">
      <span>Selected Plants Mean and Variance</span>
      <table class="listing" style="width: 320px; overflow: hidden;" id="selectedPlantsMeanAndVariance">
        <tr>
          <th>Trait</th>
          <th>Mean</th>
          <th>Variance</th>
        </tr>
        <tr>
          <td colspan="3">None</td>
        </tr>
      </table>
    </div>
  </div>

<!-- END CONTENT -->

<?php require_once('../includes/footer.inc.php'); ?>
