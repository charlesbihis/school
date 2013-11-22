//////////////////////////////////////////////////////////////////////////
//
// File:		Texture.cpp
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#include "CommonInclude.h"

#include "Texture.h"

//////////////////////////////////////////////////////////////////////////
//

Texture::Texture( const char* pFileName ) :
	m_textureID( 0 )
{
	snprintf( m_fileName, sizeof( m_fileName ), "%s", pFileName );

	m_format.width	= 0;
	m_format.height	= 0;
	m_format.depth	= 0;

	m_format.texelType = TT_Invalid;
}

Texture::~Texture()
{
	// empty
}
