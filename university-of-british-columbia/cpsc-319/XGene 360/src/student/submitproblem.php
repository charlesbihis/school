<?php 

$pageTitle = "View Problem Solution";
$navLinks = array('Login' => '/login.php', 
				  'Logout' => '/logout.php');

require_once('../includes/global.inc'); 
require_once('../includes/header.inc');
require_once('../includes/navi.inc'); 

$inputid = $_GET["problemid"];
?>

<!-- START CONTENT -->

<form method="post" action="">

<b>Submit Problem Solution</b>

<table class="formattable">
	<tr>
		<td colspan="2">
			<table class="formattable">
				<tr>
					<td>Problem ID:</td>
					<td><? echo($inputid); ?></td>
				</tr>
				<tr>
					<td>Course:</td>
					<td>BIOL444</td>
				</tr>
				<tr>
					<td>Start Date:</td>
					<td>
						01/06
					</td>
				</tr>
				<tr>
					<td>Due Date:</td>
					<td>
						04/06
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td>
			<table class="formattable">
				<tr>
					<td>Trait #:</td>
					<td>&nbsp;</td>
				</tr>
				<tr>
					<td>Parent 1 Mean:</td>
					<td><input type="text" name="ap1mean" size="5" /></td>
				</tr>
				<tr>
					<td>Parent 2 Mean:</td>
					<td><input type="text" name="ap2mean" size="5" /></td>
				</tr>			
				<tr>
					<td>Parent 1 SD:</td>
					<td><input type="text" name="ap1sd" size="5" /></td>
				</tr>
				<tr>
					<td>Parent 2 SD:</td>
					<td><input type="text" name="ap2sd" size="5" /></td>
				</tr>
				<tr>
					<td>h2:</td>
					<td><input type="text" name="ah2" size="5" /></td>
				</tr>
				</table>
		</td>
		<td>
			<table class="formattable">
				<tr>
					<td>Trait #:</td>
					<td>&nbsp;</td>
				</tr>
				<tr>
					<td>Parent 1 Mean:</td>
					<td><input type="text" name="bp1mean" size="5" /></td>
				</tr>
				<tr>
					<td>Parent 2 Mean:</td>
					<td><input type="text" name="bp2mean" size="5" /></td>
				</tr>			
				<tr>
					<td>Parent 1 SD:</td>
					<td><input type="text" name="bp1sd" size="5" /></td>
				</tr>
				<tr>
					<td>Parent 2 SD:</td>
					<td><input type="text" name="bp2sd" size="5" /></td>
				</tr>
				<tr>
					<td>h2:</td>
					<td><input type="text" name="bh2" size="5" /></td>
				</tr>
				</table>
		</td>
	</tr>
	<tr>
    <td colspan="2">
      <input type="submit" value="Submit" name="B1" /> <input type="reset" value="Reset" name="B1" />
		</td>
	</tr>
</table>

</form>



<!-- END CONTENT -->

<?php require_once('../includes/footer.inc'); ?>
