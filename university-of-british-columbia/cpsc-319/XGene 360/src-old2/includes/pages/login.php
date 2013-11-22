<?php
  
  $invalidLogin = false;
      
  if (isset($_POST['Command']))
  {
    $command = $_POST['Command'];
    
    if ($command == 'Login')
    {
      // authenticate the user
      $userPrivilege = UserHandler::authenticateUser($_POST['Username'], $_POST['Password']);
      
      if ($userPrivilege == UP_INVALID)
      {
        $invalidLogin = true;
      }
      
      else
      {
        PageHandler::redirectInitialPage($userPrivilege);
      }
    }
}
      
  function getPageTitle()
  {
    return "Login";
  }

  function getScripts()
  {
    return array("Login.js");
  }

  function renderContent()
  {   
?>
        <!-- Start Content -->

        <h1>Welcome to XGene 360!</h1>

        <form method="post" id="LoginForm" action="login.php">

          <table border="0" cellpadding="0" cellspacing="0" class="box">
            <tr>
              <th colspan="2">Login</th>
            </tr>
            <tr>
              <td>Username:&nbsp;</td>
              <td><input type="text" name="Username" id="Username" value="<?= isset($_POST['Username']) ? $_POST['Username'] : ''; ?>" size="20" /></td>
            </tr>
            <tr>
              <td>Password:&nbsp;</td>
              <td><input type="password" name="Password" id="Password" size="20" /></td>
            </tr>
            <tr>
              <td colspan="2" align="center">
                <?php
            
                  global $invalidLogin;
                      
                  if ($invalidLogin)
                  {
                    echo("<p>The username or password is incorrect.</p>\n");
                  }
                  
                ?>
                <input type="submit" name="Command" value="Login" onclick="return validateLoginForm();" />
              </td>
            </tr>
          </table>
          
        </form>

        <!-- End Content -->
<?php
  }
?>
