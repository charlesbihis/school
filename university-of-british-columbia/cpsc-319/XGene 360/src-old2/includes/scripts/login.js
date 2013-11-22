function validateLoginForm()
{
  var objUsername = document.getElementById('Username');
  var objPassword = document.getElementById('Password');
  
  var strUsername = Trim(objUsername.value);
  var strPassword = Trim(objPassword.value);
  
  if (strUsername.length == 0)
  {
    alert('Please enter your username');
    objUsername.focus();    
    return false;
  }
  
  if (strPassword.length == 0)
  {
    alert('Please enter the password');
    objPassword.focus();
    return false;
  }
  
  // the form is valid
  return true;
}