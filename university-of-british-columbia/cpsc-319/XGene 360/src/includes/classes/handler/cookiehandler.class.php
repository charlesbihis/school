<?php

define( 'COOKIE_USERNAME', 'xgene360_username' );
define( 'COOKIE_PASSWORD', 'xgene360_password' );

class CookieHandler
{
  
  function set_user( $obj_user )
  {
    $_SESSION[COOKIE_USERNAME] = $obj_user->str_username;
    $_SESSION[COOKIE_PASSWORD] = $obj_user->str_password;
  }
  
  function unset_user()
  {
    
    if (isset($_SESSION))
    {
		if (isset($_SESSION[COOKIE_USERNAME]))
		{
		unset($_SESSION[COOKIE_USERNAME]);
		}
		
		if (isset($_SESSION[COOKIE_PASSWORD]))
		{
		unset($_SESSION[COOKIE_PASSWORD]);
		}
		
		$_SESSION = array();
	}
	
    session_destroy();
  }
   
  /**
  * 
  * get the user from the cookie
  *
  */
  function get_user( $obj_db )
  {
    if ( !isset( $_SESSION[COOKIE_USERNAME] ) || !isset( $_SESSION[COOKIE_PASSWORD] ) )
    {
      return null;
    }
    
    $obj_user = LoginManager::authenticate_hash( $_SESSION[COOKIE_USERNAME], $_SESSION[COOKIE_PASSWORD], $obj_db );
    
    return $obj_user;
  }
  
  function set_cookie_value( $str_name, $obj_value )
  {
    setcookie( $str_name, $obj_value );
  }
  
  function get_cookie_value( $str_name )
  {
    if ( !isset( $_COOKIE[$str_name] ) )
    {
      return null;
    }
  
    return $_COOKIE[$str_name];
  }
}
  
?>
