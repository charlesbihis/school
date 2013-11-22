
function validateUpdateTAForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  alert('here');
  var objTAFirstName = xgene360_cu.Element( 'TAFirstName' );
  var objTALastName = xgene360_cu.Element( 'TALastName' );
  
  
  var strTAFirstName = objTAFirstName.value.trim().escape();
  var strTALastName = objTALastName.value.trim().escape();
  
  if ( strTAFirstName.length == 0 )
  {
    alert( 'Please enter the TA's first name' );
    objTAFirstName.focus();    
    return false;
  }
  
  if ( strTALastName.length == 0 )
  {
    alert( 'Please enter the TA's last name' );
    objTALastName.focus();
    return false;
  }
  
  objTALastName.value = strTALastName;
  objTAFirstName.value = strTAFirstName;
  
  return true;
}

function resetUpdateTAForm()
{
  return confirm( 'Reset the form to original values?' );
}
