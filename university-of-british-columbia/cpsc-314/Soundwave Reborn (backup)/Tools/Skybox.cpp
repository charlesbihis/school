/************************************************************
*	APRON TUTORIALS PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
*	Version					: English (UK)					*
************************************************************/
#include <stdio.h>
#include <gl\glut.h>
#include "Skybox.h"




/////////////////////////////////////////////////////////////////////////////////////////////////
//										JPEG TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
void JPEG_Skybox(UINT textureArray[], LPSTR strFileName, int ID)
{
	if(!strFileName)	return;
	
	tImageJPG *pBitMap = Load_JPEG(strFileName);
	
	if(pBitMap == NULL)	exit(0);
	
	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitMap->sizeX, pBitMap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitMap->data);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		// Linear Filtered
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pBitMap->sizeX, pBitMap->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pBitMap->data);

	
	if (pBitMap)									
	{
		if (pBitMap->data)					
		{
			free(pBitMap->data);			
		}
		free(pBitMap);
	}
}
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////











void JPEG_Texture(UINT textureArray[], LPSTR strFileName, int ID)
{
	if(!strFileName)	return;
	
	tImageJPG *pBitMap = Load_JPEG(strFileName);
	
	if(pBitMap == NULL)	exit(0);
	
	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitMap->sizeX, pBitMap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitMap->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	
	
	if (pBitMap)									
	{
		if (pBitMap->data)					
		{
			free(pBitMap->data);			
		}
		free(pBitMap);
	}
}





tImageJPG *Load_JPEG(const char *strfilename)
{
	struct jpeg_decompress_struct cInfo;
	tImageJPG *pImgData = NULL;
	FILE *pFile;
	
	if((pFile = fopen(strfilename, "rb")) == NULL) 
	{
		//MessageBox(hWnd, "Error loading jpg file.", "ERROR", MB_OK);
		return NULL;
	}
	
	jpeg_error_mgr jerr;

	cInfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cInfo);

	jpeg_stdio_src(&cInfo, pFile);
	
	pImgData = (tImageJPG*)malloc(sizeof(tImageJPG));

	Decompress_JPEG(&cInfo, pImgData);

	jpeg_destroy_decompress(&cInfo);
	
	fclose(pFile);
	
	return pImgData;
}


void Decompress_JPEG(jpeg_decompress_struct* cInfo, tImageJPG *pImgData)
{
	jpeg_read_header(cInfo, TRUE);
	
	jpeg_start_decompress(cInfo);
	
	pImgData->rowSpan = cInfo->image_width * cInfo->num_components;
	pImgData->sizeX   = cInfo->image_width;
	pImgData->sizeY   = cInfo->image_height;
	
	pImgData->data = new unsigned char[pImgData->rowSpan * pImgData->sizeY];
	
	unsigned char** rowPtr = new unsigned char*[pImgData->sizeY];
	for (int i = 0; i < pImgData->sizeY; i++)
		rowPtr[i] = &(pImgData->data[i*pImgData->rowSpan]);
	
	int rowsRead = cInfo->output_height-1;
	while (cInfo->output_scanline < cInfo->output_height) 
	{
		rowsRead -= jpeg_read_scanlines(cInfo, &rowPtr[rowsRead], cInfo->output_height - rowsRead);
	}
	delete [] rowPtr;
	
	jpeg_finish_decompress(cInfo);
}




//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com
