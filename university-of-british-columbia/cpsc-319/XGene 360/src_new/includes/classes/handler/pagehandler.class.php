<?php

class PageHandler
{    
  /*
    * Redirect the user to their initial URL
    *
    * @param int $int_user_privilege the user privilege
    */
  function redirect_initial_page( $int_user_privilege )
  {
    switch ( $int_user_privilege )
    {
      case UP_ADMINISTRATOR:
      case UP_PROFESSOR:
        PageHandler::redirect( URLROOT.'admin/managecourses.php' );
        break;
      
      case UP_TA:
        PageHandler::redirect( URLROOT.'admin/manageproblems.php' );
        break;  
      
      case UP_STUDENT:
        PageHandler::redirect( URLROOT.'student/viewproblems.php' );
        break;
        
      default:
        PageHandler::redirect( URLROOT.'login.php' );
        break;  
    }
  }
  
  /*
    * Redirect to URL
    *
    * @param string $str_url the URL the user should be redirected to
    */
  function redirect( $str_url )
  {
    header( "Location: $str_url" );
    exit;
  }
  
  /*
    * Return the value of the POST field
    *
    * @param string $str_field_name the name of the field
    *
    * @return mix null if the post value doesn't exist; otherwise, the actual value
    */
  function get_post_value( $str_field_name )
  {
		if ( isset( $_POST[$str_field_name] ) )
		{
			return $_POST[$str_field_name];
		}
		
		return null;
	}
	
	function write_post_value_if_failed( $str_field_name )
	{
		global $g_bln_fail;
		
		if ( $g_bln_fail )
		{
			return PageHandler::get_post_Value( $str_field_name );
		}
		
		return null;
	}
	
	function initialize()
	{
		global $g_obj_db, $g_obj_lock, $g_str_serial, $g_obj_user;
		
		$g_obj_db = new DBManager();
		$g_obj_lock = new LockManager( $g_obj_db );
		
		$g_str_serial = $g_obj_lock->get_serial();

		$g_obj_user = CookieHandler::get_user( $g_obj_db );
	}
	
	function check_permission( $arr_allowed_users )
	{
		global $g_obj_user;
		
		if ( $g_obj_user == null )
		{
			PageHandler::redirect_initial_page( UP_INVALID );
		}
		
		foreach ( $arr_allowed_users as $int_allowed_user )
		{
			if ( $g_obj_user->int_privilege == $int_allowed_user )
			{
				return;
			}
		}
		
		// the user is not in the permission list
		PageHandler::redirect_initial_page( UP_INVALID );
	}
	
	function check_necessary_id( $arr_required_ids, $str_url )
	{
		foreach ( $arr_required_ids as $str_required_id )
		{
			if ( !isset( $_GET[ $str_required_id ] ) )
			{
				PageHandler::redirect( $str_url );
			}
		}
	}
	
	function format_date( $int_time_stamp )
	{
		return date( 'F d, Y H:i:s', $int_time_stamp );
	}
	
}

?>