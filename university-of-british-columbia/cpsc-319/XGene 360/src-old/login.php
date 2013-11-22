<?php

require ('includes/config.php');
require ('includes/header.php');

?>

<!-- Start Content -->

<form method="POST" action="login.php">

  <table border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td>Username:&nbsp;</td>
      <td><input class="box" type="text" id="username" size="20"></td>
    </tr>
    <tr>
      <td>Password:&nbsp;</td>
      <td><input class="box" type="text" id="password" size="20"></td>
    </tr>
  </table>
  <p><input class="button" type="submit" value="OK" id="submit"></p>
  
</form>


<!-- End Content -->

<?php

require ('includes/footer.php');

?>
