<?php

  require ('includes/global.inc');
  
  $filename = 'includes/pages/';
  
  if (!isset($_GET['Page']))
  {
    $filename = $filename.'login.php';
  }
  
  else
  {
    $filename = $filename.$_GET['Page'];
  }
  
  if (file_exists($filename))
  {
    include($filename);
  }
  
  else
  {
    $errorMessage = "The page cannot be found";
    include('includes/pages/error.php');
  }
        
  echo("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  
  <head>
	  <title>XGene 360 <?php echo(function_exists('getPageTitle') ? '- '.getPageTitle() : ''); ?></title>
	  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	  <meta name="Copyright" content="&copy; 2006" />
	  <meta name="Robots" content="noindex, nofollow" />
	  <style type="text/css" media="screen">@import url(includes/css/styles.css);</style>
	  <script type="text/javascript" src="includes/scripts/common.js"></script>
	  <?php
	  
	    if (function_exists('getScripts'))
	    {
	      $scripts = getScripts();
	      
	      foreach ($scripts as $scriptName)
	      {
	        echo("<script type=\"text/javascript\" src=\"".URLROOT."includes/scripts/$scriptName\"></script>\n");
	      }
	    }
	    
	  ?>
	    
  </head>
  
  <body onload="document.getElementById('contentMain').style.display = 'block';<?php echo(function_exists('getBodyOnLoad') ? getBodyOnLoad() : ''); ?>">
  
    <hr class="ineffable" />
    
    <div id="main">
    
      <div id="header">
	      <h1>XGene 360</h1>
      </div>
      
      <div id="content">
      
        <noscript>Please enable JavaScript to access this page.</noscript>
      
        <div id="contentMain" style="display: none;">
          
          <?php
          
            if (function_exists('renderContent'))
            {
              renderContent();
            }
          
          ?>
          
        </div>
      
      </div>

	    <div id="footer">
		    <p>&copy; 2006 Spoon</p>
	    </div>
    	
    </div>
    
    <hr class="ineffable" />
    
  </body>

</html>
