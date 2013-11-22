<?php

// since realpath doesn't work on windows, here is a hack that works on linux/mac/windows
$rootPath = dirname( dirname( __FILE__ ) );

define( 'LOG_SQL', str_replace( '\\', '/', $rootPath.( '/log/sql.log' ) ) );
define( 'LOG_TRANSACTION', str_replace( '\\', '/', $rootPath.( '/log/transaction.log' ) ) );

define( 'UP_INVALID', 0 );
define( 'UP_STUDENT', 3 );
define( 'UP_TA', 2 );
define( 'UP_PROFESSOR', 1 );
define( 'UP_ADMINISTRATOR', 10 );

require_once( 'config.inc.php' );
require_once( 'classes/log/log.class.php' );
require_once( 'classes/db/dbmanager.class.php' );
require_once( 'classes/db/loginmanager.class.php' );
require_once( 'classes/db/lockmanager.class.php' );
require_once( 'classes/handler/linkhandler.class.php' );
require_once( 'classes/handler/cookiehandler.class.php' );
require_once( 'classes/handler/messagehandler.class.php' );
require_once( 'classes/handler/errorhandler.class.php' );
require_once( 'classes/handler/userhandler.class.php' );
require_once( 'classes/handler/pagehandler.class.php' );
require_once( 'classes/simulator/gene.class.php' );

session_start();

?>