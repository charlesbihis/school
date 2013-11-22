#ifndef JPEG_H
#define JPEG_H


#include "jpegdefs.h"
#include "jpeglib.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
#define GL_CLAMP_TO_EDGE	0x812F		// Define this for glTexParameteri
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////




tImageJPG *Load_JPEG(const char *strfilename);

void Decompress_JPEG(jpeg_decompress_struct* cInfo, tImageJPG *pImgData);

void JPEG_Texture(UINT textureArray[], LPSTR strFileName, int ID);

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
void JPEG_Skybox(UINT textureArray[], LPSTR strFileName, int ID);
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////


#endif



// www.morrowland.com
// apron@morrowland.com