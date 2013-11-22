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
     */
    function get_post_value( $str_field_name )
    {
			if ( isset( $_POST[$str_field_name] ) )
			{
				return $_POST[$str_field_name];
			}
			
			return "";
		}
}

?>