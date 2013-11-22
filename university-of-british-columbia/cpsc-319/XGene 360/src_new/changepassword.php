<?php

require ('includes/global.inc.php');

$str_page_title = "Change Password";

require( 'includes/header.inc.php' );

if (isset($_POST['Command']))
{
  $command = $_POST['Command'];
  
  if ($command == 'Update')
  {
    
  }
}
  
?>
        <!-- Start Content -->

        <form method="post" action="changepassword.php">

          <table border="0" cellpadding="0" cellspacing="0" class="box">
            <tr>
              <th colspan="2">Change Password</th>
            </tr>
            <tr>
              <td>Old Password:&nbsp;</td>
              <td><input type="password" name="OldPassword" size="20" /></td>
            </tr>
            <tr>
              <td>New Password:&nbsp;</td>
              <td><input type="password" name="NewPassword" size="20" /></td>
            </tr>
            <tr>
              <td>Retype New Password:&nbsp;</td>
              <td><input type="password" name="RetypeNewPassword" size="20" /></td>
            </tr>
            <tr>
              <td colspan="2" align="center"><input type="submit" name="Command" value="Update" /></td>
            </tr>
          </table>
          
        </form>

        <!-- End Content -->
<?php

require( 'includes/footer.inc.php' );

?>
