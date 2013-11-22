function xgene360_histogram_manager() {}

xgene360_histogram_manager.m_objHistograms = new Object();

xgene360_histogram_manager.addHistogram = function( strId, objHistogram )
{
  xgene360_histogram_manager.m_objHistograms[ strId ] = objHistogram;
}

xgene360_histogram_manager.getHistogram = function( strId )
{
  return xgene360_histogram_manager.m_objHistograms[ strId ];
}

function xgene360_histogram()
{  
  ////////////////////////////////////////////////////////////
  //
  // member variables
  //
  ////////////////////////////////////////////////////////////
  
  this.m_fMinX  = 0;  // the minimum value of the histogram
  this.m_fMaxX  = 0;  // the maximum value of the histogram
  this.m_iMaxY  = 0;  // the maximum number of items in one bar
 
  this.m_iXCount  = 11; // the number of bars horizontally
  this.m_iYCount  = 5;  // the number of points appears in y axis
  
  this.m_fBarRange  = 0;  // the data range for each bar
  
  this.m_iXAxisOffset = 0;
  this.m_iYAxisOffset = 10;
  
  // the data array containing all the plants
  this.m_objRange = null;
  this.m_objOriginalColor = null;
  this.m_objSelected = null;
  
  this.m_strContainerId = '';
  this.m_objContainer = null;
  
  this.m_bTraitA = false;
  
  this.m_objInfoLabel = null;
  
  ////////////////////////////////////////////////////////////
  //
  // methods
  //
  ////////////////////////////////////////////////////////////
  
  this.assignValues = function( objPlants, bTraitA )
  {
    this.m_fMinX  = 0;
    this.m_fMaxX  = 0;
    this.m_iMaxY  = 0;
    
    this.m_objRange = new Array( this.m_iXCount );
  
    for ( var i = 0; i < this.m_objRange.length; ++i )
    {
      this.m_objRange[i] = new Array();
    }

    this.m_objOriginalColor = new Array( this.m_iXCount );

    this.m_objSelected = new Array( this.m_iXCount );

    this.m_bTraitA = bTraitA;
    
    if ( bTraitA )
    {
      var fValue = objPlants[0].fTraitAValue;
    }
    
    else
    {
      var fValue = objPlants[0].fTraitBValue;
    }
    
    this.m_fMinX = fValue;
    
    // check for the max and min x
    for ( var i = 0; i < objPlants.length; ++i )
    {
      if ( bTraitA )
      {
        fValue = objPlants[i].fTraitAValue;
      }
      
      else
      {
        fValue = objPlants[i].fTraitBValue;
      }
      
      if ( fValue > this.m_fMaxX )
      {
        this.m_fMaxX = fValue;
      }
      
      else if ( fValue < this.m_fMinX )
      {
        this.m_fMinX = fValue;
      }
    }
    
    if ( this.m_fMinX == this.m_fMaxX )
    {
      // special case where all plants belong to the same range, so equally divide the range
      this.m_fMinX -= 0.5;
      this.m_fMaxX += 0.5;
    }

    // calculate the delta (the range of each bar)
    this.m_fBarRange = ( this.m_fMaxX - this.m_fMinX ) / ( this.m_iXCount - 1 );
    
    for ( var i = 0; i < objPlants.length; ++i )
    {
      if ( bTraitA )
      {
        fValue = objPlants[i].fTraitAValue;
      }
      
      else
      {
        fValue = objPlants[i].fTraitBValue;
      }
      
      // check which group this value belongs to
      var iIndex = Math.floor( ( fValue - this.m_fMinX ) / this.m_fBarRange );
      
      this.m_objRange[iIndex].push( objPlants[i] );
      
      objPlants[i].setTraitClass( bTraitA, iIndex );
      
      if ( this.m_objRange[iIndex].length > this.m_iMaxY )
      {
        this.m_iMaxY = this.m_objRange[iIndex].length;
      }
    }
  }

  // render the histogram
  this.render = function( strCanvas, iCanvasWidth, iCanvasHeight, iAxisWidth, iAxisHeight )
  {
    // setting up the canvas stuff
    var objCanvas = xgene360_cu.Element( strCanvas );
   
    // to prevent memory leak
    var objDivs = objCanvas.getElementsByTagName( 'DIV' );
    
    for ( var i = 0; i < objDivs.length; ++i )
    {
      objDivs.onmousedown = null;
      objDivs.onselectstart = null;
      objDivs.onmouseover = null;
      objDivs.onmouseout = null;
    }
    
    
    // faster to clear this way
    objCanvas.innerHTML = '';
    
    // comment: i choose to use DOM here because the operation it takes to create histogram is fairly small 
    // and frankly.. i would prefer speed over programming style since what visible to the user is the loading time
    // not the coding style (http://www.quirksmode.org/dom/innerhtml.html)
    
    objCanvas.style.width = iCanvasWidth + 'px';
    objCanvas.style.height = iCanvasHeight + 'px';
    objCanvas.style.position = 'relative';
    objCanvas.className = "histogram";
    
    this.m_strContainerId = strCanvas + '_Container';
    
    // setting up the bar stuff
    var iBarWidth = Math.floor( ( iCanvasWidth - iAxisWidth ) / this.m_iXCount ) - 1;
    var iBarMaxHeight = iCanvasHeight - 3 * iAxisHeight;
    
    // container related stuff
    var objContainer = document.createElement( 'DIV' );
    
    objContainer.id = this.m_strContainerId;
    objContainer.style.width = ( iCanvasWidth - iAxisWidth ) + 'px';
    objContainer.style.height = ( iCanvasHeight - iAxisHeight * 2 ) + 'px';
    objContainer.style.position = 'absolute';
    objContainer.style.left = iAxisWidth  + 'px';
    objContainer.style.top = '0px';
    objContainer.style.backgroundColor = '#ececec';
    
    objContainer.onmousedown = function( e ) { xgene360_histogram_drag_select.init( e, this ) };
    objContainer.onselectstart = function() { return false; };
    
    // create all histogram bars
    var iLeft = 0;
    var fBarHeightRatio = iBarMaxHeight / this.m_iMaxY;
    
    for ( var i = 0; i < this.m_objRange.length; ++i )
    {
      var iBarHeight = Math.ceil( this.m_objRange[i].length * fBarHeightRatio );
      
      var strBarDescription = 'Count: ' + this.m_objRange[i].length + '<br />' +
                              'Range: ' + ( this.m_fMinX + i * this.m_fBarRange ).toFixed( 1 ) + ' - ' + ( this.m_fMinX + i * this.m_fBarRange + this.m_fBarRange ).toFixed( 1 );
                                    
      var objBar = document.createElement( 'DIV' );
      
      // which trait is this?
      this.m_bTraitA ? objBar.className = 'traitA' : objBar.className = 'traitB';
      
      objBar.style.width = iBarWidth + 'px';
      
      // we want to hide the bar (since IE cannot display 0px height)
      iBarHeight == 0 ? objBar.style.display = 'none' : objBar.style.height = iBarHeight + 'px';
      
      objBar.style.left = iLeft + 'px';
      
      eval( 'objBar.onmouseover = function() { xgene360_cu.tip.show( \'' + strBarDescription + '\'); };' );
      objBar.onmouseout = function() { xgene360_cu.tip.hide(); };
      
      iLeft += iBarWidth + 1;
      
      objContainer.appendChild( objBar );
      
      this.m_objOriginalColor[i] = objBar.style.backgroundColor;
    }
    
    // create mean/variance label
    this.m_objInfoLabel = document.createElement( 'SPAN' );
    this.m_objInfoLabel.style.borderWidth = '1px';
    this.m_objInfoLabel.style.borderStyle = 'solid';
    this.m_objInfoLabel.style.borderColor = '#000000';
    this.m_objInfoLabel.style.backgroundColor = '#ffff66';
    this.m_objInfoLabel.style.position = 'absolute';
    this.m_objInfoLabel.style.fontSize = '9px';
    this.updateInfoLabel();
    
    objContainer.appendChild( this.m_objInfoLabel );
    
    objCanvas.appendChild( objContainer );
    
    // create the y axis
    var objAxis = document.createElement( 'DIV' );
    
    objAxis.className = 'yAxis';
    objAxis.style.width = iAxisWidth + 'px';
    objAxis.style.height = ( iCanvasHeight - iAxisHeight ) + 'px';
    
    for ( var i = 0; i < this.m_iYCount; ++i )
    {
      var objAxisLabel = document.createElement( 'DIV' );
      
      objAxisLabel.className = 'yAxisLabel';
      objAxisLabel.style.width = iAxisWidth + 'px';
      objAxisLabel.style.bottom = ( Math.floor( iBarMaxHeight - ( iBarMaxHeight / this.m_iYCount ) * i ) + this.m_iYAxisOffset ) + 'px';
      
      objAxisLabel.appendChild( document.createTextNode( ( this.m_iMaxY -  ( this.m_iMaxY / this.m_iYCount ) * i ).toFixed( 1 ) ) );
      
      objAxis.appendChild( objAxisLabel );
    }
    
    objCanvas.appendChild( objAxis );
    
    // create the x axis
    objAxis = document.createElement( 'DIV' );
    objAxis.className = 'xAxis';
    objAxis.style.width = iCanvasWidth + 'px';
    objAxis.style.height = iAxisHeight + 'px';
    objAxis.style.bottom = iAxisHeight + 'px';
    
    iLeft = 0;
    
    for ( var i = 0; i < this.m_iXCount; ++i )
    {
      if ( i % 2 == 0 )
      {
        var objAxisLabel = document.createElement( 'DIV' );
        
        objAxisLabel.className = 'xAxisLabel';
        objAxisLabel.style.width = iBarWidth + 'px';
        objAxisLabel.style.left = ( iLeft + iAxisWidth + this.m_iXAxisOffset ) + 'px';
        
        objAxisLabel.appendChild( document.createTextNode( ( this.m_fMinX + i * this.m_fBarRange ).toFixed( 1 ) ) );
      }
      
      iLeft += iBarWidth + 1;
      
      objAxis.appendChild( objAxisLabel );
    }
    
    objCanvas.appendChild( objAxis );
    
    // create the label
    var objLabel = document.createElement( 'DIV' );
    
    objLabel.className = 'traitLabel';
    objLabel.style.width = iCanvasWidth + 'px';
    objLabel.style.height = iAxisHeight + 'px';
    
    if ( this.m_bTraitA )
    {
      objLabel.appendChild( document.createTextNode( 'Trait A' ) );
    }
    
    else
    {
      objLabel.appendChild( document.createTextNode( 'TraitB' ) );
    }
    
    objCanvas.appendChild( objLabel );
    
    xgene360_histogram_manager.addHistogram( this.m_strContainerId, this );
  }
  
  this.updateInfoLabel = function()
  {
    var fMean = 0.0;
    var fVariance = 0.0;
    var iNumberOfItems = 0;
    
    var objPlants = new Array();
    
    for ( var i = 0; i < this.m_objRange.length; ++i )
    {
      if ( this.m_objSelected[i] )
      {
        iNumberOfItems += this.m_objRange[i].length;
        
        for ( var j = 0; j < this.m_objRange[i].length; ++j )
        {
          objPlants.push( this.m_objRange[i][j] );
          
          if ( this.m_bTraitA )
          {
            fMean += this.m_objRange[i][j].fTraitAValue;
          }
          
          else
          {
            fMean += this.m_objRange[i][j].fTraitBValue;
          }
        }
      }
    }
    
    if ( iNumberOfItems != 0 )
    {
      fMean /= iNumberOfItems;
      
      while ( objPlants.length != 0 )
      {
        var objPlant = objPlants.pop();
        
        if ( this.m_bTraitA )
        {
          fVariance += ( objPlant.fTraitAValue - fMean ) * ( objPlant.fTraitAValue - fMean );
        }
        
        else
        {
          fVariance += ( objPlant.fTraitBValue - fMean ) * ( objPlant.fTraitBValue - fMean );
        }
      }
      
      fVariance /= ( iNumberOfItems - 1 );
    }
    
    else
    {
      fVariance = NaN;
    }
    
    if ( isNaN( fVariance ) )
    {
      this.m_objInfoLabel.innerHTML = '&nbsp;Mean: ' + fMean.toFixed( 1 ) + '&nbsp;';
    }
    
    else
    {
      this.m_objInfoLabel.innerHTML = '&nbsp;Mean: ' + fMean.toFixed( 1 ) + '&nbsp;&nbsp;Variance: ' + fVariance.toFixed( 1 ) + '&nbsp;';
    }
    
  }
}

xgene360_cu.using( 'event' );
xgene360_cu.using( 'geometry' );

function xgene360_histogram_drag_select() {}

xgene360_histogram_drag_select.m_objPrevHistogram = null;
xgene360_histogram_drag_select.m_objHistogram = null;
xgene360_histogram_drag_select.m_objContainer = null;
xgene360_histogram_drag_select.m_objBounds = null;
xgene360_histogram_drag_select.m_objBars = null;
xgene360_histogram_drag_select.m_objSelectedBars = null;

xgene360_histogram_drag_select.m_strId = 'dragSelection';

xgene360_histogram_drag_select.m_objMask = null;

xgene360_histogram_drag_select._internalInit = function()
{
  var objMask = document.createElement( 'DIV' );
  
  objMask.id = xgene360_histogram_drag_select.m_strId;
  objMask.style.visibility = 'hidden';
  objMask.style.overflow = 'hidden';
  objMask.style.position = 'absolute';
  objMask.style.zIndex = 100;
  objMask.style.borderWidth = '1px';
  objMask.style.borderStyle = 'solid';
  objMask.style.borderColor = '#ffffff';
  objMask.style.backgroundColor = '#505050';
  
  xgene360_cu.setOpacity( objMask, 70 );
  
  document.body.appendChild( objMask );
  
  xgene360_histogram_drag_select.m_objMask = objMask;
}

xgene360_cu.event.addDOMListener( window, "onload", xgene360_histogram_drag_select._internalInit );

xgene360_histogram_drag_select.init = function( e, objContainer )
{
  if ( xgene360_cu.drag.m_bDragging )
  {
    return;
  }
  
  xgene360_histogram_drag_select.m_objHistogram = xgene360_histogram_manager.getHistogram( objContainer.id );
  xgene360_histogram_drag_select.m_objContainer = objContainer;
  xgene360_histogram_drag_select.m_objBounds = xgene360_cu.geometry.getBounds( objContainer );
  xgene360_histogram_drag_select.m_objBars = objContainer.getElementsByTagName( 'DIV' );
  xgene360_histogram_drag_select.m_objSelectedBars = new Array( xgene360_histogram_drag_select.m_objBars.length );
  
  xgene360_cu.drag.onstart = xgene360_histogram_drag_select.ondragstart;
  xgene360_cu.drag.onstop = xgene360_histogram_drag_select.ondragstop;
  xgene360_cu.drag.onmove = xgene360_histogram_drag_select.onmove;
  
  var objEvent = xgene360_cu.event.getEvent( e );
  objEvent.stopPropagation();
  objEvent.preventDefault();
  
  xgene360_cu.drag.start( objEvent );
}

xgene360_histogram_drag_select.ondragstart = function( objInfo )
{
  xgene360_histogram_drag_select.m_objBars = xgene360_histogram_drag_select.m_objContainer.getElementsByTagName( 'DIV' );
  
  var objMask = xgene360_histogram_drag_select.m_objMask;
  
  objMask.style.left = objInfo.m_objStartEvent.pageX + 'px';
  objMask.style.top = objInfo.m_objStartEvent.pageY + 'px';
  objMask.style.width = '0px';
  objMask.style.height = '0px';
  
  xgene360_cu.showElement( objMask );
}

xgene360_histogram_drag_select.ondragstop = function( objInfo )
{
  for ( var i = 0; i < xgene360_histogram_drag_select.m_objSelectedBars.length; ++i )
  {
    if ( objInfo.m_objStartEvent.shiftKey )
    {
      if ( !xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i] )
      {
        // we need to preserve selected status
        xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i] = xgene360_histogram_drag_select.m_objSelectedBars[i];
      }
    }
    
    else
    {
      // we don't need to preserve selected status
      xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i] = xgene360_histogram_drag_select.m_objSelectedBars[i];
    }
  }
  
  xgene360_histogram_drag_select.m_objPrevHistogram = xgene360_histogram_drag_select.m_objHistogram;
  
  xgene360_histogram_drag_select.m_objHistogram = null;
  xgene360_histogram_drag_select.m_objContainer = null;
  xgene360_histogram_drag_select.m_objBounds = null;
  xgene360_histogram_drag_select.m_objBars = null;
  xgene360_histogram_drag_select.m_objSelectedBars = null;
  
  xgene360_cu.hideElement( xgene360_histogram_drag_select.m_objMask );
}

xgene360_histogram_drag_select.onmove = function( objInfo )
{
  if ( xgene360_histogram_drag_select.m_objMask != null )
  {
    var iCurX = objInfo.m_objCurrentEvent.pageX;
    var iCurY = objInfo.m_objCurrentEvent.pageY;

    // check the boundary
    var objBounds = xgene360_histogram_drag_select.m_objBounds;
    
    var iWidth = 0;
    var iHeight = 0;
    
    if ( iCurX < objBounds.left )
    {
      iCurX = objBounds.left;
      iWidth = objInfo.m_objStartEvent.pageX - objBounds.left;
    }
    
    else if ( iCurX >= objBounds.left + objBounds.width )
    {
      iCurX = objInfo.m_objStartEvent.pageX;
      iWidth = objBounds.left + objBounds.width - objInfo.m_objStartEvent.pageX - 1;
    }
    
    else
    {
      if ( objInfo.dx < 0 )
      {
        iWidth = -objInfo.dx;
      }
      
      else
      {
        iCurX = objInfo.m_objStartEvent.pageX;
        iWidth = objInfo.dx;
      }
    }
    
    if ( iCurY < objBounds.top )
    {
      iCurY = objBounds.top;
      iHeight = objInfo.m_objStartEvent.pageY - objBounds.top;
    }
    
    else if ( iCurY >= objBounds.top + objBounds.height )
    {
      iCurY = objInfo.m_objStartEvent.pageY;
      iHeight = objBounds.top + objBounds.height - objInfo.m_objStartEvent.pageY - 1;
    }
    
    else
    {
      if ( objInfo.dy <= 0 )
      {
        iHeight = -objInfo.dy;
      }
      
      else
      {
        iCurY = objInfo.m_objStartEvent.pageY;
        iHeight = objInfo.dy;
      }  
    }
    
    var objMask = xgene360_histogram_drag_select.m_objMask;
    
    objMask.style.left = iCurX + 'px';
    objMask.style.width = iWidth + 'px';
    objMask.style.top = iCurY + 'px';
    objMask.style.height = iHeight + 'px';
    
    // check which bars are within the region
    for ( var i = 0; i < xgene360_histogram_drag_select.m_objBars.length; ++i )
    {
      var bPreserveSelection = objInfo.m_objStartEvent.shiftKey;
      var bReverseSelection = objInfo.m_objStartEvent.ctrlKey;
      
      if ( bReverseSelection )
      {
        // if we use reverse selection, preserve selection is also used
        bPreserveSelection = true;
      }
      
      if ( bPreserveSelection )
      {
        xgene360_histogram_drag_select.m_objSelectedBars[i] = xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i];
      }
      
      else
      {        
        xgene360_histogram_drag_select.m_objSelectedBars[i] = false;
      }
      
      var objBarBounds = xgene360_cu.geometry.getBounds( xgene360_histogram_drag_select.m_objBars[i] );
      
      if ( objBarBounds.left + objBarBounds.width >= iCurX && objBarBounds.left <= iCurX + iWidth && 
            objBarBounds.top <= iCurY + iHeight )
      {
        if ( bReverseSelection )
        {
          xgene360_histogram_drag_select.m_objSelectedBars[i] = !xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i];
        }
        
        else
        {
          // selected
          xgene360_histogram_drag_select.m_objSelectedBars[i] = true;
        }
      }
    }
    
    for ( var i = 0; i < xgene360_histogram_drag_select.m_objBars.length; ++i )
    {
      var objRange = xgene360_histogram_drag_select.m_objHistogram.m_objRange[i];
      
      xgene360_histogram_drag_select.m_objHistogram.m_objSelected[i] = xgene360_histogram_drag_select.m_objSelectedBars[i];
      
      if ( xgene360_histogram_drag_select.m_objSelectedBars[i] )
      {
        xgene360_histogram_drag_select.m_objBars[i].style.backgroundColor = '#0000ff';
        
        for ( var j = 0; j < objRange.length; ++j )
        {
          objRange[j].select( xgene360_histogram_drag_select.m_objHistogram.m_bTraitA );
        }
      }
      
      else
      {
        xgene360_histogram_drag_select.m_objBars[i].style.backgroundColor = xgene360_histogram_drag_select.m_objHistogram.m_objOriginalColor[i];
        
        for ( var j = 0; j < objRange.length; ++j )
        {
          objRange[j].deselect( xgene360_histogram_drag_select.m_objHistogram.m_bTraitA );
        }
      }
    }
    
    xgene360_histogram_drag_select.m_objHistogram.updateInfoLabel();    
  }
}
