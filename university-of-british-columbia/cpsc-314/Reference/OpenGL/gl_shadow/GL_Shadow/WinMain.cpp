#include "glwindow.h"
#include <math.h>
#include <GL/glu.h>

CGLWindow window;

#define PI 3.1415926535
#define SIDES_NUM	100

#define LX light_position[0]
#define LY light_position[1]
#define LZ light_position[2]

GLfloat light_position[] = { -1.0f, 3.0f, 0.0f, 1.0f };
GLfloat shadow_matrix[] = {
	LY,		0.0,	0.0,	0.0,
	-LX,	0.0,	-LZ,	-1.0,
	0.0,	0.0,	LY,		0.0,
	0.0,	0.0,	0.0,	LY,
};

void Initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.3f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-7);
	glRotatef(30, 1, 0, 0);

	GLfloat light_diffuse[]  = { 0.7f, 1.0f, 0.7f, 1.0f };

	GLfloat material_diffuse[] = { 0.0f, 0.5f, 0.0f, 1.0f };
	GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat material_shininess[] = { 10.0f };

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glColor4f(1,1,1,1);

	glPolygonOffset(-1, 0);
}

void DrawCylinder(float alpha, bool shadow)
{
	glPushMatrix();

	
	if(shadow){
		glMultMatrixf(shadow_matrix);
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0,0,0,0.7);
	}

	glTranslatef(0,1.5,0);
	glRotatef(alpha,1.0f,0.5f,0.3f);

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
	glVertex3f(0.0f,0.0f, 0.5f);
	for(i=0;i<SIDES_NUM+1;i++){
		float x = 0.5f*sinf(-i*2*PI/SIDES_NUM);
		float y = 0.5f*cosf(-i*2*PI/SIDES_NUM);
		float d = sqrtf(x*x+y*y);
		glVertex3f(x,y, 0.5f);
	}
	glEnd();

	if(shadow){
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glDepthMask(GL_TRUE);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	glPopMatrix();
}

void DrawLight()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	GLUquadricObj *quadric = gluNewQuadric();
	gluSphere(quadric, 0.1, SIDES_NUM, SIDES_NUM);
	gluDeleteQuadric(quadric);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void DrawGround()
{
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex3f(-5,0,-5);
	glVertex3f(-5,0,+5);
	glVertex3f(+5,0,+5);
	glVertex3f(+5,0,-5);
	glEnd();
}

void Render()
{
	float alpha = GetTickCount()/10.0f;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3f(1,1,1);
	DrawLight();
	DrawGround();
	DrawCylinder(alpha, true);
	DrawCylinder(alpha, false);

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
