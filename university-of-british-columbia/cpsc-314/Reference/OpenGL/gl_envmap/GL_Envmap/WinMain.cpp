#include "glwindow.h"
#include <math.h>
#include <GL/glu.h>
#include <GL/glaux.h>

CGLWindow window;
GLuint tex;

#define PI 3.1415926535
#define SIDES_NUM	100

GLuint LoadTexture(char *filename)
{
	GLuint texID;

	AUX_RGBImageRec *image = auxDIBImageLoad(filename);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);

	return texID;
}

void Initialize()
{
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	tex = LoadTexture("lobbyxneg.bmp");	
}

void Render()
{
	float alpha = GetTickCount()/10.0f;
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-2,-2,-2);
	glTexCoord2f(1,0); glVertex3f( 2,-2,-2);
	glTexCoord2f(1,1); glVertex3f( 2, 2,-2);
	glTexCoord2f(0,1); glVertex3f(-2, 2,-2);
	glEnd();

	glRotatef(alpha,1.0f,0.5f,0.3f);

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<SIDES_NUM+1;i++){
		float x = 0.5f*sinf(i*2*PI/SIDES_NUM);
		float y = 0.5f*cosf(i*2*PI/SIDES_NUM);
		float d = sqrtf(x*x+y*y);
		glNormal3f(x/d,y/d,0);
		glVertex3f(x,y,-0.5f);
		glNormal3f(x/d,y/d,0);
		glVertex3f(x,y, 0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f,0.0f,-1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f,0.0f,-0.5f);
	for(i=0;i<SIDES_NUM+1;i++){
		float x = 0.5f*sinf(i*2*PI/SIDES_NUM);
		float y = 0.5f*cosf(i*2*PI/SIDES_NUM);
		float d = sqrtf(x*x+y*y);
		glVertex3f(x,y,-0.5f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f,0.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f,0.0f, 0.5f);
	for(i=0;i<SIDES_NUM+1;i++){
		float x = 0.5f*sinf(-i*2*PI/SIDES_NUM);
		float y = 0.5f*cosf(-i*2*PI/SIDES_NUM);
		float d = sqrtf(x*x+y*y);
		glVertex3f(x,y, 0.5f);
	}
	glEnd();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			window.Resize(LOWORD(lParam), HIWORD(lParam));
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	MSG msg;
	bool done = false;
	
	window.Initialize(800, 600, 32, false);
	
	Initialize();
	
	while(!done){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message==WM_QUIT){
				done = true;
			}
			else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else{
			Render();
			window.Swap();
		}
	}
	
	window.Terminate();
	
	return msg.wParam;
}
