          <table id="navi">
            
            <tr>
              <td>
                
                <?php
                
                  if ( isset( $arr_nav_links ) )
                  {
                    echo( '<ul class="horizontalmenu">' );
                        
                    LinkHandler::populate_menu_items( $arr_nav_links, $str_page_title ); 
   
                    echo( '</ul>' );
                  }
                  
                ?>
             
              </td>
            </tr>
          
          </table>
