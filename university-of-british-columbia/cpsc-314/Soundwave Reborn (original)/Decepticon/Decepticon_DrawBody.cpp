#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"
#include "../Draw/DrawFunctions.h"


void Decepticon :: DrawBody()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  GLfloat mat_ambient[] = {0.0, 0.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {0.0, 0.0, 0.8, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// bottom left edge
    CalculateNormal(10, 10, -2.5, -2.5, 0, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-35, 0, 20);
	glVertex3f(-37.5, 0, 17.5);
	glVertex3f(-45, 10, 17.5);
	glVertex3f(-42.5, 10, 20);
  glEnd();

  glBegin(display_mode);				// bottom right edge
    CalculateNormal(2.5, 0, -2.5, 5, 10, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(35, 0, 20);
	glVertex3f(37.5, 0, 17.5);
	glVertex3f(45, 10, 17.5);
	glVertex3f(42.5, 10, 20);
  glEnd(); 

  glBegin(display_mode);				// left edge
    CalculateNormal(-2.5, 40, -2.5, -2.5, 0, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-42.5, 10, 20);
	glVertex3f(-45, 10, 17.5);
	glVertex3f(-45, 50, 17.5);
	glVertex3f(-42.5, 47.5, 20);
  glEnd();

  glBegin(display_mode);				// right edge
    CalculateNormal(2.5, 0, -2.5, 2.5, 40, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(42.5, 10, 20);
	glVertex3f(45, 10, 17.5);
	glVertex3f(45, 50, 17.5);
	glVertex3f(42.5, 47.5, 20);
  glEnd();

  glBegin(display_mode);				// top left edge
    CalculateNormal(30, 2.5, -2.5, 27.5, 2.5, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-42.5, 47.5, 20);
	glVertex3f(-45, 50, 17.5);
	glVertex3f(-15, 50, 17.5);
	glVertex3f(-15, 47.5, 20);
  glEnd();

  glBegin(display_mode);				// top right edge
    CalculateNormal(2.5, 2.5, -2.5, -27.5, 2.5, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(42.5, 47.5, 20);
	glVertex3f(45, 50, 17.5);
	glVertex3f(15, 50, 17.5);
	glVertex3f(15, 47.5, 20);
  glEnd();

  glBegin(display_mode);				// left inner wall
    glNormal3f(0, 0, 1);
    glVertex3f(-15, 50, 15);
    glVertex3f(-15, 50, 17.5);
	glVertex3f(-15, 47.5, 20);
	glVertex3f(-15, 45, 20);
	glVertex3f(-15, 45, 17.5);
  glEnd();

  glBegin(display_mode);				// right inner wall
    glNormal3f(0, 0, 1);
    glVertex3f(15, 50, 15);
    glVertex3f(15, 50, 17.5);
	glVertex3f(15, 47.5, 20);
	glVertex3f(15, 45, 20);
	glVertex3f(15, 45, 17.5);
  glEnd();

  glBegin(display_mode);				// middle flat wall
    glNormal3f(0, 1, 0);
    glVertex3f(-15, 45, 17.5);
	glVertex3f(-15, 45, 20);
	glVertex3f(15, 45, 20);
	glVertex3f(15, 45, 17.5);
  glEnd();

  glBegin(display_mode);			// middle slanted edge
    CalculateNormal(30, 5, -2.5, 0, 5, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-15, 45, 17.5);
	glVertex3f(-15, 50, 15);
	glVertex3f(15, 50, 15);
	glVertex3f(15, 45, 17.5);
  glEnd();

  glBegin(display_mode);				// bottom edge
    CalculateNormal(-2.5, 0, -2.5, 72.5, 0, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-35, 0, 20);
	glVertex3f(-37.5, 0, 17.5);
	glVertex3f(37.5, 0, 17.5);
	glVertex3f(35, 0, 20);
  glEnd();

  glBegin(display_mode);			// back face
    glNormal3f(0, 0, -1);
    glVertex3f(-37.5, 0, -17.5);
	glVertex3f(-45, 10, -17.5);
	glVertex3f(-45, 50, -17.5);
	glVertex3f(45, 50, -17.5);
	glVertex3f(45, 10, -17.5);
	glVertex3f(37.5, 0, -17.5);
  glEnd();

  glBegin(display_mode);				// front bevelled left face
    glNormal3f(0, 0, 1);
    glVertex3f(-35, 0, 20);
	glVertex3f(-42.5, 10, 20);
	glVertex3f(-42.5, 47.5, 20);
    glVertex3f(-30, 40, 20);
	glVertex3f(-30, 15, 20);
	glVertex3f(-27.5, 12.5, 20);
  glEnd();

  glBegin(display_mode);				// front bevelled left edge
    glNormal3f(1, 0, 0);
	glVertex3f(-30, 40, 20);
	glVertex3f(-30, 15, 20);
	glVertex3f(-30, 15, 17.5);
	glVertex3f(-30, 40, 17.5);
  glEnd();

  glBegin(display_mode);				// front bevelled right face
    glNormal3f(0, 0, 1);
    glVertex3f(35, 0, 20);
	glVertex3f(42.5, 10, 20);
	glVertex3f(42.5, 47.5, 20);
    glVertex3f(30, 40, 20);
	glVertex3f(30, 15, 20);
	glVertex3f(27.5, 12.5, 20);
  glEnd();

  glBegin(display_mode);				// front bevelled right edge
    glNormal3f(-1, 0, 0);
    glVertex3f(30, 40, 20);
    glVertex3f(30, 15, 20);
    glVertex3f(30, 15, 17.5);
    glVertex3f(30, 40, 17.5);
  glEnd();

  glBegin(display_mode);				// front bevelled bottom face
    glNormal3f(0, 0, 1);
	glVertex3f(-35, 0, 20);
	glVertex3f(-27.5, 12.5, 20);
	glVertex3f(27.5, 12.5, 20);
	glVertex3f(35, 0, 20);
  glEnd();

  glBegin(display_mode);				// front bevelled bottom edge
    glNormal3f(0, 1, 0);
	glVertex3f(-27.5, 12.5, 20);
	glVertex3f(27.5, 12.5, 20);
	glVertex3f(27.5, 12.5, 17.5);
	glVertex3f(-27.5, 12.5, 17.5);
  glEnd();

  glBegin(display_mode);				// front bevelled bottom left edge
    CalculateNormal(-2.5, 2.5, -2.5, -2.5, 2.5, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-27.5, 12.5, 20);
	glVertex3f(-30, 15, 20);
	glVertex3f(-30, 15, 17.5);
	glVertex3f(-27.5, 12.5, 17.5);
  glEnd();

  glBegin(display_mode);				// front bevelled bottom right edge
    CalculateNormal(2.5, 2.5, 0, 2.5, 2.5, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(27.5, 12.5, 20);
    glVertex3f(30, 15, 20);
    glVertex3f(30, 15, 17.5);
    glVertex3f(27.5, 12.5, 17.5);
  glEnd();

  glBegin(display_mode);					// front bevelled top left face
    glNormal3f(0, 0, 1);
	glVertex3f(-30, 40, 20);
	glVertex3f(-42.5, 47.5, 20);
	glVertex3f(-15, 47.5, 20);
	glVertex3f(-15, 40, 20);
  glEnd();

  glBegin(display_mode);					// front bevelled top right face
    glNormal3f(0, 0, 1);
    glVertex3f(30, 40, 20);
    glVertex3f(42.5, 47.5, 20);
    glVertex3f(15, 47.5, 20);
    glVertex3f(15, 40, 20);
  glEnd();

  glBegin(display_mode);					// front bevelled top middle face
    glNormal3f(0, 0, 1);
	glVertex3f(-15, 45, 20);
	glVertex3f(-15, 40, 20);
	glVertex3f(15, 40, 20);
	glVertex3f(15, 45, 20);
  glEnd();

  glBegin(display_mode);					// front bevelled top edge
    glNormal3f(0, 1, 0);
    glVertex3f(-30, 40, 20);
    glVertex3f(30, 40, 20);
    glVertex3f(30, 40, 17.5);
    glVertex3f(-30, 40, 17.5);
  glEnd();

  glBegin(display_mode);				// bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(-37.5, 0, 17.5);
	glVertex3f(-37.5, 0, -17.5);
	glVertex3f(37.5, 0, -17.5);
	glVertex3f(37.5, 0, 17.5);
  glEnd();

  glBegin(display_mode);				// bottom left face
    CalculateNormal(-7.5, 10, 35, -7.5, 10, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-37.5, 0, 17.5);
	glVertex3f(-45, 10, 17.5);
	glVertex3f(-45, 10, -17.5);
	glVertex3f(-37.5, 0, -17.5);
  glEnd();
  
  glBegin(display_mode);				// bottom right face
    CalculateNormal(7.5, 10, 0, 7.5, 10, 35);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(37.5, 0, 17.5);
	glVertex3f(45, 10, 17.5);
	glVertex3f(45, 10, -17.5);
	glVertex3f(37.5, 0, -17.5);
  glEnd();

  glBegin(display_mode);				// left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-45, 10, 17.5);
	glVertex3f(-45, 50, 17.5);
	glVertex3f(-45, 50, -17.5);
	glVertex3f(-45, 10, -17.5);
  glEnd();

  glBegin(display_mode);				// right face
    glNormal3f(1, 0, 0);
    glVertex3f(45, 10, 17.5);
	glVertex3f(45, 50, 17.5);
	glVertex3f(45, 50, -17.5);
	glVertex3f(45, 10, -17.5);
  glEnd();

  glBegin(display_mode);				// top face
    glNormal3f(0, 1, 0);
    glVertex3f(-45, 50, 17.5);
	glVertex3f(-15, 50, 17.5);
	glVertex3f(-15, 50, 15);
	glVertex3f(15, 50, 15);
	glVertex3f(15, 50, 17.5);
	glVertex3f(45, 50, 17.5);
	glVertex3f(45, 50, -17.5);
	glVertex3f(-45, 50, -17.5);
  glEnd();

  mat_ambient[0] = 1.0;
  mat_ambient[1] = 1.0;
  mat_ambient[2] = 0.0;
  mat_diffuse[0] = 0.8;
  mat_diffuse[1] = 0.8;
  mat_diffuse[2] = 0.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// left upper stripe face
    glNormal3f(0, 0, 1);
    glVertex3f(-42.5, 35, 21);
	glVertex3f(-42.5, 31, 21);
	glVertex3f(-32.5, 31, 21);
	glVertex3f(-32.5, 35, 21);
  glEnd();

  glBegin(display_mode);				// right upper stripe face
    glNormal3f(0, 0, 1);
    glVertex3f(42.5, 35, 21);
	glVertex3f(42.5, 31, 21);
	glVertex3f(32.5, 31, 21);
	glVertex3f(32.5, 35, 21);
  glEnd();

  glBegin(display_mode);				// left lower stripe face
    glNormal3f(0, 0, 1);
    glVertex3f(-42.5, 29, 21);
	glVertex3f(-42.5, 25, 21);
	glVertex3f(-32.5, 25, 21);
	glVertex3f(-32.5, 29, 21);
  glEnd();

  glBegin(display_mode);				// right lower stripe face
    glNormal3f(0, 0, 1);
    glVertex3f(42.5, 29, 21);
	glVertex3f(42.5, 25, 21);
	glVertex3f(32.5, 25, 21);
	glVertex3f(32.5, 29, 21);
  glEnd();

  glBegin(display_mode);					// left upper stripe left rise
    glNormal3f(-1, 0, 0);
    glVertex3f(-42.5, 35, 21);
	glVertex3f(-42.5, 31, 21);
	glVertex3f(-42.5, 31, 20);
	glVertex3f(-42.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// right upper stripe right rise
    glNormal3f(1, 0, 0);
    glVertex3f(42.5, 35, 21);
	glVertex3f(42.5, 31, 21);
	glVertex3f(42.5, 31, 20);
	glVertex3f(42.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// left upper stripe upper rise
    glNormal3f(0, 1, 0);
    glVertex3f(-42.5, 35, 21);
	glVertex3f(-32.5, 35, 21);
	glVertex3f(-32.5, 35, 20);
	glVertex3f(-42.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// right upper stripe upper rise
    glNormal3f(0, 1, 0);
    glVertex3f(42.5, 35, 21);
	glVertex3f(32.5, 35, 21);
	glVertex3f(32.5, 35, 20);
	glVertex3f(42.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// left upper stripe right rise
    glNormal3f(1, 0, 0);
    glVertex3f(-32.5, 35, 21);
	glVertex3f(-32.5, 31, 21);
	glVertex3f(-32.5, 31, 20);
	glVertex3f(-32.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// right upper stripe left rise
    glNormal3f(-1, 0, 0);
    glVertex3f(32.5, 35, 21);
	glVertex3f(32.5, 31, 21);
	glVertex3f(32.5, 31, 20);
	glVertex3f(32.5, 35, 20);
  glEnd();

  glBegin(display_mode);					// left upper stripe lower rise
    glNormal3f(0, -1, 0);
    glVertex3f(-42.5, 31, 21);
	glVertex3f(-32.5, 31, 21);
	glVertex3f(-32.5, 31, 20);
	glVertex3f(-42.5, 31, 20);
  glEnd();

  glBegin(display_mode);					// right upper stripe lower rise
    glNormal3f(0, -1, 0);
    glVertex3f(42.5, 31, 21);
	glVertex3f(32.5, 31, 21);
	glVertex3f(32.5, 31, 20);
	glVertex3f(42.5, 31, 20);
  glEnd();

  glBegin(display_mode);					// left lower stripe left rise
    glNormal3f(-1, 0, 0);
    glVertex3f(-42.5, 29, 21);
	glVertex3f(-42.5, 25, 21);
	glVertex3f(-42.5, 25, 20);
	glVertex3f(-42.5, 29, 20);
  glEnd();

  glBegin(display_mode);					// right lower stripe right rise
    glNormal3f(1, 0, 0);
    glVertex3f(42.5, 29, 21);
	glVertex3f(42.5, 25, 21);
	glVertex3f(42.5, 25, 20);
	glVertex3f(42.5, 29, 20);
  glEnd();

  glBegin(display_mode);					// left lower stripe upper rise
    glNormal3f(0, 1, 0);
    glVertex3f(-42.5, 29, 21);
	glVertex3f(-32.5, 29, 21);
	glVertex3f(-32.5, 29, 20);
	glVertex3f(-42.5, 29, 20);
  glEnd();

  glBegin(display_mode);					// right lower stripe upper rise
    glNormal3f(0, 1, 0);
    glVertex3f(42.5, 29, 21);
	glVertex3f(32.5, 29, 21);
	glVertex3f(32.5, 29, 20);
	glVertex3f(42.5, 29, 20);
  glEnd();

  glBegin(display_mode);					// left lower stripe right rise
    glNormal3f(1, 0, 0);
    glVertex3f(-32.5, 29, 21);
	glVertex3f(-32.5, 25, 21);
	glVertex3f(-32.5, 25, 20);
	glVertex3f(-32.5, 29, 21);
  glEnd();

  glBegin(display_mode);					// right lower stripe left rise
    glNormal3f(-1, 0, 0);
    glVertex3f(32.5, 29, 21);
	glVertex3f(32.5, 25, 21);
	glVertex3f(32.5, 25, 20);
	glVertex3f(32.5, 29, 21);
  glEnd();

  glBegin(display_mode);					// left lower stripe lower rise
    glNormal3f(0, -1, 0);
    glVertex3f(-42.5, 25, 21);
	glVertex3f(-32.5, 25, 21);
	glVertex3f(-32.5, 25, 20);
	glVertex3f(-42.5, 25, 20);
  glEnd();

  glBegin(display_mode);					// right lower stripe lower rise
    glNormal3f(0, 0, -1);
    glVertex3f(42.5, 25, 21);
	glVertex3f(32.5, 25, 21);
	glVertex3f(32.5, 25, 20);
	glVertex3f(42.5, 25, 20);
  glEnd();

  mat_ambient[0] = 0.0;
  mat_ambient[1] = 0.0;
  mat_ambient[2] = 0.8;
  mat_diffuse[0] = 0.0;
  mat_diffuse[1] = 0.0;
  mat_diffuse[2] = 0.5;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// back brace back left face
    glNormal3f(0, 0, -1);
	glVertex3f(-45, 20, -15);
	glVertex3f(-50, 25, -15);
	glVertex3f(-50, 50, -15);
	glVertex3f(-45, 50, -15);
  glEnd();

  glBegin(display_mode);				// back brace back right face
    glNormal3f(0, 0, -1);
	glVertex3f(45, 20, -15);
	glVertex3f(50, 25, -15);
	glVertex3f(50, 50, -15);
	glVertex3f(45, 50, -15);
  glEnd();

  glBegin(display_mode);				// back brace back top face
    glNormal3f(0, 0, -1);
	glVertex3f(-50, 50, -15);
	glVertex3f(-45, 55, -15);
	glVertex3f(45, 55, -15);
	glVertex3f(50, 50, -15);
  glEnd();

  glBegin(display_mode);				// back brace front left face
    glNormal3f(0, 0, 1);
	glVertex3f(-45, 20, -5);
	glVertex3f(-50, 25, -5);
	glVertex3f(-50, 50, -5);
	glVertex3f(-45, 50, -5);
  glEnd();

  glBegin(display_mode);				// back brace front right face
    glNormal3f(0, 0, 1);
	glVertex3f(45, 20, -5);
	glVertex3f(50, 25, -5);
	glVertex3f(50, 50, -5);
	glVertex3f(45, 50, -5);
  glEnd();

  glBegin(display_mode);				// back brace front top face
    glNormal3f(0, 0, 1);
	glVertex3f(-50, 50, -5);
	glVertex3f(-45, 55, -5);
	glVertex3f(45, 55, -5);
	glVertex3f(50, 50, -5);
  glEnd();

  glBegin(display_mode);				// front brace back left face
    glNormal3f(0, 0, -1);
	glVertex3f(-45, 20, 5);
	glVertex3f(-50, 25, 5);
	glVertex3f(-50, 50, 5);
	glVertex3f(-45, 50, 5);
  glEnd();

  glBegin(display_mode);				// front brace back right face
    glNormal3f(0, 0, -1);
	glVertex3f(45, 20, 5);
	glVertex3f(50, 25, 5);
	glVertex3f(50, 50, 5);
	glVertex3f(45, 50, 5);
  glEnd();

  glBegin(display_mode);				// front brace back top face
    glNormal3f(0, 0, 1);
	glVertex3f(-50, 50, 15);
	glVertex3f(-45, 55, 15);
	glVertex3f(45, 55, 15);
	glVertex3f(50, 50, 15);
  glEnd();

  glBegin(display_mode);				// front brace back left face
    glNormal3f(0, 0, 1);
	glVertex3f(-45, 20, 15);
	glVertex3f(-50, 25, 15);
	glVertex3f(-50, 50, 15);
	glVertex3f(-45, 50, 15);
  glEnd();

  glBegin(display_mode);				// front brace back right face
    glNormal3f(0, 0, 1);
	glVertex3f(45, 20, 15);
	glVertex3f(50, 25, 15);
	glVertex3f(50, 50, 15);
	glVertex3f(45, 50, 15);
  glEnd();

  glBegin(display_mode);				// front brace back top face
    glNormal3f(0, 0, 1);
	glVertex3f(-50, 50, 15);
	glVertex3f(-45, 55, 15);
	glVertex3f(45, 55, 15);
	glVertex3f(50, 50, 15);
  glEnd();

  glBegin(display_mode);				// back brace lower left edge
    CalculateNormal(-5, 5, 0, -5, 5, -10);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-45, 20, -5);
	glVertex3f(-50, 25, -5);
	glVertex3f(-50, 25, -15);
	glVertex3f(-45, 20, -15);
  glEnd();

  glBegin(display_mode);				// front brace lower left edge
    CalculateNormal(-5, 5, 10, -5, 5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-45, 20, 5);
	glVertex3f(-50, 25, 5);
	glVertex3f(-50, 25, 15);
	glVertex3f(-45, 20, 15);
  glEnd();

  glBegin(display_mode);				// back brace lower right edge
    CalculateNormal(5, 5, -10, 5, 5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(45, 20, -5);
	glVertex3f(50, 25, -5);
	glVertex3f(50, 25, -15);
	glVertex3f(45, 20, -15);
  glEnd();

  glBegin(display_mode);				// front brace lower right edge
    CalculateNormal(5, 5, 0, 5, 5, 10);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(45, 20, 5);
	glVertex3f(50, 25, 5);
	glVertex3f(50, 25, 15);
	glVertex3f(45, 20, 15);
  glEnd();

  glBegin(display_mode);				// back brace left edge
    glNormal3f(-1, 0, 0);
    glVertex3f(-50, 25, -5);
	glVertex3f(-50, 50, -5);
	glVertex3f(-50, 50, -15);
	glVertex3f(-50, 25, -15);
  glEnd();

  glBegin(display_mode);				// front brace left edge
    glNormal3f(-1, 0, 0);
    glVertex3f(-50, 25, 5);
	glVertex3f(-50, 50, 5);
	glVertex3f(-50, 50, 15);
	glVertex3f(-50, 25, 15);
  glEnd();

  glBegin(display_mode);				// back brace right edge
    glNormal3f(1, 0, 0);
    glVertex3f(50, 25, -5);
	glVertex3f(50, 50, -5);
	glVertex3f(50, 50, -15);
	glVertex3f(50, 25, -15);
  glEnd();

  glBegin(display_mode);				// front brace right edge
    glNormal3f(1, 0, 0);
    glVertex3f(50, 25, 5);
	glVertex3f(50, 50, 5);
	glVertex3f(50, 50, 15);
	glVertex3f(50, 25, 15);
  glEnd();

  glBegin(display_mode);				// back brace top left edge
    CalculateNormal(5, 5, 0, 5, 5, -10);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-50, 50, -5);
	glVertex3f(-45, 55, -5);
	glVertex3f(-45, 55, -15);
	glVertex3f(-50, 50, -15);
  glEnd();

  glBegin(display_mode);				// back brace top right edge
    CalculateNormal(-5, 5, -10, -5, 5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(50, 50, -5);
	glVertex3f(45, 55, -5);
	glVertex3f(45, 55, -15);
	glVertex3f(50, 50, -15);
  glEnd();

  glBegin(display_mode);				// front brace top left edge
    CalculateNormal(5, 5, 10, 5, 5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-50, 50, 5);
	glVertex3f(-45, 55, 5);
	glVertex3f(-45, 55, 15);
	glVertex3f(-50, 50, 15);
  glEnd();

  glBegin(display_mode);				// front brace top right edge
    CalculateNormal(5, 5, 0, -5, 5, 10);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(50, 50, 5);
	glVertex3f(45, 55, 5);
	glVertex3f(45, 55, 15);
	glVertex3f(50, 50, 15);
  glEnd();

  glBegin(display_mode);				// back brace top edge
    glNormal3f(0, 1, 0);
    glVertex3f(-45, 55, -5);
	glVertex3f(45, 55, -5);
	glVertex3f(45, 55, -15);
	glVertex3f(-45, 55, -15);
  glEnd();

  glBegin(display_mode);				// front brace top edge
    glNormal3f(0, 1, 0);
    glVertex3f(-45, 55, 5);
	glVertex3f(45, 55, 5);
	glVertex3f(45, 55, 15);
	glVertex3f(-45, 55, 15);
  glEnd();

  mat_ambient[0] = 1.0;
  mat_ambient[1] = 1.0;
  mat_ambient[2] = 1.0;
  mat_diffuse[0] = 1.0;
  mat_diffuse[1] = 1.0;
  mat_diffuse[2] = 1.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// gun-mount front face
    glNormal3f(0, 0, 1);
    glVertex3f(22, 55, 12.5);
	glVertex3f(22, 60, 12.5);
	glVertex3f(32, 60, 12.5);
	glVertex3f(32, 55, 12.5);
  glEnd();

  glBegin(display_mode);				// gun-mount back face
    glNormal3f(0, 0, -1);
    glVertex3f(22, 55, 7.5);
	glVertex3f(22, 60, 7.5);
	glVertex3f(32, 60, 7.5);
	glVertex3f(32, 55, 7.5);
  glEnd();

  glBegin(display_mode);				// gun-mount left face
    glNormal3f(-1, 0, 0);
	glVertex3f(22, 55, 12.5);
	glVertex3f(22, 60, 12.5);
	glVertex3f(22, 60, 7.5);
	glVertex3f(22, 55, 7.5);
  glEnd();

  glBegin(display_mode);				// gun-mount right face
    glNormal3f(1, 0, 0);
	glVertex3f(32, 55, 12.5);
	glVertex3f(32, 60, 12.5);
	glVertex3f(32, 60, 7.5);
	glVertex3f(32, 55, 7.5);
  glEnd();

  glBegin(display_mode);				// gun-mount top face
    glNormal3f(0, 1, 0);
	glVertex3f(22, 60, 12.5);
	glVertex3f(22, 60, 7.5);
	glVertex3f(32, 60, 7.5);
	glVertex3f(32, 60, 12.5);
  glEnd();

  mat_ambient[0] = 0.0;
  mat_ambient[1] = 0.0;
  mat_ambient[2] = 1.0;
  mat_diffuse[0] = 0.0;
  mat_diffuse[1] = 0.0;
  mat_diffuse[2] = 0.8;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  if (display_mode == GL_LINE_LOOP)
  {
	glPushMatrix();
	  glTranslatef(-30, 67.5, -32.5);
	  glRotatef(90, 1, 0, 0);
	  TaperedWireCylinder(0, 12.5, 0, 20);
	  TaperedWireCylinder(15, 12.5, 12.5, 20);
	  glTranslatef(0, 15, 0);
	  TaperedWireCylinder(0, 12.5, 9.5, 20);
	  TaperedWireCylinder(3, 9.5, 9.5, 20);
	  glTranslatef(0, 3, 0);
	  TaperedWireCylinder(0, 9.5, 12.5, 20);
	  TaperedWireCylinder(30, 12.5, 12.5, 20);
	  glTranslatef(0, 30, 0);
	  TaperedWireCylinder(0, 12.5, 9.5, 20);
	  TaperedWireCylinder(2, 9.5, 9.5, 20);
	  glTranslatef(0, 2, 0);
	  TaperedWireCylinder(0, 9.5, 12.5, 20);
	  TaperedWireCylinder(4, 12.5, 12.5, 20);
	  glTranslatef(0, 4, 0);
	  TaperedWireCylinder(0, 12.5, 9.5, 20);
	  TaperedWireCylinder(5, 9.5, 9.5, 20);
	  glTranslatef(0, 5, 0);
	  TaperedWireCylinder(0, 9.5, 12.5, 20);
	  TaperedWireCylinder(4, 12.5, 12.5, 20);
	  glTranslatef(0, 4, 0);
	  TaperedWireCylinder(0, 12.5, 9.5, 20);
	  TaperedWireCylinder(2, 9.5, 9.5, 20);
	  glTranslatef(0, 2, 0);
	  TaperedWireCylinder(0, 9.5, 12.5, 20);
	  glPushMatrix();
	    glTranslatef(0, 5, 0);
		  mat_ambient[0] = 1.0;
          mat_ambient[1] = 0.0;
          mat_ambient[2] = 0.0;
          mat_diffuse[0] = 0.8;
          mat_diffuse[1] = 0.0;
          mat_diffuse[2] = 0.0;
          glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

		  TaperedWireCylinder(5, 12.5, 12.5, 20);
		  mat_ambient[0] = 0.0;
          mat_ambient[1] = 0.0;
          mat_ambient[2] = 1.0;
          mat_diffuse[0] = 0.0;
          mat_diffuse[1] = 0.0;
          mat_diffuse[2] = 1.0;
          glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	  glPopMatrix();
	  TaperedWireCylinder(15, 12.5, 12.5, 20);
	  glTranslatef(0, 15, 0);
	  TaperedWireCylinder(0, 12.5, 9.5, 20);
	  glTranslatef(0, -2, 0);
	  TaperedWireCylinder(0, 9.5, 0, 20);
	  TaperedWireCylinder(2, 9.5, 9.5, 20);
	glPopMatrix();
  }  // if statement
  else if (display_mode == GL_POLYGON)
  {
	glPushMatrix();
	  glTranslatef(-30, 67.5, -32.5);
	  glRotatef(90, 1, 0, 0);
	  TaperedCylinder(0, 12.5, 0, 20);
	  TaperedCylinder(15, 12.5, 12.5, 20);
	  glTranslatef(0, 15, 0);
	  TaperedCylinder(0, 12.5, 9.5, 20);
	  TaperedCylinder(3, 9.5, 9.5, 20);
	  glTranslatef(0, 3, 0);
	  TaperedCylinder(0, 9.5, 12.5, 20);
	  TaperedCylinder(30, 12.5, 12.5, 20);
	  glTranslatef(0, 30, 0);
	  TaperedCylinder(0, 12.5, 9.5, 20);
	  TaperedCylinder(2, 9.5, 9.5, 20);
	  glTranslatef(0, 2, 0);
	  TaperedCylinder(0, 9.5, 12.5, 20);
	  TaperedCylinder(4, 12.5, 12.5, 20);
	  glTranslatef(0, 4, 0);
	  TaperedCylinder(0, 12.5, 9.5, 20);
	  TaperedCylinder(5, 9.5, 9.5, 20);
	  glTranslatef(0, 5, 0);
	  TaperedCylinder(0, 9.5, 12.5, 20);
	  TaperedCylinder(4, 12.5, 12.5, 20);
	  glTranslatef(0, 4, 0);
	  TaperedCylinder(0, 12.5, 9.5, 20);
	  TaperedCylinder(2, 9.5, 9.5, 20);
	  glTranslatef(0, 2, 0);
	  TaperedCylinder(0, 9.5, 12.5, 20);
	  glPushMatrix();
	    glTranslatef(0, 5, 0);
		  mat_ambient[0] = 1.0;
          mat_ambient[1] = 0.0;
          mat_ambient[2] = 0.0;
          mat_diffuse[0] = 0.8;
          mat_diffuse[1] = 0.0;
          mat_diffuse[2] = 0.0;
          glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

		  TaperedCylinder(5, 12.6, 12.6, 20);
		  mat_ambient[0] = 0.0;
          mat_ambient[1] = 0.0;
          mat_ambient[2] = 1.0;
          mat_diffuse[0] = 0.0;
          mat_diffuse[1] = 0.0;
          mat_diffuse[2] = 1.0;
          glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
          glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	  glPopMatrix();
	  TaperedCylinder(15, 12.5, 12.5, 20);
	  glTranslatef(0, 15, 0);
	  TaperedCylinder(0, 12.5, 9.5, 20);
	  glTranslatef(0, -2, 0);
	  TaperedCylinder(0, 9.5, 0, 20);
	  TaperedCylinder(2, 9.5, 9.5, 20);
	glPopMatrix();
  }  // else statement
}  // DrawBody


void Decepticon :: SetWindowAngle(int new_value)
{
	window_angle = new_value;
}  // SetWindowAngle


void Decepticon :: OpenWindow()
{
	if (window_angle < 90)
	{
		window_angle ++;
		printf("Opening window.\n");
	}  // if statement
	else
		printf("Cannot open window further.\n");
}  // OpenWindow


void Decepticon :: CloseWindow()
{
	if (window_angle > 0)
	{
		window_angle--;
		printf("Closing window.\n");
	}  // if statement
	else
		printf("Cannot close window further.\n");
}  // CloseWindow
