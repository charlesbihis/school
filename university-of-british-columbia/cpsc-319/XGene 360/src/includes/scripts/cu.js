var xgene360_cu = new Object();

// user agent related stuff
xgene360_cu.USER_AGENT = navigator.userAgent.toLowerCase();
xgene360_cu.IE = ( xgene360_cu.USER_AGENT.indexOf( 'msie' ) != -1 );
xgene360_cu.NS = !xgene360_cu.IE;
xgene360_cu.IE_CM = xgene360_cu.IE && document.compatMode && document.compatMode != 'BackCompat';
xgene360_cu.SAFARI = xgene360_cu.USER_AGENT.indexOf( 'safari' ) != -1;
xgene360_cu.IE55 = xgene360_cu.IE && xgene360_cu.USER_AGENT.match( 'msie 5.5' ) != null;
xgene360_cu.FIREFOX = xgene360_cu.USER_AGENT.indexOf( 'firefox' ) != -1;
xgene360_cu.OPERA = window.opera;

////////////////////////////////////////////////////////////
//
// element related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.Element = function( objIdOrElement )
{
  return ( typeof( objIdOrElement ) == 'string' ) ? xgene360_cu.Id( objIdOrElement ) : objIdOrElement;
}

xgene360_cu.Id = function( strId )
{
  return document.getElementById( strId );
}

xgene360_cu.setContent = function( objIdOrElement, strHTML )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  if ( xgene360_cu.stringLength( strHTML ) == 0 )
  {
    strHTML = '';
  }
  
  objElement.innerHTML = strHTML;
}

xgene360_cu.hideElement = function( objIdOrElement )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  objElement.style.visibility = 'hidden';
}

xgene360_cu.showElement = function( objIdOrElement )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  objElement.style.visibility = 'visible';
}

xgene360_cu.setVisibility = function( objIdOrElement, bVisible )
{
  if ( bVisible )
  {
    xgene360_cu.showElement( objIdOrElement );
  }
  
  else
  {
    xgene360_cu.hideElement( objIdOrElement );
  }
}

xgene360_cu.setDisplay = function( objIdOrElement, bDisplay )
{
  var objElement = xgene360_cu.Element( objIdOrElement );

  if ( bDisplay )
  {
    objElement.style.display = 'block';
  }
  
  else
  {
    objElement.style.display = 'none';
  }
}

xgene360_cu.toggleDisplay = function( objIdOrElement )
{
  var objElement = xgene360_cu.Element( objIdOrElement );

  xgene360_cu.setDisplay( objElement, objElement.style.display == 'none' );
}

xgene360_cu.selectDisplay = function( objIdOrElement, arrIdsOrElements )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  if ( objElement[ objElement.selectedIndex ].value != "" )
  {
    var objSelectedElement = xgene360_cu.Element( objElement[ objElement.selectedIndex ].value );
  
    objSelectedElement.style.display = 'block';

    for ( var i = 0; i < arrIdsOrElements.length; i++ )
    {
      var objInnerElement = xgene360_cu.Element( arrIdsOrElements[i] );
      
      if( objInnerElement != objSelectedElement )
      {
        objInnerElement.style.display = 'none';
      }
    }
  }
}

xgene360_cu.setOpacity = function( objIdOrElement, fOpacity )
{
  if ( fOpacity < 0 )
	{
		fOpacity = 0;
	}
	  
	else if ( fOpacity > 100 )
	{
		fOpacity = 100;
	}
	
	var objElement = xgene360_cu.Element( objIdOrElement );

	objElement.style.opacity = fOpacity / 100;
	objElement.style.MozOpacity = fOpacity / 100;
	objElement.style.KhtmlOpacity = fOpacity / 100;
	objElement.style.filter = "alpha(opacity=" + fOpacity + ")";
}

xgene360_cu.checkAll = function( objIdOrElementMaster, strCheckboxId )
{
  var objMaster = xgene360_cu.Element( objIdOrElementMaster );
  var bChecked = objMaster.checked;
  
  var objInputElements = document.getElementsByTagName( 'INPUT' );
  
  for ( var i = 0; i < objInputElements.length; ++i )
  {
    if ( objInputElements[i].type == 'checkbox' &&
          objInputElements[i].name == strCheckboxId )
    {
      objInputElements[i].checked = bChecked;
    }
  }
}

xgene360_cu.countText = function( objIdOrElementField, objIdOrElementCountField, intMaxLimit )
{
  var objElementField = xgene360_cu.Element( objIdOrElementField );
  var objElementCounter = xgene360_cu.Element( objIdOrElementCountField );
  
  if ( objElementField.value.length > intMaxLimit )
  {
    objElementField.value = objElementField.value.substring( 0, intMaxLimit );
  }
  
  objElementCounter.value = intMaxLimit - objElementField.value.length;
}

xgene360_cu.useHandCursor = function( objIdOrElement )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  xgene360_cu.IE ? objElement.style.cursor = 'hand' : objElement.style.cursor = 'pointer';
}

xgene360_cu.useRegularCursor = function( objIdOrElement )
{
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  objElement.style.cursor = '';
}

xgene360_cu.setLocation = function( strLocation )
{
  window.location.href = strLocation;
}

xgene360_cu.stopPropagation = function( e )
{
  xgene360_cu.using( 'event' );
  
  xgene360_cu.event.getEvent( e ).stopPropagation();
}

xgene360_cu.getParentNode = function( objIdOrElement, strTagName )
{
  if ( objIdOrElement == null )
  {
    return null;
  }
  
  var objElement = xgene360_cu.Element( objIdOrElement );
  
  if ( objElement.nodeType == 1 && objElement.tagName.toLowerCase() == strTagName.toLowerCase() )
  {
    return objElement;
  }
  
  else
  {
    return xgene360_cu.getParentNode( objIdOrElement.parentNode, strTagName );
  }
}

xgene360_cu.getInnerText = function( obj )
{
  if ( typeof( obj ) == 'string' )
  {
    return obj;
  }
  
  if ( typeof( obj ) == 'undefined' ) 
  {
    return obj;
  }
  
  // for IE
  if ( obj.innerText )
  {
    return obj.innerText;
  }
  
  var strText = '';
  
  var objChildNodes = obj.childNodes;
  
  for ( var i = 0; i < objChildNodes.length; ++i )
  {
    switch ( objChildNodes[i].nodeType )
    {
      case 1: // ELEMENT_NODE
      
        strText += xgene360_cu.getInnerText( objChildNodes[i] );
        break;
        
      case 3: // TEXT_NODE
        
        strText += objChildNodes[i].nodeValue;
        break;
    }
  }
  
  return strText;
}

xgene360_cu.redirect = function( strLocation, iDelay )
{
  setTimeout( "window.location='" + strLocation + "'", iDelay );
}

////////////////////////////////////////////////////////////
//
// function related stuff
//
////////////////////////////////////////////////////////////

Function.prototype.bind = function( object )
{
  var objMethod = this;
  
  return function () { objMethod.apply( object, arguments ); };
}

////////////////////////////////////////////////////////////
//
// component related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component = new Object();

xgene360_cu.using = function( strComponent )
{
  var objLoader = xgene360_cu.component[ strComponent ];
  
  if ( !objLoader.m_bLoaded )
  {
    objLoader();
    objLoader.m_bLoaded = true;
  }
}

////////////////////////////////////////////////////////////
//
// string related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.stringExtension = function()
{
  String.prototype.trim = function()
  {
    return this.trimStart().trimEnd();
  }

  String.prototype.trimStart= function()
  {
    return this.replace(/^\s+/g, '');
  }

  String.prototype.trimEnd = function()
  {
    return this.replace(/\s+$/g, '');
  }

  String.prototype.escape = function( bHTMLOnly )
  {
    var str = this;
    
    str = str.replace( /\&/g, '&amp;' );
    str = str.replace( /\</g, '&lt;' );
    str = str.replace( /\>/g, '&gt;' );
    str = str.replace( /\"/g, '&quot;' );
    str = str.replace( /\xA0/g, '&nbsp;' );
    
    if ( bHTMLOnly )
    {
      str = str.replace( /\n/g, '<br />' );
      str = str.replace( /  /g, ' &nbsp;' );
      str = str.replace( /&nbsp; /g, '&nbsp;&nbsp;' );
    };
    
    return str;
  }

  String.prototype.unescape = function( bHTMLOnly )
  {
    var str = this;
    
    str = str.replace( /&amp;/g, '&' );
    str = str.replace( /&lt;/g, '<' );
    str = str.replace( /&gt;/g, '>' );
    str = str.replace( /&quot;/g, '"' );
    str = str.replace( /&nbsp;/g, ' ' );
    
    if ( bHTMLOnly )
    {
      str = str.replace( /<br \/>/g, '\n' );
      str = str.replace( /<br>/g, '\n' );
    }
    
    return s;
  }
}

////////////////////////////////////////////////////////////
//
// event related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.event = function()
{
  xgene360_cu.event = new Object();
  
  xgene360_cu.event.addDOMListener = function( objSourceElement, strEventName, objListener )
  {
    var strShortEventName = strEventName.replace( /on/, '' );
    
    if ( xgene360_cu.IE )
    {
      objSourceElement.attachEvent( strEventName, objListener );
    }
    
    else
    {
      objSourceElement.addEventListener( strShortEventName, objListener, false );
    }
  }
  
  xgene360_cu.event.removeDOMListener = function( objSourceElement, strEventName, objListener )
  {
    var strShortEventName = strEventName.replace( /on/, '' );
    
    if ( xgene360_cu.IE )
    {
      objSourceElement.detachEvent( strEventName, objListener );
    }
    
    else
    {
      objSourceElement.removeEventListener( strShortEventName, objListener, false );
    }
  }
  
  xgene360_cu.event.getEvent = function( e )
  {
    return new xgene360_Event( e );
  }
  
  xgene360_cu.event.disableSelection = function()
  {
    if ( xgene360_cu.IE || xgene360_cu.SAFARI )
    {
      document.ondragstart = function() { return false; };
      document.onselectstart = function() { return false; };
    }
    
    if ( xgene360_cu.IE )
    {
      var bAllowSelection = function( e )
      {
        var objEvent = xgene360_cu.event.getEvent( e );
        objEvent.stopPropagation();
        
        return true;
      }
    }
    
    var objInputElements = document.getElementsByTagName( 'INPUT' );
    
    for ( var i = 0; i < objInputElements.length; ++i )
    {
      if ( objInputElements[i].type == 'text' )
      {
        objInputElements[i].onselectstart = bAllowSelection;
      }
    }
    
    var objTextAreas = document.getElementsByTagName( 'TEXTAREA' );
    
    for ( var i = 0; i < objTextAreas.length; ++i )
    {
      objTextAreas[i].onselectstart = bAllowSelection;
    }
  }
  
  xgene360_cu.event.disableContextMenu = function()
  {
    document.body.oncontextmenu = function() { return false; };
  }
  
  xgene360_Event = function( e )
  {
    var objEvent = e ? e : window.event;
    
    this.browserEvent = objEvent;
    this.target = ( objEvent.target && objEvent.target.nodeType == 3 ) ? objEvent.target.parentNode : ( objEvent.target ) ? objEvent.target : objEvent.srcElement;
    this.type = objEvent.type;
    
    this.posX = ( xgene360_cu.IE ) ? objEvent.x : objEvent.layerX;
    this.posY = ( xgene360_cu.IE ) ? objEvent.y : objEvent.layerY;
    
    var objBody = document.body;
    var objPE = objBody.parentElement;
    
    if ( xgene360_cu.IE )
    {
      this.pageX = objEvent.clientX + objBody.scrollLeft - objBody.clientLeft;
      this.pageY = objEvent.clientY + objBody.scrollTop - objBody.clientTop;
    }
    
    if ( objPE && objPE.clientLeft )
    {
      this.pageX += objPE.scrollLeft - objPE.clientLeft;
      this.pageY += objPE.scrollTop - objPE.clientTop;
    }
    
    else
    {
      this.pageX = objEvent.pageX;
      this.pageY = objEvent.pageY;
    }
    
    if ( xgene360_cu.IE && !xgene360_cu.OPERA )
    {
      if ( xgene360_cu.IE_CM )
      {
        this.windowWidth = document.documentElement.clientWidth;
        this.windowHeight = document.documentElement.clientHeight;
      }
      
      else
      {
        this.windowWidth = objBody.clientWidth;
        this.windowHeight = objBody.clientHeight;
      }
    }
    
    else
    {
      this.windowWidth = window.innerWidth;
      this.windowHeight = window.innerHeight;
    }
    
    this.screenX = objEvent.screenX;
    this.screenY = objEvent.screenY;
    this.ctrlKey = objEvent.ctrlKey;
    this.shiftKey = objEvent.shiftKey;
    
    if ( this.type == 'keydown' || this.type == 'keyup' )
    {
      this.keyCode = objEvent.keyCode;
    }
    
    if ( this.type == 'keypress' )
    {
      this.keyCode = xgene360_cu.IE ? objEvent.keyCode : objEvent.charCode;
    }
    
    this.stopPropagation = function()
    {
      xgene360_cu.IE ? this.browserEvent.cancelBubble = true : this.browserEvent.stopPropagation();
    }
    
    this.preventDefault = function()
    {
      xgene360_cu.IE ? this.browserEvent.returnValue = false : this.browserEvent.preventDefault();
    }
  }
}

////////////////////////////////////////////////////////////
//
// tip related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.tip = function()
{
  xgene360_cu.using( 'event' );
 
  xgene360_cu.tip = new Object(); 
  
  xgene360_cu.tip.m_iOffsetX = 12;
  xgene360_cu.tip.m_iOffsetY = 10;
  
  xgene360_cu.tip.m_bDisplayed = false;
  xgene360_cu.tip.m_bEnabled = true;
  
  xgene360_cu.tip.m_strId = 'tip';
  
  xgene360_cu.tip.m_objTip = null;
  
  xgene360_cu.tip._internalInit = function( e )
  {
    var objTip = document.createElement( 'DIV' );
    
    objTip.id = xgene360_cu.tip.m_strId;
    objTip.style.position = 'absolute';
    objTip.style.width = '150px';
    objTip.style.borderWidth = '1px';
    objTip.style.borderStyle = 'solid';
    objTip.style.borderColor = '#000000';
    objTip.style.padding = '2px';
    objTip.style.backgroundColor = '#ffffe0';
    objTip.style.visibility = 'hidden';
    objTip.style.zIndex = 100;
    objTip.style.textAlign = 'left';
    
    document.body.appendChild( objTip );
    
    xgene360_cu.tip.m_objTip = objTip;
  }
  
  xgene360_cu.event.addDOMListener( window, 'onload', xgene360_cu.tip._internalInit );
  
  xgene360_cu.tip.enable = function()
  {
    xgene360_cu.tip.m_bEnabled = true;
  }
  
  xgene360_cu.tip.disable = function()
  {
    xgene360_cu.tip.m_bEnabled = false;
  }
  
  xgene360_cu.tip.show = function( strText, strColor, iWidth )
  { 
    var objTip = xgene360_cu.tip.m_objTip;
    
    if ( typeof( strColor ) != 'undefined' )
    {
      objTip.style.backgroundColor = strColor;
    }
    
    if ( typeof( iWidth ) != 'undefined' )
    {
      objTip.style.width = iWidth;
    }
        
    objTip.innerHTML = strText;
    
    xgene360_cu.tip.m_bDisplayed = true;
  }
  
  xgene360_cu.tip.hide = function()
  {
    var objTip = xgene360_cu.tip.m_objTip;
    
    xgene360_cu.tip.m_bDisplayed = false;
    
    objTip.style.visibility = 'hidden';
  }
  
  xgene360_cu.tip.move = function( e )
  {
    if ( xgene360_cu.tip.m_bDisplayed && xgene360_cu.tip.m_bEnabled )
    {    
      var objTip = xgene360_cu.tip.m_objTip;
      var objEvent = xgene360_cu.event.getEvent( e );
      
      var rightEdge = objEvent.windowWidth - objEvent.pageX - xgene360_cu.tip.m_iOffsetX;
      var bottomEdge = objEvent.windowHeight - objEvent.pageY - xgene360_cu.tip.m_iOffsetY;
      
      var leftEdge = ( xgene360_cu.tip.m_iOffsetX < 0 ) ? xgene360_cu.tip.m_iOffsetX * -1 : -1000;
      
      if ( rightEdge < objTip.offsetWidth )
      {
        objTip.style.left = objEvent.pageX - objTip.offsetWidth + 'px';
      }
      
      else if ( objEvent.pageX < leftEdge )
      {
        objTip.style.left = '5px';
      }
      
      else
      {
        objTip.style.left = objEvent.pageX + xgene360_cu.tip.m_iOffsetX + 'px';
      }
      
      if ( bottomEdge < objTip.offsetHeight )
      {
        objTip.style.top = objEvent.pageY - objTip.offsetHeight - xgene360_cu.tip.m_iOffsetY + 'px';
      }
      
      else
      {
        objTip.style.top = objEvent.pageY + xgene360_cu.tip.m_iOffsetY + 'px';
      }
      
      objTip.style.visibility = 'visible';
    }
  }
  
  xgene360_cu.event.addDOMListener( document, 'onmousemove', xgene360_cu.tip.move );
}

////////////////////////////////////////////////////////////
//
// drag selection related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.drag = function()
{
  xgene360_cu.using( 'event' );
  xgene360_cu.using( 'geometry' );
  
  xgene360_cu.drag = new Object();
  
  xgene360_cu.drag.m_bDragging = false;
  
  xgene360_cu.drag.m_bUseClick = true;
  
  xgene360_cu.drag.m_objDragInfo = new Object();
    
  xgene360_cu.drag.start = function( objEvent, objContainer )
  {
    if ( xgene360_cu.drag.m_bDragging )
    {
      return;
    }
    
    xgene360_cu.drag.m_objDragInfo.m_objStartEvent = objEvent;
    xgene360_cu.drag.m_objDragInfo.m_objCurrentEvent = objEvent;
    
    if ( xgene360_cu.tip != null )
    {
      xgene360_cu.tip.disable();
    }
    
    xgene360_cu.drag._internalRegisterEventListeners();
    
    if ( xgene360_cu.drag.m_bUseClick )
    {
      xgene360_cu.drag.m_objDragInfo.dx = 0;
      xgene360_cu.drag.m_objDragInfo.dy = 0;
      
      xgene360_cu.drag.onmove( xgene360_cu.drag.m_objDragInfo );
    }
  }
  
  xgene360_cu.drag.stop = function()
  {
    xgene360_cu.drag._internalInit();
    xgene360_cu.drag._internalUnregisterEventListeners();
    
    if ( xgene360_cu.tip != null )
    {
      xgene360_cu.tip.enable();
    }
  }
  
  xgene360_cu.drag._internalInit = function()
  {
    xgene360_cu.drag.m_bDragging = false;
    xgene360_cu.drag.onstart = xgene360_cu.drag.onstop = xgene360_cu.drag.onmove = function() { };
    xgene360_cu.drag.m_objDragInfo = new Object();
  }
  
  xgene360_cu.drag._internalRegisterEventListeners = function()
  {
    var objNode = document.body.parentNode;
    
    objNode.onmouseup = xgene360_cu.drag._internalHandleMouseUp;
    objNode.onmousemove = xgene360_cu.drag._internalHandleMouseMove;
    
    if ( xgene360_cu.IE )
    {
      objNode.ondragstart = function() { return false; };
    }
    
    else
    {
      objNode.onmousedown = function() { return false; };
    }
  }
  
  xgene360_cu.drag._internalUnregisterEventListeners = function()
  {
    var objNode = document.body.parentNode;
    
    objNode.onmouseup = null;
    objNode.onmousemove = null;
    
    if ( xgene360_cu.IE )
    {
      objNode.ondragstart = null;
    }
    
    else
    {
      objNode.onmousedown = null;
    }
  }
  
  xgene360_cu.drag._internalHandleMouseUp = function( e )
  {
    var objEvent = xgene360_cu.event.getEvent( e );
    var objInfo = xgene360_cu.drag.m_objDragInfo;
    objInfo.m_objCurrentEvent = objEvent;
    
    if ( xgene360_cu.drag.m_bDragging || xgene360_cu.drag.m_bUseClick )
    {
      xgene360_cu.drag.onstop( objInfo );
    }
    
    xgene360_cu.drag.stop(); 
  }
  
  xgene360_cu.drag._internalHandleMouseMove = function( e )
  {
    var objEvent = xgene360_cu.event.getEvent( e );
    var objInfo = xgene360_cu.drag.m_objDragInfo;
    objInfo.m_objCurrentEvent = objEvent;
    
    objInfo.dx = objInfo.m_objCurrentEvent.screenX - objInfo.m_objStartEvent.screenX - 1;
    objInfo.dy = objInfo.m_objCurrentEvent.screenY - objInfo.m_objStartEvent.screenY - 1;
    
    if ( !xgene360_cu.drag.m_bDragging )
    {
      xgene360_cu.drag.onstart( xgene360_cu.drag.m_objDragInfo );
      xgene360_cu.drag.m_bDragging = true;
    }
    
    else
    {
      xgene360_cu.drag.onmove( objInfo );
    }
  }
}

////////////////////////////////////////////////////////////
//
// geometry related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.geometry = function()
{
  xgene360_cu.geometry = new Object();
  
  xgene360_cu.geometry.getBounds = function( objIdOrElement )
  {
    var objBoundary = new Object();
    var objElement = xgene360_cu.Element( objIdOrElement );
    
    objBoundary.left = 0;
    objBoundary.top = 0;
    objBoundary.width = objElement.offsetWidth;
    objBoundary.height = objElement.offsetHeight;
    
    var objContainerElement = ( xgene360_cu.IE ) ? objElement.document.body : objElement.ownerDocument.body;
    
    var objTraceElement = objElement;
    
    while ( objTraceElement != objContainerElement && objTraceElement != null )
    {
      objBoundary.left += objTraceElement.offsetLeft;
      objBoundary.top += objTraceElement.offsetTop;
      
      objTraceElement = objTraceElement.offsetParent;
    }
    
    return objBoundary;
  }
}

////////////////////////////////////////////////////////////
//
// sortable table related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.sortabletable = function()
{
  xgene360_cu.using( 'event' );
  
  xgene360_cu.sortabletable = new Object();
  xgene360_cu.sortabletable.sortDirection = new Array();
  xgene360_cu.sortabletable.sortingColumn = -1;
  
  xgene360_cu.sortabletable.init = function()
  {
    // assign all tables with sortable class to be sortable
    var objTables = document.getElementsByTagName( 'TABLE' );
        
    for ( var i = 0; i < objTables.length; ++i )
    {
      if ( objTables[i].className == 'listing' && xgene360_cu.stringLength( objTables[i].id ) != 0 )
      {
        xgene360_cu.sortabletable.makeSortable( objTables[i] );
      }
    }
  }
  
  xgene360_cu.event.addDOMListener( window, "onload", xgene360_cu.sortabletable.init );
  
  xgene360_cu.sortabletable.makeSortable = function( objTable )
  {
    if ( objTable.rows && objTable.rows.length > 0 )
    {
      var objFirstRow = objTable.rows[0];
    }
    
    if ( !objFirstRow )
    {
      return;
    }
    
    // the first row has to be header
    for ( var i = 0; i < objFirstRow.cells.length; ++i )
    {
      var objCell = objFirstRow.cells[i];
      
      if ( xgene360_cu.stringLength( objCell.id ) == 0 )
      {
        objCell.id = objTable.id + '_Column' + i;
      }
      
      var strText = xgene360_cu.getInnerText( objCell );
      
      // rewrite the header to be sortable
      if ( xgene360_cu.stringLength( strText ) != 0 )
      {
        objCell.innerHTML = '<a href="#" onclick="xgene360_cu.sortabletable.sortTable( this ); return false;">' + strText + '<span class="sortdirection">&nbsp;&nbsp;&nbsp;</span></a>';
      }
      
      xgene360_cu.sortabletable.sortDirection[objCell.id] = 'down';
    }
  }
  
  xgene360_cu.sortabletable.sortTable = function( objLink )
  {
    // there should only be one span here
    var objSortDirection = objLink.getElementsByTagName( 'SPAN' )[0];
    var objCell = objLink.parentNode;
    var iColumnIndex = objCell.cellIndex;
    
    var objTable = xgene360_cu.getParentNode( objCell, 'TABLE' );
    
    // what type of column is this?
    if ( objTable.rows.length <= 1 )
    {
      // nothing to sort
      return;
    }
    
    xgene360_cu.sortabletable.sortingColumn = iColumnIndex;
    
    var strItemText = xgene360_cu.getInnerText( objTable.rows[1].cells[iColumnIndex] );
    
    // default sort algorithm
    var objSortFunc = xgene360_cu.sortabletable.sortCaseInsensitive;
    
    var objFirstRow = new Array();
    var objNewRows = new Array();
    
    for ( var i = 0; i < objTable.rows[0].length; ++i )
    {
      objFirstRow[i] = objTable.rows[0][i];
    }
    
    for ( var i = 1; i < objTable.rows.length; ++i )
    {
      objNewRows[i - 1] = objTable.rows[i];
    }
    
    var strSortDirection = '&nbsp;&nbsp;&nbsp;';
    
    objNewRows.sort( objSortFunc );
    
    if ( xgene360_cu.sortabletable.sortDirection[objCell.id] == 'down' )
    {
      xgene360_cu.sortabletable.sortDirection[objCell.id] = 'up';
      strSortDirection = '&nbsp;&nbsp;&uarr;';
    }
    
    else
    {
      objNewRows.reverse();
      xgene360_cu.sortabletable.sortDirection[objCell.id] = 'down';
      strSortDirection = '&nbsp;&nbsp;&darr;';
    }
    
    for ( var i = 0; i < objNewRows.length; ++i )
    {
      if ( !objNewRows[i].className || 
            ( objNewRows[i].className && ( objNewRows[i].className != 'sortbottom' ) ) )
      {
        objTable.tBodies[0].appendChild( objNewRows[i] );
      }
    }
    
    for ( var i = 0; i < objNewRows.length; ++i )
    {
      if ( objNewRows[i].className && 
            ( objNewRows[i].className == 'sortbottom' ) )
      {
        objTable.tBodies[0].appendChild( objNewRows[i] );
      }
    }
    
    // delete any other arrows
    var objSortDirections = objTable.getElementsByTagName( 'span' );
    
    for ( var i = 0; i < objSortDirections.length; ++i )
    {
      if ( objSortDirections[i].className == 'sortdirection' )
      {
        if ( xgene360_cu.getParentNode( objSortDirections[i], 'TABLE' ) == xgene360_cu.getParentNode( objLink, "TABLE" ) )
        {
          objSortDirections[i].innerHTML = '&nbsp;&nbsp;&nbsp;';
        }
      }
    }
    
    objSortDirection.innerHTML = strSortDirection;
  }

  xgene360_cu.sortabletable.sortCaseInsensitive = function( objA, objB )
  {
    var strItem1 = xgene360_cu.getInnerText( objA.cells[xgene360_cu.sortabletable.sortingColumn] ).toLowerCase();
    var strItem2 = xgene360_cu.getInnerText( objB.cells[xgene360_cu.sortabletable.sortingColumn] ).toLowerCase();
    
    if ( strItem1 == strItem2 )
    {
      return 0;
    }
    
    if ( strItem1 < strItem2 )
    {
      return -1;
    }
    
    return 1;
  }

}

////////////////////////////////////////////////////////////
//
// form related stuff
//
////////////////////////////////////////////////////////////

xgene360_cu.component.form = function()
{
  xgene360_cu.using( 'stringExtension' );
  
  xgene360_cu.form = new Object();
 
  xgene360_cu.form.objForm = null;
  xgene360_cu.form.objValidates = null;
  
  xgene360_cu.form.init = function( objIdOrElement )
  {
    xgene360_cu.form.objForm = objIdOrElement;
    xgene360_cu.form.objValidates = new Array();
  }
  
  xgene360_cu.form.addRequiredTextBox = function( objIdOrElement, strMessage, iMaxLength )
  {
    var objItem = new Object();
    objItem.objElement = xgene360_cu.Element( objIdOrElement );
    objItem.strMessage = strMessage;
    objItem.iMaxLength = iMaxLength;
    objItem.objFunc = xgene360_cu.form.validateRequiredTextBox;
    
    if ( objItem.objElement != null )
    {
      xgene360_cu.form.objValidates.push( objItem );
    }
    
    return true;
  }
  
  xgene360_cu.form.validateRequiredTextBox = function()
  {
    var iLength = xgene360_cu.stringLength( this.objElement.value.trim() );
    
    if ( iLength == 0 || iLength > this.iMaxLength )
    {
      alert( this.strMessage );
      this.objElement.focus();
      
      return false;
    }
    
    return true;
  }
  
  xgene360_cu.form.addRegExTextBox = function( objIdOrElement, strMessage, strRegEx, bAllowEmpty )
  {
    var objItem = new Object();
    
    objItem.objElement = xgene360_cu.Element( objIdOrElement );
    objItem.strMessage = strMessage;
    objItem.strRegEx = strRegEx;
    objItem.bAllowEmpty = bAllowEmpty;
    objItem.objFunc = xgene360_cu.form.validateRegExTextBox;
    
    if ( objItem.objElement != null )
    {
      xgene360_cu.form.objValidates.push( objItem );
    }
  }
  
  xgene360_cu.form.validateRegExTextBox = function()
  {
    var str = this.objElement.value.trim();
    
    if ( this.bAllowEmpty && str.length == 0 )
    {
      return true;
    }
    
    var objRegEx = new RegExp( this.strRegEx );
    
    if ( !objRegEx.test( str ) )
    {
      alert( this.strMessage );
      this.objElement.focus();
      
      return false;
    }
    
    return true;
  }
  
  xgene360_cu.form.addCustomValidator = function( onvalidateHandler )
  {
    var objItem = new Object();
    objItem.objFunc = function() {}
    objItem.objFunc = onvalidateHandler;
    
    this.objValidates.push( objItem );
  }
  
  xgene360_cu.form.validate = function()
  {
    for ( var i = 0; i < xgene360_cu.form.objValidates.length; ++i )
    {
      if ( !xgene360_cu.form.objValidates[i].objFunc() )
      {
        return false;
      }
    }
    
    return true;
  }
}

////////////////////////////////////////////////////////////
//
// utility functions
//
////////////////////////////////////////////////////////////

xgene360_cu.preloadImage = function( src, onloadHandler )
{
  var objImg = new Image();
  
  if ( onloadHandler )
  {
    objImg.onload = onloadHandler;
    objImg.onerror = onloadHandler;
  }
  
  objImg.src = src;
  
  return objImg;
}

xgene360_cu.stringLength = function( str )
{
  if ( str == null )
  {
    return 0;
  }
  
  return str.length;
}
