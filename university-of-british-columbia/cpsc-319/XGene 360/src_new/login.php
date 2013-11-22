<?php

/*
* include necessary files
*/

require( 'includes/global.inc.php' );

$g_bln_invalid_login = false;

process_post();

/*
* set header stuff
*/

$g_arr_scripts = array( 'login.js' );
$g_str_script_block = "

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

      <form method="post" id="LoginForm" action="<?= $_SERVER['REQUEST_URI'] ?>">
      
        <table class="format">
        
          <tr>
            <td colspan="4">
              <h3>Welcome to XGene 360, an<em> interactive quantitative genetics simulator</em>.</h3>
              <br />
            </td>
          </tr>
          
          <tr>
            <td valign="middle"><img src="includes/images/main_logo.gif" alt="Main Logo"/></td>
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
                          <td><input class="textinput" type="text" name="Username" id="Username" value="<?= PageHandler::get_post_value( 'Username' ); ?>" size="20" /></td>
                        </tr>
                        
                        <tr>
                          <td width="100">Password:&nbsp;</td>
                          <td><input class="textinput" type="password" name="Password" id="Password" size="20" /></td>
                        </tr>
                        
                        <tr>
                          <td colspan="2" align="center">
                            <?php
                                  
                              if ( $g_bln_invalid_login )
                              {
                                echo( "<p align='left' class='errortext'>The username or password is incorrect.</p>\n" );
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

function process_post()
{
	if ( isset( $_POST['Command'] ) )
	{
		$command = $_POST['Command']; 

		switch ( $command )
		{
			case 'Login':
			{
				on_login_handler();
			}
			break;
			
			default:
			{
				MessageHandler::add_message( MSG_ERROR, "Unknown Command" );
			}
			break;
		}
	}
}

function on_login_handler()
{
	global $g_bln_invalid_login;
	
	$obj_db = new DBManager();

	$str_username = PageHandler::get_post_value( 'Username' );
	$str_password = PageHandler::get_post_value( 'Password' );
	
	// authenticate the user
	$obj_user = LoginManager::authenticate( $str_username, $str_password, $obj_db );

	// ocassionally purge old lock data
	$obj_lock = new LockManager( $obj_db );
	$obj_lock->purge();

	$obj_db->disconnect();
	
	if ( $obj_user != null )
	{
		CookieHandler::set_user( $obj_user );
		PageHandler::redirect_initial_page( $obj_user->int_privilege );
	}

	else
	{		
		$g_bln_invalid_login = true;
	}
}

?>
