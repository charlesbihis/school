#ifndef _MAIN_H
#define _MAIN_H


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
#pragma comment(lib, "jpeg.lib")
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

#include <windows.h>
#include <windowsx.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
		// Header File For The Glaux Library
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
//#include "jpeg.h"


#define CAMERASPEED	0.03f				// The Camera Speed

#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////











//////////////////////////////////////
//	Global Variables
//////////////////////////////////////
extern	HDC			hDC;				// Device context
extern	HGLRC		hRC;				// Permanent rendering context
extern	HWND		hWnd;				// Holds our window handle
extern	HINSTANCE	hInstance;			// Holds the instance of the application



//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

//////////////////////////////////////
//	MAIN FUNCTIONS
//////////////////////////////////////
void Keyboard_Input();
void Draw_Grid();
void Draw_Skybox(float x, float y, float z, float width, float height, float length);

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////




#endif

//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com