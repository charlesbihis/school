#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawWindow()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  GLfloat mat_transparent[] = { 0.5, 0.5, 0.5, 0.5 };
  //GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };

  //glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
  glEnable (GL_BLEND);
  glDepthMask (GL_FALSE);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE);
  glDepthMask (GL_TRUE);

  GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// window
    glNormal3f(0, 0, 1);
	glVertex3f(-30, 30, 0.1);
	glVertex3f(-30, 5, 0.1);
	glVertex3f(-27.5, 2.5, 0.1);
	glVertex3f(27.5, 2.5, 0.1);
	glVertex3f(30, 5, 0.1);
	glVertex3f(30, 30, 0.1);
  glEnd();

  glDisable (GL_BLEND);

  mat_ambient[0] = 1.0;
  mat_ambient[1] = 1.0;
  mat_ambient[2] = 0.0;
  mat_diffuse[0] = 0.8;
  mat_diffuse[1] = 0.8;
  mat_diffuse[2] = 0.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// bottom left window face
    glNormal3f(0, 0, 1);
    glVertex3f(-32.5, 2.5, 2.5);
	glVertex3f(-30, 5, 2.5);
	glVertex3f(-27.5, 2.5, 2.5);
	glVertex3f(-30, 0, 2.5);
  glEnd();

  glBegin(display_mode);				// bottom right window face
    glNormal3f(0, 0, 1);
    glVertex3f(32.5, 2.5, 2.5);
	glVertex3f(30, 5, 2.5);
	glVertex3f(27.5, 2.5, 2.5);
	glVertex3f(30, 0, 2.5);
  glEnd();

  glBegin(display_mode);				// bottom window face
    glNormal3f(0, 0, 1);
    glVertex3f(-30, 0, 2.5);
	glVertex3f(30, 0, 2.5);
	glVertex3f(27.5, 2.5, 2.5);
	glVertex3f(-27.5, 2.5, 2.5);
  glEnd();

  glBegin(display_mode);				// top window face
    glNormal3f(0, 0, 1);
    glVertex3f(-32.5, 32.5, 2.5);
	glVertex3f(-30, 30, 2.5);
	glVertex3f(30, 30, 2.5);
	glVertex3f(32.5, 32.5, 2.5);
  glEnd();

  glBegin(display_mode);				// left window face
    glVertex3f(-32.5, 2.5, 2.5);
	glVertex3f(-32.5, 32.5, 2.5);
	glVertex3f(-30, 30, 2.5);
	glVertex3f(-30, 5, 2.5);
  glEnd();

  glBegin(display_mode);				// right window face
    glNormal3f(0, 0, 1);
    glVertex3f(32.5, 2.5, 2.5);
	glVertex3f(32.5, 32.5, 2.5);
	glVertex3f(30, 30, 2.5);
	glVertex3f(30, 5, 2.5);
  glEnd();

  glBegin(display_mode);					// bottom left outer rise
    CalculateNormal(2.5, -2.5, -2.5, 2.5, -2.5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-32.5, 2.5, 2.5);
	glVertex3f(-30, 0, 2.5);
	glVertex3f(-30, 0, 0);
	glVertex3f(-32.5, 2.5, 0);
  glEnd();

  glBegin(display_mode);					// bottom right outer rise
    CalculateNormal(-2.5, -2.5, 0, -2.5, -2.5, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(32.5, 2.5, 2.5);
	glVertex3f(30, 0, 2.5);
	glVertex3f(30, 0, 0);
	glVertex3f(32.5, 2.5, 0);
  glEnd();

  glBegin(display_mode);					// bottom left inner rise
    CalculateNormal(2.5, -2.5, 0, 2.5, -2.5, -2.5);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-30, 5, 2.5);
	glVertex3f(-27.5, 2.5, 2.5);
	glVertex3f(-27.5, 2.5, 0);
	glVertex3f(-30, 5, 0);
  glEnd();

  glBegin(display_mode);					// bottom right inner rise
    CalculateNormal(-2.5, -2.5, -2.5, -2.5, -2.5, 0);
    glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(30, 5, 2.5);
	glVertex3f(27.5, 2.5, 2.5);
	glVertex3f(27.5, 2.5, 0);
	glVertex3f(30, 5, 0);
  glEnd();

  glBegin(display_mode);					// left outer rise
    glNormal3f(-1, 0, 0);
    glVertex3f(-32.5, 2.5, 2.5);
	glVertex3f(-32.5, 32.5, 2.5);
	glVertex3f(-32.5, 32.5, 0);
	glVertex3f(-32.5, 2.5, 0);
  glEnd();

  glBegin(display_mode);					// right outer rise
    glNormal3f(1, 0, 0);
    glVertex3f(32.5, 2.5, 2.5);
	glVertex3f(32.5, 32.5, 2.5);
	glVertex3f(32.5, 32.5, 0);
	glVertex3f(32.5, 2.5, 0);
  glEnd();

  glBegin(display_mode);					// left inner rise
    glNormal3f(1, 0, 0);
    glVertex3f(-30, 5, 2.5);
	glVertex3f(-30, 30, 2.5);
	glVertex3f(-30, 30, 0);
	glVertex3f(-30, 5, 0);
  glEnd();

  glBegin(display_mode);					// right inner rise
    glNormal3f(-1, 0, 0);
    glVertex3f(30, 5, 2.5);
	glVertex3f(30, 30, 2.5);
	glVertex3f(30, 30, 0);
	glVertex3f(30, 5, 0);
  glEnd();

  glBegin(display_mode);					// upper outer rise
    glNormal3f(0, 1, 0);
    glVertex3f(-32.5, 32.5, 2.5);
	glVertex3f(32.5, 32.5, 2.5);
	glVertex3f(32.5, 32.5, 0);
	glVertex3f(-32.5, 32.5, 0);
  glEnd();

  glBegin(display_mode);					// upper inner rise
    glNormal3f(0, -1, 0);
    glVertex3f(-30, 30, 2.5);
	glVertex3f(30, 30, 2.5);
	glVertex3f(30, 30, 0);
	glVertex3f(-30, 30, 0);
  glEnd();

  glBegin(display_mode);					// lower inner rise
    glNormal3f(0, 1, 0);
    glVertex3f(-27.5, 2.5, 2.5);
	glVertex3f(27.5, 2.5, 2.5);
	glVertex3f(27.5, 2.5, 0);
	glVertex3f(-27.5, 2.5, 0);
  glEnd();

  glBegin(display_mode);					// lower outer rise
    glNormal3f(0, -1, 0);
    glVertex3f(-30, 0, 2.5);
	glVertex3f(30, 0, 2.5);
	glVertex3f(30, 0, 0);
	glVertex3f(-30, 0, 0);
  glEnd();
}  // DrawWindow
