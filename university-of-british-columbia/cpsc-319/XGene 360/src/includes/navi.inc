            <div id="navi">

            <ul>

            <?php
              
            if ( isset( $navLinks ) )
            {
            $tmp_bln_is_first_link = false;

            foreach ( $navLinks as $tmp_str_link_name => $tmp_str_url )
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

            </div><!-- navi -->
