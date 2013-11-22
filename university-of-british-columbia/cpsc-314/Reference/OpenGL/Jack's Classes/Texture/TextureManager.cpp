//////////////////////////////////////////////////////////////////////////
//
// File:		TextureManager.cpp
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#include "TextureManager.h"
#include "TextureLoader.h"

#include "Texture.h"

//////////////////////////////////////////////////////////////////////////
//

namespace
{
	TextureManager* pInstance = NULL;
}

//////////////////////////////////////////////////////////////////////////
//

const TextureManager::TextureID TextureManager::InvalidID = 0;

//////////////////////////////////////////////////////////////////////////
// constructors/destructors

TextureManager::TextureManager()
{
	// empty
}

TextureManager::~TextureManager()
{
	DestroyAll();
}

//////////////////////////////////////////////////////////////////////////
// interfaces

void TextureManager::Initialize()
{
	DebugAssert( pInstance == NULL );

	pInstance = new TextureManager();

	DebugPrintf( "TextureManager Initialized" );
}

void TextureManager::Uninitialize()
{
	DebugAssert( pInstance );

	DELETEZERO( pInstance );

	DebugPrintf( "TextureManager Uninitialized" );
}

TextureManager* TextureManager::Instance()
{
	return pInstance;
}

TextureManager::TextureID TextureManager::LoadTexture( const char* pFileName )
{
	// check if the texture already exists
	TextureCont::const_iterator i = m_textures.begin();
	TextureCont::const_iterator e = m_textures.end();

	for ( ; i != e; ++i )
	{
		if ( strcmp( pFileName, ( *i )->m_fileName ) == 0 )
		{
			DebugPrintf( "The texture file '%s' has already been loaded", pFileName );
			return ( *i )->GetTextureID();
		}
	}

	Texture* pTexture = new Texture( pFileName );

	if ( !TextureLoader::LoadTGA( pTexture, pFileName ) )
	{
		DELETEZERO( pTexture );
		return InvalidID;
	}

	m_textures.push_back( pTexture );
	return pTexture->GetTextureID();
}

void TextureManager::FreeTexture( TextureID textureID )
{
	TextureCont::iterator i = m_textures.begin();
	TextureCont::iterator e = m_textures.end();

	for ( ; i != e; ++i )
	{
		if ( textureID == ( *i )->GetTextureID() )
		{
			glDeleteTextures( 1, &( *i )->m_textureID );
			m_textures.erase( i );
		}
	}

	if ( i == e )
	{
		DebugPrintf( "The specified textureID '%d' does not exist", textureID );
	}
}

const Texture* TextureManager::GetTexture( TextureID textureID )
{
	TextureCont::const_iterator item = FindTexture( textureID );

	if ( item == m_textures.end() )
	{
		DebugPrintf( "The specified textureID '%d' does not exist", textureID );
		return NULL;
	}

	else
	{
		return *item;
	}
}

bool TextureManager::IsValidTexture( TextureID textureID )
{
	return FindTexture( textureID ) != m_textures.end();
}

void TextureManager::DestroyAll()
{
	while ( !m_textures.empty() )
	{
		glDeleteTextures( 1, &( *m_textures.begin() )->m_textureID );
		m_textures.erase( m_textures.begin() );
	}
}

TextureManager::TextureCont::const_iterator TextureManager::FindTexture( TextureID textureID )
{
	TextureCont::const_iterator i = m_textures.begin();
	TextureCont::const_iterator e = m_textures.end();

	for ( ; i != e; ++i )
	{
		if ( textureID == ( *i )->GetTextureID() )
		{
			return i;
		}
	}

	return m_textures.end();
}
