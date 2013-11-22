function validateLoginForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objUsername = xgene360_cu.Element( 'Username' );
  var objPassword = xgene360_cu.Element( 'Password' );
  
  var strUsername = objUsername.value.trim();
  var strPassword = objPassword.value.trim();
  
  if ( strUsername.length == 0 )
  {
    alert( 'Please enter your username' );
    objUsername.focus();    
    return false;
  }
  
  if ( strPassword.length == 0 )
  {
    alert( 'Please enter the password' );
    objPassword.focus();
    return false;
  }
  
  return true;
}