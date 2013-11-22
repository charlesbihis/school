<?php

  if (isset($_POST['Command']))
  {
    $command = $_POST['Command'];
    
    if ($command == 'Update')
    {
      
    }
  }
  
  function renderContent()
  {
?>
        <!-- Start Content -->

        <table border="0" cellpadding="0" cellspacing="0" class="box">
          <tr>
            <td>
            <?php
              
              if (isset($errorMessage))
              {
                echo($errorMessage);
              }
              
              else
              {
                echo('Unhandled error has occured');
              }
              
            ?>
            </td>
          </tr>
                
          <tr>
            <td>
            <?php
            
              if (isset($errorMessageDescription))
              {
                echo($errorMessageDescription);
              }
              
            ?>    
            </td>
          </tr>
        </table>  

      <!-- End Content -->
<?php
  }
?>
