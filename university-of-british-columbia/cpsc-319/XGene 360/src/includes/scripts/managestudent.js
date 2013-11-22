
function validateCreateStudentForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objStudentId = xgene360_cu.Element( 'StudentId' );
  var objStudentFirstName = xgene360_cu.Element( 'FirstName' );
  var objStudentLastName = xgene360_cu.Element( 'LastName' );
  var objStudentNumber = xgene360_cu.Element( 'StudentNumber' );
  var objStudentPassword = xgene360_cu.Element( 'Password' );
  var objStudentConfirmPassword = xgene360_cu.Element( 'ConfirmPassword' );
  
  var strStudentId = objStudentId.value.trim().escape();
  var strStudentFirstName = objStudentFirstName.value.trim().escape();
  var strStudentLastName = objStudentLastName.value.trim().escape();
  var strStudentNumber = objStudentNumber.value.trim().escape();
  var strStudentPassword = objStudentPassword.value;
  var strStudentConfirmPassword = objStudentConfirmPassword.value;


  if ( strStudentId.length == 0 )
  {
    alert( 'Please enter the Student\'s Username' );
    objStudentId.focus();    
    return false;
  }
  
  if ( strStudentFirstName.length == 0 )
  {
    alert( 'Please enter the Student\'s first name' );
    objStudentFirstName.focus();    
    return false;
  }
  
  if ( strStudentLastName.length == 0 )
  {
    alert( 'Please enter the Student\'s last name' );
    objStudentLastName.focus();
    return false;
  }

  if ( strStudentNumber.length == 0 )
  {
    alert( 'Please enter the Student\'s student number' );
    objStudentNumber.focus();
    return false;
  }

  if (strStudentPassword.length == 0)
  {
    alert( 'Please enter the Student\'s password' );
    objStudentPassword.focus();    
    return false;
  }

  if (strStudentPassword != strStudentConfirmPassword)
  {
    alert( 'Please make sure the Student\'s passwords match.' );
    objStudentPassword.focus();    
    return false;
  }
  
  objStudentLastName.value = strStudentLastName;
  objStudentFirstName.value = strStudentFirstName;
  objStudentId.value = strStudentId;
  objStudentNumber.value = strStudentNumber;
  
  return true;
}

function validateUpdateStudentForm()
{
  xgene360_cu.using( 'stringExtension' );
  
  var objStudentFirstName = xgene360_cu.Element( 'StudentFirstName' );
  var objStudentLastName = xgene360_cu.Element( 'StudentLastName' );
  var objStudentNumber = xgene360_cu.Element( 'StudentNumber' );
  var strStudentFirstName = objStudentFirstName.value.trim().escape();
  var strStudentLastName = objStudentLastName.value.trim().escape();
  var strStudentNumber = objStudentNumber.value.trim().escape();
  
  if ( strStudentFirstName.length == 0 )
  {
    alert( 'Please enter the Student\'s first name' );
    objStudentFirstName.focus();    
    return false;
  }
  
  if ( strStudentLastName.length == 0 )
  {
    alert( 'Please enter the Student\'s last name' );
    objStudentLastName.focus();
    return false;
  }

  if ( strStudentNumber.length == 0 )
  {
    alert( 'Please enter the Student\'s student number' );
    objStudentNumber.focus();
    return false;
  }
  
  objStudentLastName.value = strStudentLastName;
  objStudentFirstName.value = strStudentFirstName;
  objStudentNumber.value = strStudentNumber;
  
  return true;
}

function resetCreateStudentForm()
{
  return confirm( 'Clear the form?' );
}

function resetUpdateStudentForm()
{
  return confirm( 'Reset the form to original values?' );
}
