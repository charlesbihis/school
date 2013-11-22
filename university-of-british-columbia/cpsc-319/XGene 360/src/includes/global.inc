<?php

// since realpath doesn't work on windows, here is a hack that works on linux/mac/windows
$rootPath = dirname( dirname( __FILE__ ) );

define( 'LOG_SQL', str_replace( '\\', '/', $rootPath.( '/log/sql.log' ) ) );
define( 'LOG_TRANSACTION', str_replace( '\\', '/', $rootPath.( '/log/transaction.log' ) ) );

define( 'UP_INVALID', 0 );
define( 'UP_STUDENT', 1 );
define( 'UP_TA', 2 );
define( 'UP_PROFESSOR', 3 );
define( 'UP_ADMINISTRATOR', 10 );

// Navigation links for administrator
$administratorLinks = array(
  'Manage Courses' => '/admin/managecourses.php', 
	'Manage Problems' => '/admin/manageproblems.php', 
	'Manage Professors' => '/admin/manageprofessors.php',
	'Manage TAs' => '/admin/managetas.php',
	'Manage Students' => '/admin/managestudents.php' );

// Navigation links for professor
$professorLinks = array(
  'Manage Courses' => '/admin/managecourses.php', 
	'Manage Problems' => '/admin/manageproblems.php', 
	'Manage Professors' => '/admin/manageprofessors.php',
	'Manage TAs' => '/admin/managetas.php',
	'Manage Students' => '/admin/managestudents.php' );

// Navigation links for TA
$taLinks = array(
  'Manage Students' => '/admin/managestudents.php',
  'View Courses' => '/admin/managecourses.php', 
	'View Problems' => '/admin/manageproblems.php', );

// Navigation links for student
$studentLinks = array(
	'View Problems' => '/student/viewproblems.php' );

// Navigation links for footer
$footerLinks = array(
  'About XGene 360' => '/site/aboutxgene360.php', 
	'About Team 7' => '/site/aboutteam7.php',
	'Help' => '/site/help.php' );

// Calendar months
$calendarMonths = array( 
  'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August',
  'September', 'October', 'November', 'December' );

require_once( 'config.inc' );
require_once( 'classes/log/log.class.php' );
require_once( 'classes/db/dbmanager.class.php' );
require_once( 'classes/db/loginmanager.class.php' );
require_once( 'classes/handler/cookiehandler.class.php' );
require_once( 'classes/handler/errorhandler.class.php' );
require_once( 'classes/handler/userhandler.class.php' );
require_once( 'classes/handler/pagehandler.class.php' );

session_start();

?>