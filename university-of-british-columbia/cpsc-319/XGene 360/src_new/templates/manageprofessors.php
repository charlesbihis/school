<?php 

$title = "Manage Professors";
$navLinks = array('Google' => 'http://www.google.ca/', 
				  'Yahoo' => 'http://www.yahoo.com/', 
				  'Dictionary' => 'http://www.dictionary.com/');

require_once('../includes/global.inc.php'); 
require_once('../includes/header.inc.php');
require_once('../includes/navi.inc.php'); 

?>

<!-- START CONTENT -->

<script language="JavaScript">

function showit() { 
var obj = document.getElementById('div1');
obj.style.display = "block";
}

function hideit() { 
var obj = document.getElementById('div1');
obj.style.display = "none";
}

</script>

Note: include javascript for form validation?  or check on server side?<br>

<a href="#" onClick="showit();">Create Professor</a> | 
<a href="#" onClick="hideit();">Hide Create</a> 

<div id="div1" style="display:none">
<form method="POST" action="">
<table><tr><td>
<b>Create Professor</b>
<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="AutoNumber1">
  <tr>
    <td>First Name</td>
    <td> <input type="text" name="firstname" size="30" /></td>
  </tr>
  <tr>
    <td>Last Name</td>
    <td> <input type="text" name="lastname" size="30" /></td>
  </tr>
  <tr>
    <td>Email</td>
    <td> <input type="text" name="email" size="30" /></td>
  </tr>
  <tr>
    <td>Password</td>
    <td> <input type="text" name="password" size="30" /></td>
  </tr>
  <tr>
    <td colspan="2">
      <input type="submit" value="Submit" name="B1" /> <input type="reset" value="Reset" name="B2" />
  </tr>
</table>

</form>
</td></tr></table>
</div>



<form method="POST" action="">
<table class="listing" border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111">
  <tr>
    <th>Select&nbsp;</th>
    <th>First Name&nbsp;</th>
    <th>Last Name &nbsp;</th>
    <th>Email&nbsp;</th>
    <th>Password&nbsp;</th>
  </tr>
  
  <tr>
    <td><input type="checkbox" name="profid1" value="ON" /></td>
    <td><a href="viewprofessor.php?id=1">michael</a></td>
    <td>smith</td>
    <td>msmith@ubc.ca</td>
    <td>1234</td>
  </tr>
  
  <tr>
    <td><input type="checkbox" name="profid2" value="ON" /></td>
    <td><a href="viewprofessor.php?id=2">jane</a></td>
    <td>smith</td>
    <td>jsmith@ubc.ca</td>
    <td>1234</td>
  </tr>
  
  <tr>
    <td colspan="5">
    <input type="submit" value="delete" name="deletebut" />
    <input type="reset" value="reset" name="B2" />
    </td>
  </tr>
  
</table>


</form>

<!-- END CONTENT -->

<?php require_once('../includes/footer.inc.php'); ?>
