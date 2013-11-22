          <table id="navi">
            
            <tr>
              <td>
                
<?php

	if ( isset( $g_arr_nav_links ) )
	{
		echo( '<ul class="horizontalmenu">' );
		
		LinkHandler::populate_menu_items( $g_arr_nav_links, $g_str_page_title ); 

		echo( '</ul>' );
	}
  
?>
             
              </td>
            </tr>
          
          </table>
