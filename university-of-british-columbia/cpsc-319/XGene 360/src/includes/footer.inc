            </div><!-- contentMain -->          

          </div><!-- height200 -->

        </div><!-- content -->

        <div id="footer">

        <div id="footergraphic">

        <div class="footertext">

        <ul class="linklist">

        <?php

        if ( isset( $footerLinks ) )
        {
        $tmp_bln_is_first_link = false;

        foreach ( $footerLinks as $tmp_str_link_name => $tmp_str_url )
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

        if( $tmp_str_link_name == $pageTitle )
        {
        echo( $tmp_str_link_name.'</li>' );
        }

        else
        {
        echo( '<a href="'.$tmp_str_url.'">'.$tmp_str_link_name.'</a></li>' );
        }
        }
        }

        ?>

        </ul>

        <br /><br />&copy; 2006 Team 7

        </div><!-- footertext -->

        </div><!-- footergraphic -->

        </div><!-- footer -->

      </div><!-- mainrightbargraphic -->

    </div><!-- main -->

    <hr class="invisible" />

  </body>

</html>

