<?php

class PageHandler
{    
    /*
     * Redirect the user to their initial URL
     *
     * @param int $userPrivilege the user privilege
     */
    function redirectInitialPage($userPrivilege)
    {
      switch ($userPrivilege)
      {
        case UP_Administrator:
        case UP_Professor:
          $this->redirect(URLROOT.'admin/managecourses.php');
          break;
        
        case UP_TA:
          $this->redirect(URLROOT.'admin/manageproblems.php');
          break;  
        
        case UP_Student:
          $this->redirect(URLROOT.'student/viewproblems.php');
          break;
          
        default:
          $this->redirect(URLROOT.'login.php');
          break;  
      }
    }
    
    /*
     * Redirect to URL
     *
     * @param string $url the URL the user should be redirected to
     */
    function redirect($url)
    {
      header("Location: $url");
      exit;
    }
}

?>