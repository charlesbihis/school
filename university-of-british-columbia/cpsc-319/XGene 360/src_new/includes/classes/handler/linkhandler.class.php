<?php

$g_arr_nav_defined_links = array();

$g_arr_nav_defined_links[UP_STUDENT] = array( 
  'View Problems' => '/student/viewproblems.php'
);

$g_arr_nav_defined_links[UP_TA] = array( 
  'Manage Students' => '/admin/managestudents.php',
  'View Courses' => '/admin/managecourses.php', 
	'View Problems' => '/admin/manageproblems.php'
);

$g_arr_nav_defined_links[UP_PROFESSOR] = array(
  'Manage Courses' => '/admin/managecourses.php', 
	'Manage Problems' => '/admin/manageproblems.php', 
	'Manage Professors' => '/admin/manageprofessors.php',
	'Manage TAs' => '/admin/managetas.php',
	'Manage Students' => '/admin/managestudents.php'
);

$g_arr_nav_defined_links[UP_ADMINISTRATOR] = array(
  'Manage Courses' => '/admin/managecourses.php', 
	'Manage Problems' => '/admin/manageproblems.php', 
	'Manage Professors' => '/admin/manageprofessors.php',
	'Manage TAs' => '/admin/managetas.php',
	'Manage Students' => '/admin/managestudents.php'
);

$g_arr_header_links = array(
	'Home' => '/',
	'Help' => '/site/help.php'
);

$g_arr_footer_links = array(
  'About XGene 360' => '/site/aboutxgene360.php', 
	'About Team 7' => '/site/aboutteam7.php' );

$g_arr_header_login_links = array(
	'Home' => '/',	
	'Sitemap' => '/site/sitemap.php',
	'Help' => '/site/help.php',
	'LOGOUT' => '/logout.php'
);

$g_arr_calendar_months = array( 
  'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August',
  'September', 'October', 'November', 'December'
);

class LinkHandler
{
  function populate_menu_items( $arr_link, $str_page_title ) 
  {
    if ( isset( $arr_link ) )
    {
      $tmp_bln_is_first_link = false;

      foreach ( $arr_link as $tmp_str_link_name => $tmp_str_url )
      {
        if ( !$tmp_bln_is_first_link )
        {
          echo( '<li class="first">' );
          $tmp_bln_is_first_link = true;
        }
        
        else
        {
          echo( '<li>' );
        }

        if( $tmp_str_link_name == $str_page_title )
        {
          echo( $tmp_str_link_name.'</li>' );
        }
        
        else
        {
          echo( '<a href="'.$tmp_str_url.'">'.$tmp_str_link_name.'</a></li>' );
        }
      }
    }
  }
}

?>