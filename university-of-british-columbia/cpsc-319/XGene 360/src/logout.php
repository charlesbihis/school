<?php

require( 'includes/global.inc.php' );


// destroy user session
CookieHandler::unset_user( );

$redirect_delay = 5000;

$str_page_title = null;
$arr_nav_links = null;
$arr_scripts = array( 'redirect.js' );

$str_script_block = "

  function onloadHandler()
  {
    xgene360_cu.redirect( './login.php', $redirect_delay );
  }
  
  xgene360_cu.using( 'event' );
  xgene360_cu.event.addDOMListener( window, 'onload', onloadHandler );
";

require( 'includes/header.inc.php' );

?>
        <!-- Start Content -->

        <div class="centered">
        
          <h3>
            Thank you for using XGene 360.  You have been successfully logged out.
          </h3>
		  <br />
		  <strong>If</strong> this page <strong>does not redirect</strong> you in <?php echo $redirect_delay/1000 ?> secs, please <strong><a href="login.php">click here</a></strong>.
        </div>

        <!-- End Content -->
<?php

require( 'includes/footer.inc.php' );

?>