function validateSubmitSolutionForm()
{
  xgene360_cu.using( 'form' );
  
  xgene360_cu.form.init( 'SubmitSolutionForm' );
  
  xgene360_cu.form.addCustomValidator( customValidator );
   
  xgene360_cu.form.addRegExTextBox( 'TraitANumberOfGenes', 'Please enter number for \'TraitA Number of Genes\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'TraitAHeritability', 'Please enter number for \'TraitA Heritability\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAParent1Mean', 'Please enter number for \'TraitA Parent 1 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAParent2Mean', 'Please enter number for \'TraitA Parent 2 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAVariance', 'Please enter number for \'TraitA Variance\'', '[0-9]+.?[0-9]*' );
  
  xgene360_cu.form.addRegExTextBox( 'TraitBNumberOfGenes', 'Please enter number for \'TraitB Number of Genes\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'TraitBHeritability', 'Please enter number for \'TraitB Heritability\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBParent1Mean', 'Please enter number for \'TraitB Parent 1 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBParent2Mean', 'Please enter number for \'TraitB Parent 2 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBVariance', 'Please enter number for \'TraitB Variance\'', '[0-9]+.?[0-9]*' );
  
  
  return xgene360_cu.form.validate();
}

function customValidator()
{
  var objItem = xgene360_cu.Element( 'TraitANumberOfGenes' );
  var iNumber = parseInt( objItem.value );
  
  if ( iNumber <= 0 || iNumber > 200 )
  {
    alert( 'Please enter a number between 1 and 200 for \'TraitA Number of Genes\'' );
    objItem.focus();
    
    return false;
  }
  
  objItem = xgene360_cu.Element( 'TraitBNumberOfGenes' );
  iNumber = parseInt( objItem.value );
  
  if ( iNumber <= 0 || iNumber > 200 )
  {
    alert( 'Please enter a number between 0 and 200 for \'TraitB Number of Genes\'' );
    objItem.focus();
    
    return false;
  }
  
  return true;
}
