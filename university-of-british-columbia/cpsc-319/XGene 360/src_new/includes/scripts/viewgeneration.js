xgene360_cu.using( 'tip' );
xgene360_cu.using( 'drag' );
xgene360_cu.using( 'event' );

function onloadHandler()
{
  xgene360_plantshelf.objListOfSelectPlantsTable = xgene360_cu.Element( 'SelectedPlantsTable' );
  xgene360_plantshelf.objListOfSelectedPlantsMeanAndVariance = xgene360_cu.Element( 'selectedPlantsMeanAndVariance' );
  changeGeneration( xgene360_cu.Element( 'selectGeneration' ) );
}

xgene360_cu.event.addDOMListener( window, 'onload', onloadHandler );

var objHistogramA = new xgene360_histogram();
var objHistogramB = new xgene360_histogram();

function initHackForIE()
{
  if ( xgene360_cu.IE )
  {
    setTimeout( 'checkHackForIE()', 100 );
  }
  
  else
  {
    xgene360_plantshelf.render( 'shelf', objPlants[xgene360_plantshelf.iCurrentGeneration] );
  }
}

function checkHackForIE()
{
  if ( document.readyState == 'complete' )
  {
    xgene360_plantshelf.render( 'shelf', objPlants[xgene360_plantshelf.iCurrentGeneration] );
  }
  
  else
  {
    initHackForIE();
  }
}

function changeGeneration( objSelection )
{
  xgene360_plantshelf.iCurrentGeneration = parseInt( objSelection.options[objSelection.selectedIndex].value );
  
  objHistogramA.assignValues( objPlants[xgene360_plantshelf.iCurrentGeneration], true );
  objHistogramA.render( 'histogramA', 284, 200, 20, 20 );
  
  objHistogramB.assignValues( objPlants[xgene360_plantshelf.iCurrentGeneration], false );
  objHistogramB.render( 'histogramB', 284, 200, 20, 20 );
  
  initHackForIE();
}

function onCrossButtonClickHandler()
{
  var objElement = xgene360_cu.Element( 'SelectedPlants' );
  var strSelectedPlantIds = '';
  
  if ( xgene360_plantshelf.objSelectedPlants.length == 0 )
  {
    alert( 'Please select at least one plant to cross' );
    return false;
  }
  
  for ( var i = 0; i < xgene360_plantshelf.objSelectedPlants.length; ++i )
  {
    strSelectedPlantIds += xgene360_plantshelf.objSelectedPlants[i].strPlantId;
    
    if ( i < xgene360_plantshelf.objSelectedPlants.length - 1 )
    {
      strSelectedPlantIds += ';';
    }
  }
  
  objElement.value = strSelectedPlantIds;
  
  return true;
}