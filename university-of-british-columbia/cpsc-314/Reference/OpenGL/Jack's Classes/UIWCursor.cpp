//////////////////////////////////////////////////////////////////////////
//
// File:		UIWCursor.cpp
// Date:		Apr 3, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#include "UIWCursor.h"
#include "UIManager.h"

#include "CommonInclude.h"

#include "TextureManager.h"
#include "TextureRender.h"

#include "Mouse.h"

#include "FontRender.h"
#include "FontManager.h"

//////////////////////////////////////////////////////////////////////////
// 

namespace
{
	const char textureName[] = "cursor.tga";

	TextureManager::TextureID textureID = TextureManager::InvalidID;
	GLuint displayID = INVALID_DISPLAYLIST_ID;

	const int cursorSize = 32;
}

//////////////////////////////////////////////////////////////////////////
// constructors/destructors

UIWCursor::UIWCursor( UIManager* pManager ) :
	UIWidget( pManager )
{
	// empty
}

UIWCursor::~UIWCursor()
{
	// empty
}

//////////////////////////////////////////////////////////////////////////
// interfaces

void UIWCursor::OnRender()
{
	if ( textureID == TextureManager::InvalidID )
	{
		textureID = TextureManager::Instance()->LoadTexture( textureName );
	}

	if ( displayID == INVALID_DISPLAYLIST_ID )
	{
		displayID = glGenLists( 1 );

		glNewList( displayID, GL_COMPILE );
		{
			TextureRender::TextureVertex textureVertex[ 6 ];

			textureVertex[ 0 ].Clear();
			textureVertex[ 0 ].vertex		= Math::Vector3f( cursorSize, -cursorSize, 0 );
			textureVertex[ 0 ].uv			= Math::Vector2f( 1.0, 0.0 );

			textureVertex[ 1 ].Clear();
			textureVertex[ 1 ].vertex		= Math::Vector3f( cursorSize, 0, 0 );
			textureVertex[ 1 ].uv			= Math::Vector2f( 1.0, 1.0 );

			textureVertex[ 2 ].Clear();
			textureVertex[ 2 ].vertex		= Math::Vector3f( 0, -cursorSize, 0 );
			textureVertex[ 2 ].uv			= Math::Vector2f( 0.0, 0.0 );

			textureVertex[ 3 ]				= textureVertex[ 1 ];
			textureVertex[ 4 ]				= textureVertex[ 2 ];

			textureVertex[ 5 ].Clear();
			textureVertex[ 5 ].vertex		= Math::Vector3f( 0, 0, 0 );
			textureVertex[ 5 ].uv			= Math::Vector2f( 0.0, 1.0 );

			glDisable( GL_LIGHTING );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable( GL_BLEND );
			TextureRender::Render( textureID, TextureRender::PT_TriangleList, textureVertex, 6 );
			glDisable( GL_BLEND );
			glEnable( GL_LIGHTING );
		}
		glEndList();
	}

	Math::Vector2f mousePos = Mouse::GetMousePos();

	glTranslatef( mousePos.x, m_pManager->GetViewPort().bottom - mousePos.y, 0.0 );
	glCallList( displayID );
}

