//////////////////////////////////////////////////////////////////////////
//
// File:		TextureLoader.h
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <cstdio>

// forward declaration
class Texture;

class TextureLoader
{

// interfaces
public:

	static bool LoadTGA( Texture* pTexture, const char* pFileName );

// types
private:

	struct TGAHeader
	{
		GLubyte	header[ 12 ];
	};

	struct TGABody
	{
		GLubyte		header[ 6 ];
		GLuint		bytesPerPixel;
		GLuint		bitsPerPixel;
		GLuint		imageSize;
		GLuint		height;
		GLuint		width;
		GLubyte*	pData;
	};

// implementations
private:

	static bool LoadUncompressedTGA( Texture* pTexture, const char* pFileName, FILE* pFile );
};

#endif /* TEXTURELOADER_H_ */
