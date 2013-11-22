<?php 

require_once('../includes/global.inc.php'); 

$str_page_title = "View Problem Solution";
$arr_nav_links = $g_arr_nav_links[UP_STUDENT];

require_once('../includes/header.inc.php');

$inputid = $_GET["problemid"];
?>

<!-- START CONTENT -->


<form method="post" action="">

<b>Problem Solution</b>

<table class="formattable">
	<tr>
		<td>
			<table class="formattable">
				<tr>
					<td>Plants Generated:</td>
					<td><input type="text" name="plantsgenerated" size="5" /></td>
					<td>plants</td>
				</tr>
				<tr>
					<td>Plants Displayed:</td>
					<td><input type="text" name="plantsdisplayed" size="5" /></td>
					<td>plants</td>
				</tr>
				<tr>
					<td>Range of Acceptance:</td>
					<td><input type="text" name="rangeofacceptance" size="3" maxlength="3" /></td>
					<td>%</td>
				</tr>
			</table>
		</td>
		<td>
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
						<select name="startdate">
							<option selected label="date1" value="date1">Date 1</option>
							<option label="date2" value="date2">Date 2</option>
							<option label="date3" value="date3">Date 3</option>
							<option label="date4" value="date4">Date 4</option>
							<option label="date5" value="date5">Date 5</option>
						</select>
					</td>
				</tr>
				<tr>
					<td>Due Date:</td>
					<td>
						<select name="enddate">
							<option selected label="month" value="jan">January</option>
							<option label="month" value="febjanuary">February</option>
							<option label="date3" value="date3">Date 3</option>
							<option label="date4" value="date4">Date 4</option>
							<option label="date5" value="date5">Date 5</option>
						</select>
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td>
			<table class="formattable">
				<tr>
					<td>Trait A:</td>
					<td><input type="text" name="atrait" size="30" /></td>
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
					<td>Base Value:</td>
					<td><input type="text" name="abasevalue" size="5" /></td>
				</tr>
				<tr>
					<td>Unit:</td>
					<td><input type="text" name="aunit" size="20" /></td>
				</tr>
				<tr>
					<td>h2:</td>
					<td><input type="text" name="ah2" size="5" /></td>
				</tr>
				<tr>
					<td>Number of Genes:</td>
					<td><input type="text" name="anumgenes" size="3" maxlen="3" /></td>
				</tr>
			</table>
		</td>
		<td>
			<table class="formattable">
				<tr>
					<td>Trait B:</td>
					<td><input type="text" name="btrait" size="30" /></td>
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
					<td>Base Value:</td>
					<td><input type="text" name="bbasevalue" size="5" /></td>
				</tr>
				<tr>
					<td>Unit:</td>
					<td><input type="text" name="bunit" size="20" /></td>
				</tr>
				<tr>
					<td>h2:</td>
					<td><input type="text" name="bh2" size="5" /></td>
				</tr>
				<tr>
					<td>Number of Genes:</td>

					<td><input type="text" name="bnumgenes" size="3" maxlen="3" /></td>
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

<?php require_once('../includes/footer.inc.php'); ?>
