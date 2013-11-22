<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

  <head>

    <title>XGene 360 <?php echo( isset( $str_page_title ) ? "- $str_page_title" : ""); ?></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="Author" content="Team 7" />
    <meta name="Copyright" content="&copy; 2006 The University of British Columbia" />
    <meta name="Robots" content="noindex, nofollow" />
    <style type="text/css" media="screen">@import url(<?php echo( URLROOT ) ?>includes/css/styles.css);</style>
    
    <?php

    if ( isset( $arr_styles ) )
    {
      foreach ( $arr_styles as $str_style )
      {
        echo( '<style type="text/css" media="screen">@import url('.URLROOT.'includes/css/'.$str_style.');</style>'."\n" );
      }
    }

    ?>
    
    <script type="text/javascript" src="<?php echo( URLROOT ) ?>includes/scripts/cu.js"></script>
    <script type="text/javascript" src="<?php echo( URLROOT ) ?>includes/scripts/common.js"></script>
    <?php

    if ( isset( $arr_scripts ) )
    {
      foreach ( $arr_scripts as $str_script )
      {
        echo( '<script type="text/javascript" src="'.URLROOT.'includes/scripts/'.$str_script.'"></script>'."\n" );
      }
    }

    if ( isset( $str_script_block ) )
    {
      echo( '<script type="text/javascript">'.$str_script_block.'</script>'."\n" );
    }
    
    ?>
    
  </head>
 
  <body onload="document.getElementById('contentMain').style.display = 'block';">

    <!-- Start Main -->
    
    <table id="main">
      
      <tr>
        <td>
          
          <!-- Start Header -->
          
          <table id="header">
            
            <tr>
              <td id="headergraphic">
                
                <h2><?php echo( isset( $str_page_title ) ? $str_page_title : ""); ?></h2>
                <ul class="horizontalmenu">

                  <?php
                                    
                  if ( isset( $obj_user ) )
                  {          
                    LinkHandler::populate_menu_items( $g_arr_header_login_links, $str_page_title );
                    
                    echo( '</ul><p>[ You are logged in as <strong>'.$obj_user->str_username.' </strong>]</p>' );
                  }
                  
                  else
                  {
                    LinkHandler::populate_menu_items( $g_arr_header_links, $str_page_title );
                    
                    echo( '</ul>' );
                  }
                    
                  ?>
                
                <!-- </ul> already implemented -->
                                
              </td>
            </tr>
          
          </table>
          
          <!-- End Header -->
       
        </td>
      </tr>
      
      <tr>
        <td>
          
          <!-- Start Navigation Menu -->
          
          <?php require( 'navi.inc.php' ); ?>
          
          <!-- End Navigation Menu -->
        
        </td>
      </tr>
      
      <tr>
        
        <!-- Start Content Container -->
        
        <td id="content">
          
          <div id="formattedcontent">
          
            <noscript>Please enable JavaScript to access this page.</noscript>
            
            <div id="contentMain" style="display: none;">          
              
            <?php

			if ( MessageHandler::has_message( MSG_ERROR ) )
			{
				echo( '<table class="errorbox" style="color: #bb0000; font-weight: bold;">' );

				while ( MessageHandler::has_message( MSG_ERROR ) )
				{
					$str_message = MessageHandler::next_message( MSG_ERROR );

					echo( '<tr>' );
					echo( '<td>'.$str_message.'</td>' );
					echo( '</tr>' ); 
				}

				echo( '</table>' );
			}
            
            else
            {
				if ( MessageHandler::has_message( MSG_SUCCESS ) )
				{
					echo( '<table class="errorbox" style="color: #0000ff; font-weight: bold;">' );

					while ( MessageHandler::has_message( MSG_SUCCESS ) )
					{
						$str_message = MessageHandler::next_message( MSG_SUCCESS );
				            
						echo( '<tr>' );
						echo( '<td>'.$str_message.'</td>' );
						echo( '</tr>' ); 
					}

					echo( '</table>' );
				}
		            
				if ( MessageHandler::has_message( MSG_FAIL ) )
				{
					echo( '<table class="errorbox" style="color: #ff0000; font-weight: bold;">' );

					while ( MessageHandler::has_message( MSG_FAIL ) )
					{
						$str_message = MessageHandler::next_message( MSG_FAIL );
			                
						echo( '<tr>' );
						echo( '<td>'.$str_message.'</td>' );
						echo( '</tr>' ); 
					}

					echo( '</table>' );
				}
			}
              
			?>
