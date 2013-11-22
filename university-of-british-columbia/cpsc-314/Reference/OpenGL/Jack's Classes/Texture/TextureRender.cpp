//////////////////////////////////////////////////////////////////////////
//
// File:		TextureRender.cpp
// Date:		Mar 4, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#include "CommonInclude.h"

#include "TextureRender.h"

void TextureRender::Render( TextureManager::TextureID textureID, PrimitiveType primitiveType, const TextureVertex* pTextureVertex, unsigned long textureVertexCount )
{
	// validate the texture
	DebugAssert( TextureManager::Instance()->IsValidTexture( textureID ) );
	
	glEnable( GL_TEXTURE_2D );

	// load the texture
	glBindTexture( GL_TEXTURE_2D, textureID );

	GLenum			primitiveMode;
	unsigned long	vertexCountPerIteration = 0;

	switch ( primitiveType )
	{
	case PT_TriangleList:

		primitiveMode = GL_TRIANGLE_STRIP;
		vertexCountPerIteration = 3;
		break;

	default:

		// should not reach here
		DebugBreak();
		return;
	}

	// check the number of vertex
	DebugAssert( textureVertexCount % vertexCountPerIteration == 0 );

	glBegin( primitiveMode );
	{
		for ( unsigned long i = 0; i < textureVertexCount; i++ )
		{
			const TextureVertex& pCurrentVertex = pTextureVertex[ i ];

			glColor4f( pCurrentVertex.color.r, pCurrentVertex.color.g, pCurrentVertex.color.b, pCurrentVertex.color.a );
			glTexCoord2f( pCurrentVertex.uv.x, pCurrentVertex.uv.y );
			glVertex3f( pCurrentVertex.vertex.x, pCurrentVertex.vertex.y, pCurrentVertex.vertex.z );
		}
	}
	glEnd();

	glDisable( GL_TEXTURE_2D );
}

void TextureRender::RenderBillboardAABB( TextureManager::TextureID textureID, PrimitiveType primitiveType, const TextureVertex* pTextureVertex, unsigned long textureVertexCount, Math::Vector3f axis )
{
	glPushMatrix();
	{
		float matrix[ 16 ];
		glGetFloatv( GL_MODELVIEW_MATRIX, matrix );

		float theta = -180 * atan2f( matrix[ 8 ], matrix[ 10 ] ) / M_PI;

		axis.NormalizeSelf();

		float ct    = cosf( ConvertDegToRad( theta ) );
		float st    = sinf( ConvertDegToRad( theta ) );

		// clear the matrix
		matrix[ 0  ] = 1; matrix[ 1  ] = 0; matrix[ 2  ] = 0; matrix[ 3  ] = 0;
		matrix[ 4  ] = 0; matrix[ 5  ] = 1; matrix[ 6  ] = 0; matrix[ 7  ] = 0;
		matrix[ 8  ] = 0; matrix[ 9  ] = 0; matrix[ 10 ] = 1; matrix[ 11 ] = 0;
		matrix[ 12 ] = 0; matrix[ 13 ] = 0; matrix[ 14 ] = 0; matrix[ 15 ] = 1;

		matrix[ 0  ] = axis.x * axis.x + ct * ( 1 - axis.x * axis.x ) + st *  0;
		matrix[ 4  ] = axis.x * axis.y + ct * ( 0 - axis.x * axis.y ) + st * -axis.z;
		matrix[ 8  ] = axis.x * axis.z + ct * ( 0 - axis.x * axis.z ) + st *  axis.y;

		matrix[ 1  ] = axis.y * axis.x + ct * ( 0 - axis.y * axis.x ) + st *  axis.z;
		matrix[ 5  ] = axis.y * axis.y + ct * ( 1 - axis.y * axis.y ) + st *  0;
		matrix[ 9  ] = axis.y * axis.z + ct * ( 0 - axis.y * axis.z ) + st * -axis.x;

		matrix[ 2  ] = axis.z * axis.x + ct * ( 0 - axis.z * axis.x ) + st * -axis.y;
		matrix[ 6  ] = axis.z * axis.y + ct * ( 0 - axis.z * axis.y ) + st *  axis.x;
		matrix[ 10 ] = axis.z * axis.z + ct * ( 1 - axis.z * axis.z ) + st *  0;

		glMultMatrixf( matrix );

		glDisable( GL_CULL_FACE );
		Render( textureID, primitiveType, pTextureVertex, textureVertexCount );
		glEnable( GL_CULL_FACE );
	}
	glPopMatrix();
}
