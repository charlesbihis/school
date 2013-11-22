function validateCreateProfessorForm()
{
  xgene360_cu.using( 'form' );
  
  xgene360_cu.form.init( 'CreateProfessorForm' );

  xgene360_cu.form.addCustomValidator( customValidator );

  xgene360_cu.form.addRequiredTextBox( 'UserId', 'Please enter the Professor\'s Username', 20 );
  xgene360_cu.form.addRequiredTextBox( 'FirstName', 'Please enter the Professor\'s First Name', 20 );
  xgene360_cu.form.addRequiredTextBox( 'LastName', 'Please enter the Professor\'s Last Name', 20 );
  xgene360_cu.form.addRequiredTextBox( 'Password', 'Please enter the Professor\'s password', 20 );
  xgene360_cu.form.addRequiredTextBox( 'ConfirmPassword', 'Please confirm the Professor\'s password', 20 );

  return xgene360_cu.form.validate();

}

function customValidator()
{
  var objItem = xgene360_cu.Element( 'Password' );
  var objItem2 = xgene360_cu.Element( 'ConfirmPassword' );
 
  if ( objItem.value != objItem2.value )
  {
    alert( 'Please make sure the password fields match.' );
    objItem.focus();
    
    return false;
  }
  
  return true;
}


function validateUpdateProfessorForm()
{
  xgene360_cu.using( 'form' );
  
  xgene360_cu.form.init( 'UpdateProfessorForm' );

  xgene360_cu.form.addCustomValidator( customValidator2 );
  
  xgene360_cu.form.addRequiredTextBox( 'ProfessorFirstName', 'Please enter the Professor\'s First Name', 20 );
  xgene360_cu.form.addRequiredTextBox( 'ProfessorLastName', 'Please enter the Professor\'s Last Name', 20 );
  
  
  return xgene360_cu.form.validate();
}

function customValidator2()
{
  var objItem = xgene360_cu.Element( 'NewProfessorPassword' );
  var objItem2 = xgene360_cu.Element( 'NewProfessorPasswordConfirm' );
 
  if ( objItem.value != objItem2.value )
  {
    alert( 'Please make sure the password fields match.' );
    objItem.focus();
    
    return false;
  }
  
  return true;
}

function resetCreateProfessorForm()
{
  return confirm( 'Clear the form?' );
}

function resetUpdateProfessorForm()
{
  return confirm( 'Reset the form to original values?' );
}

function onAssignProfessorsToACourseButtonClickHandler( strCheckboxId, strSelectId )
{
  var objSelect = xgene360_cu.Element( strSelectId );
  
  if ( xgene360_cu.stringLength( objSelect.options[objSelect.selectedIndex].value ) == 0 )
  {
    alert( 'Please select a course' );
    objSelect.focus();
    
    return false;
  }
  
  var objInputElements = document.getElementsByTagName( 'INPUT' );
  
  for ( var i = 0; i < objInputElements.length; ++i )
  {
    if ( objInputElements[i].type == 'checkbox' &&
          objInputElements[i].name == strCheckboxId &&
          objInputElements[i].checked )
    {
      return true;
    }
  }
  
  alert( 'Please select at least one professor' );
  
  return false;
}

function onAssignAProfessorToACourseButtonClickHandler( strSelectId )
{
  var objSelect = xgene360_cu.Element( strSelectId );
  
  if ( xgene360_cu.stringLength( objSelect.options[objSelect.selectedIndex].value ) == 0 )
  {
    alert( 'Please select a course' );
    objSelect.focus();
    
    return false;
  }
  
  return true;
}
