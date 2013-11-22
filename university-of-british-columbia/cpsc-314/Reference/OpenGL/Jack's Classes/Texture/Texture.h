//////////////////////////////////////////////////////////////////////////
//
// File:		Texture.h
// Date:		Mar 25, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture
{

// friends
public:

	friend class TextureLoader;
	friend class TextureManager;

// types
public:

	enum TexelType
	{
		TT_RGB = GL_RGB,
		TT_RGBA = GL_RGBA,

		TT_Invalid,
	};

	struct Format
	{
		GLuint		width;
		GLuint		height;
		GLuint		depth;

		TexelType	texelType;		
	};

// constructors/destructors
public:

	Texture				( const char* pFileName );
	virtual ~Texture	();

// interfaces
public:

	GLuint			GetTextureID() const;

	const Format&	GetFormat	() const;

// fields
protected:

	char			m_fileName[ MAX_BUFFER_SIZE ];

	GLuint			m_textureID;

	Format			m_format;
};

inline GLuint Texture::GetTextureID() const
{
	return m_textureID;
}

inline const Texture::Format& Texture::GetFormat() const
{
	return m_format;
}

#endif /* TEXTURE_H_ */
