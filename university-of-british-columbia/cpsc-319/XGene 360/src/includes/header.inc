<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

  <head>

    <title>XGene 360 <?php echo( isset( $pageTitle ) ? "- $pageTitle" : ""); ?></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="Author" content="CS319: Team 7" />
    <meta name="Copyright" content="&copy; 2006" />
    <meta name="Robots" content="noindex, nofollow" />
    <style type="text/css" media="screen">@import url(<?php echo( URLROOT ) ?>includes/css/styles.css);</style>
    <script type="text/javascript" src="<?php echo( URLROOT ) ?>includes/scripts/cu.js"></script>
    <script type="text/javascript" src="<?php echo( URLROOT ) ?>includes/scripts/common.js"></script>
    <?php

    if ( isset( $scripts ) )
    {
    foreach ($scripts as $scriptName)
    {
    echo( "<script type=\"text/javascript\" src=\"".URLROOT."includes/scripts/$scriptName\"></script>\n");
    }
    }

    ?>

  </head>

  <!-- IE hack in order to deal with text selection -->
  <!-->
  
  <style type="text/css">
  
  div#main #mainrightbargraphic {
    position: static;
  }
  
  </style>
  
  <!-->  
  
  <body onload="document.getElementById('contentMain').style.display = 'block';<?php echo( isset( $onLoad ) ? $onLoad : ""); ?>">

    <hr class="invisible" />

    <div id="main">

      <div id="mainrightbargraphic">      

        <div id="header">

          <div id="headergraphic">

            <h1><?php echo( isset( $pageTitle ) ? "$pageTitle" : "XGene 360"); ?></h1>

          </div><!-- headergraphic -->

        </div><!-- header --> 

        <?php require( 'navi.inc' ); ?>

        <div id="content">

          <div class="height200">

            <noscript>Please enable JavaScript to access this page.</noscript>

            <div id="contentMain" style="display: none;">

            <?php

            if ( ErrorHandler::has_error() )
            {
            echo( '<table class="errorbox" style="color: #ff0000; font-weight: bold;">' );

            while ( ( $errorMessage = ErrorHandler::next_error() ) != null )
            {
            echo( '<tr>' );
            echo( '<td>'.$errorMessage.'</td>' );
            echo( '</tr>' ); 
            }

            echo( '</table>' );
            }

            ?>


