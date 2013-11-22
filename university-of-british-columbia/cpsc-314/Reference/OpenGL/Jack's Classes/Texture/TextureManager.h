//////////////////////////////////////////////////////////////////////////
//
// File:		TextureManager.h
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "CommonInclude.h"

// forward declaration
class Texture;

class TextureManager
{

// types
public:

	typedef GLuint TextureID;

	static const TextureID InvalidID;

// constructors/destructors
private:

	TextureManager	();
	~TextureManager	();

// interfaces
public:

	static void				Initialize		();
	static void				Uninitialize	();
	static TextureManager*	Instance		();

	TextureID				LoadTexture		( const char* pFileName );
	void					FreeTexture		( TextureID textureID );

	const Texture*			GetTexture		( TextureID textureID );

	bool					IsValidTexture	( TextureID textureID );

	void					DestroyAll		();

// implementations
private:
	
	typedef std::vector< Texture* > TextureCont;

	TextureCont::const_iterator	FindTexture	( TextureID textureID );

// fields
private:

	TextureCont	m_textures;
};

#endif /* TEXTUREMANAGER_H_ */
