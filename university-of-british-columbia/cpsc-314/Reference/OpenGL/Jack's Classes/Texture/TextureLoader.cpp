//////////////////////////////////////////////////////////////////////////
//
// File:		TextureLoader.h
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#include "CommonInclude.h"

#include "TextureLoader.h"

#include "Texture.h"

//////////////////////////////////////////////////////////////////////////
//

namespace
{
	const char TGAUncompressedHeader[ 12 ] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	const char TGACompressedHeader[ 12 ] = {  0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

//////////////////////////////////////////////////////////////////////////
//

bool TextureLoader::LoadTGA( Texture* pTexture, const char* pFileName )
{
	FILE* pFile = fopen( pFileName, "rb" );

	if ( !pFile )
	{
		DebugPrintf( "Could not read the texture file '%s'", pFileName );
		DebugBreak();

		return false;
	}

	// Header
	char header[ 12 ];

	if ( fread( header, sizeof( header ), 1, pFile ) == 0 )
	{
		fclose( pFile );

		DebugPrintf( "Cannot read the file header for file '%s'", pFileName );
		DebugBreak();

		return false;
	}

	bool result = false;

	if ( memcmp( TGAUncompressedHeader, header, sizeof( header ) ) == 0 )
	{
		result = LoadUncompressedTGA( pTexture, pFileName, pFile );
	}
	
	else if ( memcmp( TGACompressedHeader, header, sizeof( header ) ) == 0 )
	{
		DebugPrintf( "Compressed TGA file is not supported for file '%s'", pFileName );
		DebugBreak();
	}
	
	else
	{
		DebugPrintf( "Invalid TGA file type" );
		DebugBreak();
	}

	fclose( pFile );

	return result;
}

bool TextureLoader::LoadUncompressedTGA( Texture* pTexture, const char* pFileName,  FILE* pFile )
{
	DebugAssert( pTexture );
	DebugAssert( pFile );

	TGABody tga;

	if ( fread( tga.header, sizeof( tga.header ), 1, pFile ) == 0 )
	{
		DebugPrintf( "Cannot read the info header for file '%s'", pFileName );
		DebugBreak();

		return false;
	}

	tga.width			= tga.header[ 1 ] * 256 + tga.header[ 0 ];
	tga.height			= tga.header[ 3 ] * 256 + tga.header[ 2 ];
	tga.bitsPerPixel	= tga.header[ 4 ];

	pTexture->m_format.width	= tga.width;
	pTexture->m_format.height	= tga.height;
	pTexture->m_format.depth	= tga.bitsPerPixel;
	
	if ( ( tga.width <= 0 || tga.height <= 0 ) || ( tga.bitsPerPixel != 24 && tga.bitsPerPixel != 32 ) )
	{
		DebugPrintf( "Invalid texture format for file '%s'", pFileName );
		DebugBreak();

		return false;
	}
	
	if ( tga.bitsPerPixel == 24 )
	{
		pTexture->m_format.texelType = Texture::TT_RGB;
	}

	else
	{
		pTexture->m_format.texelType = Texture::TT_RGBA;
	}

	tga.bytesPerPixel	= tga.bitsPerPixel / 8;
	tga.imageSize		= tga.width * tga.height * tga.bytesPerPixel;

	tga.pData			= new GLubyte[ tga.imageSize ];

	if ( tga.pData == NULL )
	{
		DebugPrintf( "Cannot allocate memory for the texture" );
		DebugBreak();

		return false;
	}

	if ( fread( tga.pData, 1, tga.imageSize, pFile ) != tga.imageSize )
	{
		DebugPrintf( "Cannot read the texture data for file '%s'", pFileName );
		DebugBreak();

		if ( tga.pData != NULL )
		{
			DELETEARRAYZERO( tga.pData );
		}

		return false;
	}

	// swap the bytes
	for ( unsigned int i = 0; i < tga.imageSize; i += tga.bytesPerPixel )
	{
		tga.pData[ i ] ^= tga.pData[ i + 2 ] ^= tga.pData[ i ] ^= tga.pData[ i + 2 ];
	}

	// register the texture
	glGenTextures( 1, &pTexture->m_textureID );
	glBindTexture( GL_TEXTURE_2D, pTexture->m_textureID );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, pTexture->m_format.depth / 8, pTexture->m_format.width, pTexture->m_format.height, 
					0, pTexture->m_format.texelType, GL_UNSIGNED_BYTE, tga.pData );

	gluBuild2DMipmaps( GL_TEXTURE_2D, pTexture->m_format.depth / 8, pTexture->m_format.width, pTexture->m_format.height,
						pTexture->m_format.texelType, GL_UNSIGNED_BYTE, tga.pData );

	// free the memory
	DELETEARRAYZERO( tga.pData );

	return true;
}
