function validateCreateProblemForm()
{
  xgene360_cu.using( 'form' );
  
  xgene360_cu.form.init( 'CreateProblemForm' );
  
  xgene360_cu.form.addCustomValidator( customValidator );
  xgene360_cu.form.addRequiredTextBox( 'ProblemName', 'Please enter the \'Problem Name\'', 250 );
  xgene360_cu.form.addRequiredTextBox( 'ATraitName', 'Please enter the \'Trait A\'', 250 );
  xgene360_cu.form.addRequiredTextBox( 'BTraitName', 'Please enter the \'Trait B\'', 250 );
  xgene360_cu.form.addRequiredTextBox( 'ProblemDescription', 'Please enter the \'Problem Description\'', 250 );
  xgene360_cu.form.addRegExTextBox( 'MaxCross', 'Please enter an integer for \'Offspring per Cross\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'PlantsDisplayed', 'Please enter an integer for \'Displayed Plants per Cross\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'RangeOfAcceptance', 'Please enter number for \'Range of Acceptance\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'MaximumNumberOfCross', 'Please enter number for \'Maximum Number of Cross\'', '[0-9]+' );
  
  xgene360_cu.form.addRegExTextBox( 'TraitANumberOfGenes', 'Please enter number for \'TraitA Number of Genes\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'TraitAHeritability', 'Please enter number for \'TraitA Heritability\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAParent1Mean', 'Please enter number for \'TraitA Parent 1 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAParent2Mean', 'Please enter number for \'TraitA Parent 2 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitAVariance', 'Please enter number for \'TraitA Variance\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitABaseValue', 'Please enter number for \'TraitA Base Value\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRequiredTextBox( 'TraitAUnit', 'Please enter the \'Unit\'', 250 );
  
  xgene360_cu.form.addRegExTextBox( 'TraitBNumberOfGenes', 'Please enter number for \'TraitB Number of Genes\'', '[0-9]+' );
  xgene360_cu.form.addRegExTextBox( 'TraitBHeritability', 'Please enter number for \'TraitB Heritability\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBParent1Mean', 'Please enter number for \'TraitB Parent 1 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBParent2Mean', 'Please enter number for \'TraitB Parent 2 Mean\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBVariance', 'Please enter number for \'TraitB Variance\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRegExTextBox( 'TraitBBaseValue', 'Please enter number for \'TraitB Base Value\'', '[0-9]+.?[0-9]*' );
  xgene360_cu.form.addRequiredTextBox( 'TraitBUnit', 'Please enter the \'Unit\'', 250 );
  
  
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
