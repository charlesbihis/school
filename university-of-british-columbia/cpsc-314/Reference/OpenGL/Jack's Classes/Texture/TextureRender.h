//////////////////////////////////////////////////////////////////////////
//
// File:		TextureRender.h
// Date:		Mar 4, 2005
// 
// Author:		Jack Liu
// Student ID:	74292012
//
//////////////////////////////////////////////////////////////////////////

#ifndef TEXTURERENDER_H_
#define TEXTURERENDER_H_

#include "TextureManager.h"

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace TextureRender
{
	enum PrimitiveType
	{
		PT_TriangleList,
	};

	struct TextureVertex
	{
		Math::Vector3f vertex;
		Math::Vector4f color;
		Math::Vector2f uv;

		void Clear()
		{
			vertex.Set( 0.0, 0.0, 0.0 );
			color.Set( 1.0, 1.0, 1.0, 1.0 );
			uv.Set( 0.0, 0.0 );
		}
	};

	void Render					( TextureManager::TextureID textureID, PrimitiveType primitiveType, const TextureVertex* pTextureVertex, unsigned long textureVertexCount );

	void RenderBillboardAABB	( TextureManager::TextureID textureID, PrimitiveType primitiveType, const TextureVertex* pTextureVertex, unsigned long textureVertexCount, Math::Vector3f axis );
}

#endif /* TEXTURERENDER_H_ */
