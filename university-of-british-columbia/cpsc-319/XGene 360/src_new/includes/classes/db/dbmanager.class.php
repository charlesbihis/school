<?php

class DBManager
{
	var $m_obj_connection;

	/**
	 *
	 * create connection to the sql database
	 *
	 */
	function DBManager()
	{
	  $this->m_obj_connection = mysql_connect( DB_SERVER, DB_USERNAME, DB_PASSWORD );
	  
	  if ( $this->m_obj_connection == false )
	  {
	    Log::write_log( LOG_SQL, mysql_errno().': '.mysql_error() );
	    die( "Cannot connect to MySQL server" );
	  }
	  
		mysql_select_db( DB_NAME, $this->m_obj_connection );
		
		if( mysql_errno() != 0 )
		{
			Log::write_log( LOG_SQL, mysql_errno().': '.mysql_error() );
			die( "Cannot select MySQL database" );
		}
	}

	/**
	 * 
	 * for selection queries
	 *
	 * @param string $str_SQL the sql statement
	 * @return resource the resource returned from sql query
	 *
	 */
	function query_select( $str_SQL )
	{
		
		$tmp_resource = mysql_query( $str_SQL )
		  or Log::write_log( LOG_SQL, mysql_errno().': '.mysql_error().'\n'.$str_SQL );
		
		return $tmp_resource;
	}

	/**
	*
	* commit queries
	*
	* @param string $str_SQL the sql statement
	* @return boolean whether the commit is succeeded
	*
	*/
	function query_commit( $str_SQL )
	{
		$tmp_resource = mysql_query( $str_SQL, $this->m_obj_connection )
			or Log::write_log( LOG_SQL, mysql_errno().': '.mysql_error().'\n'.$str_SQL );
		
		return ( mysql_errno() == 0 );
	}

	/**
	*
	* fetches the rows from the database
	*
	* @param resource $res the resource from SELECT query
	* @return mixed properties that correspond to the fetched row, or FALSE is there are no more rows.
	*
	*/
	function fetch( $res )
	{
		return mysql_fetch_object( $res );
	}

	/**
	*
	* get number of rows from SELECT query
	*
	* @param resource $res the resource from SELECT query
	* @return int the number of rows
	*
	*/
	function get_number_of_rows( $res )
	{
		return mysql_num_rows( $res );
	}

	/**
	*
	* get number of rows affected by insert/replace/update/delete queries
	*
	* @return int the number of rows affected
	*
	*/
	function get_number_of_rows_affected()
	{
		return mysql_affected_rows( $this->m_obj_connection );
	}

	/**
	*
	* format the sql string to SQL readable character
	*
	* @param string $str the string need to be replaced
	* @return string formatted string that's readable to SQL
	*
	*/
	function format_sql_string( $str )
	{
		if ( get_magic_quotes_gpc() )
		{
			return mysql_real_escape_string( stripslashes( $str ) );
		}
		
		return mysql_real_escape_string( $str );
	}

  /**
  * 
  * get the last inserted row id
  *
  * @return int the id of the last inserted row
  *
  */
	function get_last_inserted_id()
	{
		return mysql_insert_id();
	}

	 /**
	 *
	 * disconnect the current database connection
	 *
	 */
	function disconnect()
	{
		mysql_close( $this->m_obj_connection );
	}
}
?>
