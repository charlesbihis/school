function xgene360_plant( strPlantId, fTraitAValue, fTraitBValue )
{
  this.strPlantId      = strPlantId;
  this.fTraitAValue    = fTraitAValue;
  this.fTraitBValue    = fTraitBValue;
  
  this.m_objElement    = null;
  
  this.m_objLeftLeaf   = null;
  this.m_objRightLeaf  = null;
  this.m_objPot        = null;
  
  this.m_strTraitAImgId = null;
  this.m_strTraitBImgId = null;
  
  this.m_bSelected = false;
  this.m_bSelectionChanged = false;
  
  this.m_bTraitASelected = false;
  this.m_bTraitBSelected = false;
  
  this.m_objAssociatedSelectionTableRow = null;
  
  this.setTraitClass = function( bTraitA, iIndex )
  {
    var strIndex = "00" + ( iIndex + 1 );
    
    if ( bTraitA )
    {
      this.m_strTraitAImgId = "ll" + strIndex.substring( strIndex.length - 2, strIndex.length );
    }
    
    else
    {
      this.m_strTraitBImgId = "lr" + strIndex.substring( strIndex.length - 2, strIndex.length );
    }
  }
  
  this.attachToElement = function()
  {
    this.m_objElement = document.getElementById( this.strPlantId );
    
    this.m_objElement.onclick = null;
    this.m_objElement.onclick = this.onclickHandler.bind( this );
    
    var objImages = this.m_objElement.getElementsByTagName( 'IMG' );
    
    for ( var i = 0; i < objImages.length; ++i )
    {
      if ( objImages[i].className.indexOf( 'll' ) == 0 )
      {
        // left leaf
        this.m_objLeftLeaf = objImages[i];
      }
      
      else if ( objImages[i].className.indexOf( 'lr' ) == 0 )
      {
        // right leaf
        this.m_objRightLeaf = objImages[i];
      }
      
      else
      {
        this.m_objPot = objImages[i];
      }
    }
    
    this.m_bTraitASelected = false;
    this.m_bTraitBSelected = false;
    this.m_bSelectionChanged = true;
    
    this.update();
  }
  
  this.select = function( bTraitA )
  {
    if ( bTraitA )
    {
      this.m_bTraitASelected = true;
    }
    
    else
    {
      this.m_bTraitBSelected = true;
    }
    
    this.update();
  }
  
  this.deselect = function( bTraitA )
  {
    if ( bTraitA )
    {
      this.m_bTraitASelected = false;
    }
    
    else
    {
      this.m_bTraitBSelected = false;
    }
    
    this.update();
  }
  
  this.update = function()
  {
    if ( this.m_objElement != null )
    {
      if ( this.m_bTraitASelected || this.m_bTraitBSelected )
      {
        var strSrc = xgene360_plantshelf_img_manager.getImage( this.m_strTraitAImgId );
        
        this.replaceSrc( this.m_objLeftLeaf, strSrc );
                
        strSrc = xgene360_plantshelf_img_manager.getImage( this.m_strTraitBImgId );
          
        this.replaceSrc( this.m_objRightLeaf, strSrc );
        
        // pot
        if ( this.m_bTraitASelected && this.m_bTraitBSelected )
        {
          strSrc = xgene360_plantshelf_img_manager.getImage( 'pab' );
        }
        
        else if ( this.m_bTraitASelected )
        {
          strSrc = xgene360_plantshelf_img_manager.getImage( 'pa' );
        }
        
        else if ( this.m_bTraitBSelected )
        {
          strSrc = xgene360_plantshelf_img_manager.getImage( 'pb' );
        }
        
        this.replaceSrc( this.m_objPot, strSrc );
      }
      
      else
      {
        var strSrc = xgene360_plantshelf_img_manager.getImage( this.m_strTraitAImgId + '_a' );
          
        this.replaceSrc( this.m_objLeftLeaf, strSrc );
       
        strSrc = xgene360_plantshelf_img_manager.getImage( this.m_strTraitBImgId + '_a' );

        this.replaceSrc( this.m_objRightLeaf, strSrc );
        
        strSrc = xgene360_plantshelf_img_manager.getImage( 'pab_a' );
        
        this.replaceSrc( this.m_objPot, strSrc );
      }
      
      if ( this.m_bSelectionChanged )
      {
        if ( this.m_bSelected )
        {
          this.m_objElement.style.backgroundColor = '#0000ff';
        }
        
        else
        {
          this.m_objElement.style.backgroundColor = '';
        }
        
        this.m_bSelectionChanged = false;
      }
    }
  }
  
  this.replaceSrc = function( objImage, strSrc )
  {
    strSrc = strSrc.substring( strSrc.indexOf( '/' ) + 1 );
    
    if ( objImage.src.indexOf( strSrc ) == -1 )
    {
        objImage.src = strSrc;
    }
  }
  
  this.onclickHandler = function()
  {
    this.m_bSelected = !this.m_bSelected;
    this.m_bSelectionChanged = true;
    
    this.update();
    
    // notify the change
    xgene360_plantshelf.notifySelectionChange( this );
  }
}

function xgene360_plantshelf_img_manager() {}

xgene360_plantshelf_img_manager.objImageList = {
  'spin' : 'spin.gif',
  'tl' : 'shelf/shelf_topleft.gif',
  'tr' : 'shelf/shelf_topright.gif',
  'sl' : 'shelf/shelf_sideleft.gif',
  'sr' : 'shelf/shelf_sideright.gif',
  'bl' : 'shelf/shelf_bottomleft.gif',
  'br' : 'shelf/shelf_bottomright.gif',
  'l'  : 'shelf/shelf_level.gif',
  'pa' : 'pots/pot_a.gif',
  'pb' : 'pots/pot_b.gif',
  'pab': 'pots/pot_ab.gif',
  'pa_a' : 'pots_alpha/pot_a.gif',
  'pb_a' : 'pots_alpha/pot_b.gif',
  'pab_a': 'pots_alpha/pot_ab.gif'
};

for ( var i = 0; i < 11; ++i )
{
  var strIndex = "00" + ( i + 1 );
  strIndex = strIndex.substring( strIndex.length - 2, strIndex.length );
  
  xgene360_plantshelf_img_manager.objImageList['ll' + strIndex ] = 'leaf/left/leaf' + strIndex + '_a.gif';
  xgene360_plantshelf_img_manager.objImageList['lr' + strIndex ] = 'leaf/right/leaf' + strIndex + '_b.gif';
  xgene360_plantshelf_img_manager.objImageList['ll' + strIndex + '_a'] = 'leaf_alpha/left/leaf' + strIndex + '_a.gif';
  xgene360_plantshelf_img_manager.objImageList['lr' + strIndex + '_a'] = 'leaf_alpha/right/leaf' + strIndex + '_b.gif';
}

xgene360_plantshelf_img_manager.strImagePathBase = './images/';
  
xgene360_plantshelf_img_manager.getImage = function( strImageId )
{
  return xgene360_plantshelf_img_manager.strImagePathBase + xgene360_plantshelf_img_manager.objImageList[ strImageId ];
}

xgene360_plantshelf_img_manager.preloadImages = function()
{
  var objInvisibleContainer = document.createElement( 'DIV' );
  
  for ( strKey in xgene360_plantshelf_img_manager.objImageList )
  {
    objInvisibleContainer.appendChild( xgene360_cu.preloadImage( xgene360_plantshelf_img_manager.strImagePathBase + xgene360_plantshelf_img_manager.objImageList[strKey] ) );
  }
  
  document.body.appendChild( objInvisibleContainer );
}

xgene360_plantshelf_img_manager.bDisplayed = false;

xgene360_plantshelf_img_manager.iImageCount = 0;
xgene360_plantshelf_img_manager.iLoadedCount = 0;

xgene360_plantshelf_img_manager.objStartTime = null;

xgene360_plantshelf_img_manager.iMinLoadingDelay = 1000;
xgene360_plantshelf_img_manager.bInitialLoading = true;

xgene360_plantshelf_img_manager.onloadHandler = function()
{
  xgene360_plantshelf_img_manager.iLoadedCount++;
    
  if ( ( xgene360_plantshelf_img_manager.iLoadedCount >= xgene360_plantshelf_img_manager.iImageCount && !xgene360_plantshelf_img_manager.bDisplayed ) ||
          !xgene360_plantshelf_img_manager.bInitialLoading )
  {
    var iTimeElapsed = new Date().getTime() - xgene360_plantshelf_img_manager.objStartTime.getTime();
    
    if ( iTimeElapsed <= xgene360_plantshelf_img_manager.iMinLoadingDelay )
    {
      setTimeout( 'xgene360_plantshelf_img_manager.onloadHandler()', xgene360_plantshelf_img_manager.iMinLoadingDelay - iTimeElapsed );
      return;
    }
    
    var objTables = xgene360_plantshelf.objCanvas.getElementsByTagName( 'TABLE' );
    
    for ( var i = 0; i < objTables.length; ++i )
    {
      if ( objTables[i].className == 'spinner' )
      {
        objTables[i].style.visibility = 'hidden';
      }
    }
    
    // show the container
    xgene360_plantshelf.objPlantShelf.style.visibility = 'visible';
    xgene360_plantshelf_img_manager.bDisplayed = true;
    xgene360_plantshelf_img_manager.bInitialLoading = false;
  }
}

function xgene360_plantshelf() {}


////////////////////////////////////////////////////////////
//
// member variables
//
////////////////////////////////////////////////////////////

xgene360_plantshelf.iXCount = 10;

xgene360_plantshelf.iShelfBorderWidth = 10;
xgene360_plantshelf.iPlantWidth = 30;

xgene360_plantshelf.strPlantShelfId = null;

xgene360_plantshelf.objPlantShelf = null;
xgene360_plantshelf.objCanvas = null;

xgene360_plantshelf.iCurrentGeneration = 0;

////////////////////////////////////////////////////////////
//
// methods
//
////////////////////////////////////////////////////////////

xgene360_plantshelf.render = function( strCanvas, objPlants )
{
  xgene360_plantshelf.strPlantShelfId = strCanvas + '_shelf';
  
  // canvas related stuff
  var objCanvas = xgene360_cu.Element( strCanvas );
  
  // to prevent IE memory leak
  objImages = objCanvas.getElementsByTagName( 'IMG' );
  
  for ( var i = 0; i < objImages.length; ++i )
  {
    objImages.onload = null;
  }
  
  objDivs = objCanvas.getElementsByTagName( 'DIV' );
  
  for ( var i = 0; i < objDivs.length; ++i )
  {
    objDivs.onclick = null;
    objDivs.onmouseover = null;
    objDivs.onmouseout = null;
  }

  objCanvas.style.width = ( xgene360_plantshelf.iShelfBorderWidth * 2 + xgene360_plantshelf.iPlantWidth * 10 ) + 'px';
  objCanvas.style.position = 'relative';

  // create the plant shelf table
  
  // comment: i can use DOM methods.. but DOM methods is waaaaaaaaay slower than using innerHTML
  // and frankly.. i would prefer speed over programming style since what visible to the user is the loading time
  // not the coding style (http://www.quirksmode.org/dom/innerhtml.html)
  
  var iImageCount = 0;
  var iHeight = 0;
  
  var strHTML = '';
  
  strHTML +=  '<table id="' + xgene360_plantshelf.strPlantShelfId + '" cellpadding="0" cellspacing="0" border="0" class="plantshelf">' +
    		      '<tr>' + 
    		      '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'tl' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				  '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'l' ) + '" width="' + xgene360_plantshelf.iPlantWidth * 10 + '" height="11" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				  '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'tr' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    			    '</tr>';
  
  iImageCount += 3;
  iHeight += 11;
  
  for ( var i = 0; i < objPlants.length; ++i )
  {
    if ( i % xgene360_plantshelf.iXCount == 0 )
    {
      strHTML +=  '<tr>' +
                  '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'sl' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
                  '<td width="' + ( xgene360_plantshelf.iXCount * xgene360_plantshelf.iPlantWidth ) + '">';
                  
      iImageCount += 1;
    }
    
    var strPlantDescription = '';
          
    strPlantDescription = 'Trait A: ' + objPlants[i].fTraitAValue.toFixed( 2 ) + '<br />' +
                          'Trait B: ' + objPlants[i].fTraitBValue.toFixed( 2 );


    // determine which region this plant belongs to 
    
    strHTML +=  '<div class="p" id="' + objPlants[i].strPlantId + '" onmouseover="xgene360_cu.tip.show( \'' + strPlantDescription + '\', \'#90ee90\' );" onmouseleave="xgene360_cu.tip.hide();" onmouseout="if ( !xgene360_cu.IE ) { xgene360_cu.tip.hide(); }">' +
                '<img class="pot" onload="xgene360_plantshelf_img_manager.onloadHandler();" />' +
                '<img class="ll" onload="xgene360_plantshelf_img_manager.onloadHandler();" />' +
    			      '<img class="lr" onload="xgene360_plantshelf_img_manager.onloadHandler();" />' +
    			      '</div>';
    
    iImageCount += 3;
      
    if ( ( i + 1 ) % xgene360_plantshelf.iXCount == 0 || i == objPlants.length - 1 )
    {
      strHTML +=  '</td>' +
                  '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'sr' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    			        '</tr>';
    	
    	iImageCount += 1;
    	iHeight += 29;
    	
    	if ( i == objPlants.length - 1 )
      {
        strHTML +=  '<tr>' +
    		            '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'bl' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				        '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'l' ) + '" width="' + xgene360_plantshelf.iPlantWidth * 10 + '" height="11" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				        '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'br' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    			          '</tr>';
    			          
    			iImageCount += 3;
    			iHeight += 19;
      }
      
      else
      {
        strHTML +=  '<tr>' +
    		            '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'tl' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				        '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'l' ) + '" width="' + xgene360_plantshelf.iPlantWidth * 10 + '" height="11" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    				        '<td><img src="' + xgene360_plantshelf_img_manager.getImage( 'tr' ) + '" onload="xgene360_plantshelf_img_manager.onloadHandler();" /></td>' +
    			          '</tr>';
    			          
    		iImageCount += 3;
    		iHeight += 11;
      }
    }
  }
  
  strHTML +=  '</table>';
  
  xgene360_plantshelf_img_manager.bDisplayed = false;
  xgene360_plantshelf_img_manager.iImageCount = iImageCount;
  xgene360_plantshelf_img_manager.iLoadedCount = 0;
  xgene360_plantshelf_img_manager.objStartTime = new Date();
  
  objCanvas.style.height = iHeight + 'px';
  
  strHTML =  '<table class="spinner" cellpadding="0" cellspacing="0" border="0" style="position: absolute; left: 1px; top: 1px; width: ' + ( parseInt( objCanvas.style.width ) - 1 ) + 'px; height: ' + ( parseInt( objCanvas.style.height ) - 1 ) + 'px; z-index: 100; border: 1px solid #000000;">' +
              '<tr>' +
              '<td style="text-align: center; vertical-align: middle;"><img src="' + xgene360_plantshelf_img_manager.getImage( 'spin' ) + '" /></td>' +
              '</tr>' +
              '</table>' + strHTML;
  
  objCanvas.innerHTML = strHTML;
  
  for ( var i = 0; i < objPlants.length; ++i )
  {
    objPlants[i].attachToElement();
  }

  xgene360_plantshelf.objCanvas = objCanvas;
  xgene360_plantshelf.objPlantShelf = xgene360_cu.Element( xgene360_plantshelf.strPlantShelfId );
  
  setTimeout( 'xgene360_plantshelf_img_manager.onloadHandler()', xgene360_plantshelf_img_manager.iMinLoadingDelay );
}

xgene360_plantshelf.objListOfSelectPlantsTable = null;
xgene360_plantshelf.objSelectedPlants = new Array();

xgene360_plantshelf.notifySelectionChange = function( objPlant )
{
  if ( xgene360_plantshelf.objListOfSelectPlantsTable != null )
  {
    var objTable = xgene360_plantshelf.objListOfSelectPlantsTable;
    
    if ( objPlant.m_bSelected )
    {
      if ( objTable.rows.length == 2 )
      {
        // is the cell indicating there is no selection or is there actually a selection?
        if ( objTable.rows[1].cells.length == 1 )
        {
          // this is a cell indicating that there is no selection, so remove it
          objTable. deleteRow( 1 );
        };
      }
      
      // add this plant to selected plants
      var objNewRow = objTable.insertRow( objTable.rows.length );
      
      var objGenerationCell = objNewRow.insertCell( 0 );
      objGenerationCell.appendChild( document.createTextNode( xgene360_plantshelf.iCurrentGeneration ) );
      
      var objTraitACell = objNewRow.insertCell( 1 );
      objTraitACell.appendChild( document.createTextNode( objPlant.fTraitAValue.toFixed( 1 ) ) );
      
      var objTraitBCell = objNewRow.insertCell( 2 );
      objTraitBCell.appendChild( document.createTextNode( objPlant.fTraitBValue.toFixed( 1 ) ) );
      
      objPlant.m_objAssociatedSelectionTableRow = objNewRow;
      
      xgene360_plantshelf.objSelectedPlants.push( objPlant );
    }
    
    else
    {
      // delete this plant from the selection table
      if ( objPlant.m_objAssociatedSelectionTableRow != null )
      {
        objTable.deleteRow( objPlant.m_objAssociatedSelectionTableRow.rowIndex );
        objTable.m_objAssociatedSelectionTableRow = null;
      }
      
      if ( objTable.rows.length == 1 )
      {
        var objNewRow = objTable.insertRow( 1 );
        var objNoneCell = objNewRow.insertCell( 0 );
        objNoneCell.appendChild( document.createTextNode( 'None' ) );
        objNoneCell.colSpan = 3;
      }
      
      // remove it from the array
      for ( var i = 0; i < xgene360_plantshelf.objSelectedPlants.length; ++i )
      {
        if ( xgene360_plantshelf.objSelectedPlants[i] == objPlant )
        {
          xgene360_plantshelf.objSelectedPlants.splice( i, 1 );
        }
      }
    }
    
    xgene360_plantshelf.updateSelectedPlantsMeanAndVariance();
  }
}

xgene360_plantshelf.objListOfSelectedPlantsMeanAndVariance = null;

xgene360_plantshelf.updateSelectedPlantsMeanAndVariance = function()
{
  var objTable = xgene360_plantshelf.objListOfSelectedPlantsMeanAndVariance;
  
  if ( objTable != null )
  {
    var fMeanA = 0.0;
    var fVarianceA = 0.0;
    var fMeanB = 0.0;
    var fVarianceB = 0.0;
    
    var iNumberOfPlants = xgene360_plantshelf.objSelectedPlants.length;
    
    for ( var i = 0; i < iNumberOfPlants; ++i )
    {
      fMeanA += xgene360_plantshelf.objSelectedPlants[i].fTraitAValue;
      fMeanB += xgene360_plantshelf.objSelectedPlants[i].fTraitBValue; 
    }
    
    fMeanA /= iNumberOfPlants;
    fMeanB /= iNumberOfPlants;
    
    for ( var i = 0; i < iNumberOfPlants; ++i )
    {
      fVarianceA += ( xgene360_plantshelf.objSelectedPlants[i].fTraitAValue - fMeanA ) * ( xgene360_plantshelf.objSelectedPlants[i].fTraitAValue - fMeanA );
      fVarianceB += ( xgene360_plantshelf.objSelectedPlants[i].fTraitBValue - fMeanB ) * ( xgene360_plantshelf.objSelectedPlants[i].fTraitBValue - fMeanB );
    }  
    
    fVarianceA = fVarianceA / ( iNumberOfPlants - 1 );
    fVarianceB /= ( iNumberOfPlants - 1 );
    
    for ( var i = 1; 1 < objTable.rows.length; ++i )
    {
      objTable.deleteRow( 1 );
    }
    
    if ( iNumberOfPlants == 0 )
    {
      var objRow = objTable.insertRow( 1 );
      objRow.colSpan = 3;
      objRow.appendChild( document.createTextNode( 'None' ) );
    }
    
    else
    {
      var objRow = objTable.insertRow( 1 );
      
      var objTraitCell = objRow.insertCell( 0 );
      objTraitCell.appendChild( document.createTextNode( 'TraitA' ) );
      
      var objMeanCell = objRow.insertCell( 1 );
      objMeanCell.appendChild( document.createTextNode( fMeanA.toFixed( 1 ) ) );
      
      var objVarianceCell = objRow.insertCell( 2 );
      
      if ( isNaN( fVarianceA ) )
      {
        objVarianceCell.appendChild( document.createTextNode( 'N/A' ) );
      }
      
      else
      {
        objVarianceCell.appendChild( document.createTextNode( fVarianceA.toFixed( 1 ) ) );
      }
      
      objRow = objTable.insertRow( 2 );
      
      objTraitCell = objRow.insertCell( 0 );
      objTraitCell.appendChild( document.createTextNode( 'TraitB' ) );
      
      objMeanCell = objRow.insertCell( 1 );
      objMeanCell.appendChild( document.createTextNode( fMeanB.toFixed( 1 ) ) );
      
      objVarianceCell = objRow.insertCell( 2 );
      
      if ( isNaN( fVarianceB ) )
      {
        objVarianceCell.appendChild( document.createTextNode( 'N/A' ) );
      }
      
      else
      {
        objVarianceCell.appendChild( document.createTextNode( fVarianceB.toFixed( 1 ) ) );
      }
    }
  } 
}
