<?php

require( 'includes/global.inc.php' );

// user session is destroyed when reload login page
//CookieHandler::unset_user( );

$invalidLogin = false;

if ( isset( $_POST['Command'] ) )
{
  $command = $_POST['Command']; 
  
  if ( $command == 'Login' )
  {
    $obj_db = new DBManager();

    // authenticate the user
    $user = LoginManager::authenticate( $_POST['Username'], $_POST['Password'], $obj_db );

	// ocassionally purge old lock data
	$obj_lock = new LockManager( $obj_db );
	$obj_lock->purge();

    $obj_db->disconnect();
        
    if ( $user != null )
    {
      CookieHandler::set_user( $user );
      PageHandler::redirect_initial_page( $user->int_privilege );
    }
    
    else
    {
      $invalidLogin = true;
    }
  }
}

$str_page_title = '';
$arr_nav_links = null;
$arr_scripts = array( 'login.js' );
$str_script_block = "

  function onloadHandler()
  {
    document.getElementById( 'Username' ).focus();
  }
  
  xgene360_cu.using( 'event' );
  xgene360_cu.event.addDOMListener( window, 'onload', onloadHandler );
";

require( 'includes/header.inc.php' );

?>

<!-- Start Content -->

<table class="centered">
  
  <tr>
    <td>

      <form method="post" id="LoginForm" action="<?php echo( $_SERVER['REQUEST_URI'] ); ?>">
      
        <table class="format">
        
          <tr>
            <td colspan="4">
              <h3>Welcome to XGene 360, an<em> interactive quantitative genetics simulator</em>.</h3>
              <br />
            </td>
          </tr>
          
          <tr>
            <td valign="middle"><img src="includes/images/main_logo.gif" /></td>
            <td width="30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
            <td valign="middle">
                <p>&nbsp;</p>
                <table class="box">
                  
                  <tr>
                    <th>Login</th>
                  </tr>
                  <tr>
                    <td>
                    
                      <table width="175">
                        
                        <tr>
                          <td width="75">Username:&nbsp;</td>
                          <td><input class="textinput" type="text" name="Username" id="Username" value="<?= isset($_POST['Username']) ? $_POST['Username'] : ''; ?>" size="20" /></td>
                        </tr>
                        
                        <tr>
                          <td width="100">Password:&nbsp;</td>
                          <td><input class="textinput" type="password" name="Password" id="Password" size="20" /></td>
                        </tr>
                        
                        <tr>
                          <td colspan="2" align="center">
                            <?php
                                  
                              if ($invalidLogin)
                              {
                                echo("<p align='left' class='errortext'>The username or password is incorrect.</p>\n");
                              }
                              
                            ?>
                            <input class="buttoninput" type="submit" name="Command" value="Login" onclick="return validateLoginForm();" />
                          </td>
                        </tr>
                      
                      </table>
                        
                    </td>
                  </tr>
                
                </table>
            
            </td>
            <td width="10">&nbsp;</td>
          
          </tr>
        
          <tr>
            <td colspan="4" style="padding: 30px 60px 0px 70px; width: 500px;">
              <p align="left" style="border: 1px solid #669966; padding: 20px; color: #336633;">
                XGene 360 provides students with an interactive environment to supplement the classroom learning experience.
                Students will deepen their understanding of quantitative genetics by selective breeding in a simulated environment.
			  </p>
            </td>
          </tr>
        
        </table>
      
      </form>

    </td>
  </tr>

</table>

<!-- End Content -->

<?php

require( 'includes/footer.inc.php' );

?>

