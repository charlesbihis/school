<?php

define( 'MSG_SUCCESS', 0 );
define( 'MSG_FAIL', 1 );
define( 'MSG_ERROR', 2 );

$g_arr_messages = array();
$g_arr_messages[MSG_SUCCESS] = array();
$g_arr_messages[MSG_FAIL] = array();
$g_arr_messages[MSG_ERROR] = array();

class MessageHandler
{
  function add_message( $int_message_type, $str_message )
  {
    global $g_arr_messages;
    
    array_push( $g_arr_messages[$int_message_type], $str_message );
  }
  
  function has_message( $int_message_type )
  {
    global $g_arr_messages;
    
    return count( $g_arr_messages[$int_message_type] ) != 0;
  }
  
  function next_message( $int_message_type )
  {
    global $g_arr_messages;
    
    if ( MessageHandler::has_message( $int_message_type ) )
    {
      return array_pop( $g_arr_messages[$int_message_type] );
    }
    
    return null;
  }
}

?>