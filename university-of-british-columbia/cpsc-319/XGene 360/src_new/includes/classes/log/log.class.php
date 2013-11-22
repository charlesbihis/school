<?php

class Log
{
  function write_log( $log_type, $str_message )
  {
    $str_formatted_message = sprintf( "['%s'] %s\r\n", date( 'Y-m-d H:i:s' ), $str_message );
    
    error_log( $str_formatted_message, 3, $log_type);
    
  }
}

?>