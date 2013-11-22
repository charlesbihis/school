#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawTorso()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  GLfloat mat_ambient[] = {0.0, 0.0, 0.8, 1.0};
  GLfloat mat_diffuse[] = {0.0, 0.0, 0.5, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);			// torso back face
    glVertex3f(-32.5, 0, -12.5);			// no normal needed (not visible - hidden behind 'torso back raised face')
	glVertex3f(32.5, 0, -12.5);
	glVertex3f(27.5, -20, -7.5);
	glVertex3f(-27.5, -20, -7.5);
  glEnd();

  glBegin(display_mode);			// torso front face
    glVertex3f(-32.5, 0, 12.5);			// no normal needed (not visible - hidden behind 'torso front raised face')
	glVertex3f(32.5, 0, 12.5);
	glVertex3f(27.5, -20, 7.5);
	glVertex3f(-27.5, -20, 7.5);
  glEnd();

  glBegin(display_mode);			// torso back raised face
    CalculateNormal(50, 0, 0, 55, -20, 5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-27.5, 0, -15);
	glVertex3f(27.5, 0, -15);
	glVertex3f(22.5, -20, -10);
	glVertex3f(-22.5, -20, -10);
  glEnd();

  glBegin(display_mode);			// torso front raised face
    CalculateNormal(55, -20, -5, 50, 0, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-27.5, 0, 15);
	glVertex3f(27.5, 0, 15);
	glVertex3f(22.5, -20, 10);
	glVertex3f(-22.5, -20, 10);
  glEnd();

  glBegin(display_mode);			// torso back left edge
    CalculateNormal(0, -20, 7.5, -5, 0, 2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-27.5, 0, -15);
	glVertex3f(-32.5, 0, -12.5);
	glVertex3f(-27.5, -20, -7.5);
	glVertex3f(-22.5, -20, -10);
  glEnd();

  glBegin(display_mode);			// torso front left edge
    CalculateNormal(-5, 0, -2.5, 0, -20, -7.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-27.5, 0, 15);
	glVertex3f(-32.5, 0, 12.5);
	glVertex3f(-27.5, -20, 7.5);
	glVertex3f(-22.5, -20, 10);
  glEnd();

  glBegin(display_mode);			// torso back right edge
    CalculateNormal(5, 0, 2.5, 0, -20, 7.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(27.5, 0, -15);
	glVertex3f(32.5, 0, -12.5);
	glVertex3f(27.5, -20, -7.5);
	glVertex3f(22.5, -20, -10);
  glEnd();

  glBegin(display_mode);			// torso front right edge
    CalculateNormal(0, -20, -7.5, 5, 0, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(27.5, 0, 15);
	glVertex3f(32.5, 0, 12.5);
	glVertex3f(27.5, -20, 7.5);
	glVertex3f(22.5, -20, 10);
  glEnd();

  glBegin(display_mode);			// torso left face
    CalculateNormal(5, -20, 5, 0, 0, 25);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-32.5, 0, -12.5);
	glVertex3f(-32.5, 0, 12.5);
	glVertex3f(-27.5, -20, 7.5);
	glVertex3f(-27.5, -20, -7.5);
  glEnd();

  glBegin(display_mode);			// torso right face
    CalculateNormal(0, 0, 25, -5, -20, 5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(32.5, 0, -12.5);
	glVertex3f(32.5, 0, 12.5);
	glVertex3f(27.5, -20, 7.5);
	glVertex3f(27.5, -20, -7.5);
  glEnd();

  mat_ambient[0] = 0.0;
  mat_ambient[1] = 0.0;
  mat_ambient[2] = 1.0;
  mat_diffuse[0] = 0.0;
  mat_diffuse[1] = 0.0;
  mat_diffuse[2] = 0.8;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}  // DrawTorso


void Decepticon :: SetTorsoLength(int new_value)
{
	torso_length = new_value;
}  // SetTorsoLength
