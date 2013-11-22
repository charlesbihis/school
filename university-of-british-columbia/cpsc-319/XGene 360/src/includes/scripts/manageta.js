
function validateCreateTAForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objTAId = xgene360_cu.Element( 'UserId' );
  var objTAFirstName = xgene360_cu.Element( 'FirstName' );
  var objTALastName = xgene360_cu.Element( 'LastName' );
  var objTAPassword = xgene360_cu.Element( 'Password' );
  var objTAConfirmPassword = xgene360_cu.Element( 'ConfirmPassword' );
  
  var strTAId = objTAId.value.trim().escape();
  var strTAFirstName = objTAFirstName.value.trim().escape();
  var strTALastName = objTALastName.value.trim().escape();
  var strTAPassword = objTAPassword.value;
  var strTAConfirmPassword = objTAConfirmPassword.value;


  if ( strTAId.length == 0 )
  {
    alert( 'Please enter the TA\'s Username' );
    objTAId.focus();    
    return false;
  }
  
  if ( strTAFirstName.length == 0 )
  {
    alert( 'Please enter the TA\'s first name' );
    objTAFirstName.focus();    
    return false;
  }
  
  if ( strTALastName.length == 0 )
  {
    alert( 'Please enter the TA\'s last name' );
    objTALastName.focus();
    return false;
  }

  if (strTAPassword.length == 0)
  {
    alert( 'Please enter the TA\'s password' );
    objTAPassword.focus();    
    return false;
  }

  if (strTAPassword != strTAConfirmPassword)
  {
    alert( 'Please make sure the TA\'s passwords match.' );
    objTAPassword.focus();    
    return false;
  }
  
  objTALastName.value = strTALastName;
  objTAFirstName.value = strTAFirstName;
  
  return true;
}

function validateUpdateTAForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objTAFirstName = xgene360_cu.Element( 'FirstName' );
  var objTALastName = xgene360_cu.Element( 'LastName' );
  var strTAFirstName = objTAFirstName.value.trim().escape();
  var strTALastName = objTALastName.value.trim().escape();
  
  if ( strTAFirstName.length == 0 )
  {
    alert( 'Please enter the TA\'s first name' );
    objTAFirstName.focus();    
    return false;
  }
  
  if ( strTALastName.length == 0 )
  {
    alert( 'Please enter the TA\'s last name' );
    objTALastName.focus();
    return false;
  }
  
  objTALastName.value = strTALastName;
  objTAFirstName.value = strTAFirstName;
  
  return true;
}

function resetCreateTAForm()
{
  return confirm( 'Clear the form?' );
}

function resetUpdateTAForm()
{
  return confirm( 'Reset the form to original values?' );
}
