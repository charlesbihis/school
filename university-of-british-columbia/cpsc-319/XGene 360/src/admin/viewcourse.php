<?php 

require_once( '../includes/global.inc.php' ); 

if ( !isset( $_GET['courseid'] ) )
{
  PageHandler::redirect( './managecourses.php' );
}

$int_course_id = $_GET["courseid"];

$obj_db = new DBManager();
$obj_lock = new LockManager( $obj_db );
$serial = $obj_lock->get_serial();

$obj_user = CookieHandler::get_user( $obj_db );

// FIX: change redirection page
if ( $obj_user == null || $obj_user->int_privilege == UP_STUDENT)
{
  PageHandler::redirect_initial_page( UP_INVALID );
}

require( '../includes/classes/db/coursemanager.class.php' );

$obj_course_manager = new CourseManager( $obj_user, $obj_db );

if ( isset( $_POST['Command'] ) && $obj_lock->page_lock( $_POST['SerialId'] ) )
{
  $command = $_POST['Command'];
  
  switch ( $command )
  {
    case 'Update':
    {
		if ( $obj_course_manager->modify_course( $int_course_id, $_POST['CourseName'], $_POST['CourseDescription'] ) )
		{
			MessageHandler::add_message( MSG_SUCCESS, "Course \"" . $_POST['CourseName'] . "\" updated successfully!" );
		}  // if success
		else
		{
			MessageHandler::add_message( MSG_FAIL, "Error updating course \"" . $_POST['CourseName'] . "\"" );
		}  // else failed
    }
    
    break;
  }
}

$res_course = $obj_course_manager->view_course_details( $int_course_id );

$bln_invalidCourse = false;

if ( $obj_db->get_number_of_rows( $res_course ) == 0 )
{
  // TODO: add error handler here
  $bln_invalidCourse = true;
}

else
{
  $arr_course_info = $obj_db->fetch( $res_course );
}

$str_page_title = "View Course";
$arr_scripts = array( 'managecourse.js' );
$arr_nav_links = $g_arr_nav_links[UP_ADMINISTRATOR];

require_once( '../includes/header.inc.php' );

?>

<!-- Start Content -->

<form method="post" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
	<input class="buttoninput" type="button" value="Back to Course Listing" onClick="window.location='managecourses.php';">
	<br /><br /><br />
	
	<table class="box">
		<tr>
			<th>View Course</th>
		</tr>
		<tr>
			<td>
				<table>
					<tr>
						<td width="75">Name:</td>
						<td><input class="textinput" type="text" name="CourseName" id="CourseName" size="30" value="<?php if ( isset( $arr_course_info ) ) { echo( $arr_course_info->Name ); } ?>" /></td>
					</tr>
					<tr>
						<td style="vertical-align: top">Description:</td>
						<td>
							<textarea class="textareainput" name="CourseDescription" id="CourseDescription" cols="60" rows="10" onkeydown="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );" onkeyup="xgene360_cu.countText( 'CourseDescription', 'CourseDescriptionLetterCount', 250 );"><?php if ( isset( $arr_course_info ) ) { echo( $arr_course_info->Description ); } ?></textarea><br />
							<input class="smallnumberinput" readonly="readonly" type="text" name="CourseDescriptionLetterCount" size="3" maxlength="3" value="<?php if ( isset( $arr_course_info ) ) { echo( 250 - strlen( $arr_course_info->Description ) ); } ?>" /> characters left
						</td>
					</tr>
					<tr>
						<td colspan="2" align="right">
							<input class="buttoninput" type="submit" name="Command" value="Update" onclick="return validateCourseForm();" />
							&nbsp;<input class="buttoninput" type="reset" name="Command" value="Reset" onclick="return resetUpdateCourseForm();" />
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<br /><br />
	<strong>The following professors has access to this course:</strong>
	<table class="listing">
		<tr>
			<th width="50"><input type="checkbox" id="ProfessorIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProfessorId' );" /></th>
			<th width="150">First Name</th>
			<th>Last Name</th>
		</tr>
		<?php
			$res_professors = $obj_course_manager->view_course_professors( $int_course_id );

			if ( $obj_db->get_number_of_rows( $res_professors ) == 0 )
			{
				echo( '<tr>'."\n" );
				echo( '<td colspan="3">There is no professor associated with this course</td>'."\n" );
				echo( '</tr>'."\n" );
			}

			for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_professors ); ++$i )
			{
				$res_row = $obj_db->fetch( $res_professors );

				echo( '<tr onclick="openProfessorDetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
				echo( '<td><input type="checkbox" name="ProfessorId" value="'.$res_row->UserId.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
				echo( '<td>'.$res_row->FirstName.'</td>'."\n" );
				echo( '<td>'.$res_row->LastName.'</td>'."\n" );
				echo( '</tr>'."\n" );
			}
		?>    
	</table>
	<br />
	<strong>The following TAs has access to this course:</strong>
	<table class="listing">
		<tr>
			<th width="50"><input type="checkbox" id="TAIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'TAId' );" /></th>
			<th width="150">First Name</th>
			<th>Last Name</th>
		</tr>
		<?php
			$res_tas = $obj_course_manager->view_course_tas( $int_course_id );

			if ( $obj_db->get_number_of_rows( $res_tas ) == 0 )
			{
				echo( '<tr>'."\n" );
				echo( '<td colspan="3">There is no TA associated with this course</td>'."\n" );
				echo( '</tr>'."\n" );
			}

			for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_tas ); ++$i )
			{
				$res_row = $obj_db->fetch( $res_tas );

				echo( '<tr onclick="openTADetail( \''.$res_row->UserId.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );"">'."\n" );
				echo( '<td><input type="checkbox" name="TAId" value="'.$res_row->UserId.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
				echo( '<td>'.$res_row->FirstName.'</td>'."\n" );
				echo( '<td>'.$res_row->LastName.'</td>'."\n" );
				echo( '</tr>'."\n" );
			}
		?>
	</table>
	<br />
	<strong>The following problems are assigned to this course:</strong>
	<table class="listing">
		<tr>
			<th width="50"><input type="checkbox" id="ProblemIdSelectionToggle" onclick="xgene360_cu.checkAll( this, 'ProblemId' );" /></th>
			<th width="200">Problem</th>
			<th width="200">Start Date</th>
			<th>Due Date</th>
		</tr>
		<?php
			$res_problems = $obj_course_manager->view_course_problems( $int_course_id );

			if ( $obj_db->get_number_of_rows( $res_problems ) == 0 )
			{
				echo( '<tr>'."\n" );
				echo( '<td colspan="4">There is no problem associated with this course</td>'."\n" );
				echo( '</tr>'."\n" );
			}

			for ( $i = 0; $i < $obj_db->get_number_of_rows( $res_problems ); ++$i )
			{
				$res_row = $obj_db->fetch( $res_problems );

				echo( '<tr onclick="openProblemDetail( \''.$res_row->problem_id.'\' );" onmouseover="hightlightSelectedRow( this, true );" onmouseout="hightlightSelectedRow( this, false );">'."\n" );
				echo( '<td><input type="checkbox" name="ProblemId" value="'.$res_row->problem_id.'" onclick="xgene360_cu.stopPropagation( event )" /></td>'."\n" );
				echo( '<td>'.$res_row->problem_name.'</td>'."\n" );
				echo( '<td>'.$res_row->start_date.'</td>'."\n" );
				echo( '<td>'.$res_row->due_date.'</td>'."\n" );
				echo( '</tr>'."\n" );
			}
		?>
	</table>
	<br /><br />
	<input class="buttoninput" type=button value="Back to Course Listing" onClick="window.location='managecourses.php';">
	<input type="hidden" name="SerialId" id="SerialId" value="<?php echo( $serial ); ?>"/>
</form>

<!-- End Content -->

<?php

require_once( '../includes/footer.inc.php' );

$obj_db->disconnect();

?>
