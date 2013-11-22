#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawRewind()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);			// rewind button face
    glNormal3f(0, 0, 1);
	glVertex3f(-15, 7.5, 2.5);
	glVertex3f(-15, -7.5, 2.5);
	glVertex3f(-27.5, 0, 2.5);
  glEnd();

  glBegin(display_mode);			// rewind button right edge
    glNormal3f(1, 0, 0);
	glVertex3f(-15, 7.5, 2.5);
	glVertex3f(-15, -7.5, 2.5);
	glVertex3f(-15, -7.5, 0);
	glVertex3f(-15, 7.5, 0);
  glEnd();

  glBegin(display_mode);			// rewind top left edge
    CalculateNormal(-12.5, -7.5, -2.5, -12.5, -7.5, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-15, 7.5, 2.5);
	glVertex3f(-27.5, 0, 2.5);
	glVertex3f(-27.5, 0, 0);
	glVertex3f(-15, 7.5, 0);
  glEnd();

  glBegin(display_mode);			// rewind bottom left edge
    CalculateNormal(-12.5, 7.5, 0, -12.5, 7.5, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-15, -7.5, 2.5);
	glVertex3f(-27.5, 0, 2.5);
	glVertex3f(-27.5, 0, 0);
	glVertex3f(-15, -7.5, 0);
  glEnd();
}  // DrawRewind


void Decepticon :: DrawFastForward()
{
  glBegin(display_mode);			// fastforward button face
    glNormal3f(0, 0, 1);
	glVertex3f(15, 7.5, 2.5);
	glVertex3f(15, -7.5, 2.5);
	glVertex3f(27.5, 0, 2.5);
  glEnd();

  glBegin(display_mode);			// fastforward button left edge
    glNormal3f(-1, 0, 0);
	glVertex3f(15, 7.5, 2.5);
	glVertex3f(15, -7.5, 2.5);
	glVertex3f(15, -7.5, 0);
	glVertex3f(15, 7.5, 0);
  glEnd();

  glBegin(display_mode);			// fastforward button top right edge
    CalculateNormal(12.5, -7.5, 0, 12.5, -7.5, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(15, 7.5, 2.5);
	glVertex3f(27.5, 0, 2.5);
	glVertex3f(27.5, 0, 0);
	glVertex3f(15, 7.5, 0);
  glEnd();

  glBegin(display_mode);			// fastforward button bottom right edge
    CalculateNormal(12.5, 7.5, -2.5, 12.5, 7.5, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(15, -7.5, 2.5);
	glVertex3f(27.5, 0, 2.5);
	glVertex3f(27.5, 0, 0);
	glVertex3f(15, -7.5, 0);
  glEnd();
}  // DrawFastForward


void Decepticon :: DrawPlay()
{
  glBegin(display_mode);			// play button face
    glNormal3f(0, 0, 1);
	glVertex3f(-12.5, 1.5, 2.5);
	glVertex3f(-12.5, 7.5, 2.5);
	glVertex3f(12.5, 7.5, 2.5);
	glVertex3f(12.5, 1.5, 2.5);
  glEnd();

  glBegin(display_mode);			// play button left edge
    glNormal3f(-1, 0, 0);
    glVertex3f(-12.5, 1.5, 2.5);
	glVertex3f(-12.5, 7.5, 2.5);
	glVertex3f(-12.5, 7.5, 0);
	glVertex3f(-12.5, 1.5, 0);
  glEnd();

  glBegin(display_mode);			// play button right edge
    glNormal3f(1, 0, 0);
    glVertex3f(12.5, 1.5, 2.5);
	glVertex3f(12.5, 7.5, 2.5);
	glVertex3f(12.5, 7.5, 0);
	glVertex3f(12.5, 1.5, 0);
  glEnd();

  glBegin(display_mode);			// play button top edge
    glNormal3f(0, 1, 0);
	glVertex3f(-12.5, 7.5, 2.5);
	glVertex3f(12.5, 7.5, 2.5);
	glVertex3f(12.5, 7.5, 0);
	glVertex3f(-12.5, 7.5, 0);
  glEnd();

  glBegin(display_mode);			// play button bottom edge
    glNormal3f(0, -1, 0);
	glVertex3f(-12.5, 2.5, 2.5);
	glVertex3f(12.5, 2.5, 2.5);
	glVertex3f(12.5, 2.5, 0);
	glVertex3f(-12.5, 2.5, 0);
  glEnd();
}  // DrawPlay


void Decepticon :: DrawStop()
{
  glBegin(display_mode);			// stop button face
    glNormal3f(0, 0, 1);
	glVertex3f(-12.5, -1.5, 2.5);
	glVertex3f(-12.5, -7.5, 2.5);
	glVertex3f(-1.5, -7.5, 2.5);
	glVertex3f(-1.5, -1.5, 2.5);
  glEnd();

  glBegin(display_mode);			// stop button left edge
    glNormal3f(-1, 0, 0);
	glVertex3f(-12.5, -1.5, 2.5);
	glVertex3f(-12.5, -7.5, 2.5);
	glVertex3f(-12.5, -7.5, 0);
	glVertex3f(-12.5, -1.5, 0);
  glEnd();

  glBegin(display_mode);			// stop button right edge
    glNormal3f(1, 0, 0);
	glVertex3f(-1.5, -1.5, 2.5);
	glVertex3f(-1.5, -7.5, 2.5);
	glVertex3f(-1.5, -7.5, 0);
	glVertex3f(-1.5, -1.5, 0);
  glEnd();

  glBegin(display_mode);			// stop button bottom edge
    glNormal3f(0, -1, 0);
	glVertex3f(-12.5, -7.5, 2.5);
	glVertex3f(-1.5, -7.5, 2.5);
	glVertex3f(-1.5, -7.5, 0);
	glVertex3f(-12.5, -7.5, 0);
  glEnd();

  glBegin(display_mode);			// stop button top edge
    glNormal3f(0, 1, 0);
	glVertex3f(-12.5, -1.5, 2.5);
	glVertex3f(-1.5, -1.5, 2.5);
	glVertex3f(-1.5, -1.5, 0);
	glVertex3f(-12.5, -1.5, 0);
  glEnd();
}  // DrawStop


void Decepticon :: DrawPause()
{
  glBegin(display_mode);			// pause button face
    glNormal3f(0, 0, 1);
	glVertex3f(12.5, -1.5, 2.5);
	glVertex3f(12.5, -7.5, 2.5);
	glVertex3f(1.5, -7.5, 2.5);
	glVertex3f(1.5, -1.5, 2.5);
  glEnd();

  glBegin(display_mode);			// pause button right edge
    glNormal3f(1, 0, 0);
	glVertex3f(12.5, -1.5, 2.5);
	glVertex3f(12.5, -7.5, 2.5);
	glVertex3f(12.5, -7.5, 0);
	glVertex3f(12.5, -1.5, 0);
  glEnd();

  glBegin(display_mode);			// pause button left edge
    glNormal3f(-1, 0, 0);
	glVertex3f(1.5, -1.5, 2.5);
	glVertex3f(1.5, -7.5, 2.5);
	glVertex3f(1.5, -7.5, 0);
	glVertex3f(1.5, -1.5, 0);
  glEnd();

  glBegin(display_mode);			// pause button bottom edge
    glNormal3f(0, -1, 0);
	glVertex3f(12.5, -7.5, 2.5);
	glVertex3f(1.5, -7.5, 2.5);
	glVertex3f(1.5, -7.5, 0);
	glVertex3f(12.5, -7.5, 0);
  glEnd();

  glBegin(display_mode);			// pause button top edge
    glNormal3f(0, 1, 0);
	glVertex3f(12.5, -1.5, 2.5);
	glVertex3f(1.5, -1.5, 2.5);
	glVertex3f(1.5, -1.5, 0);
	glVertex3f(12.5, -1.5, 0);
  glEnd();

  GLfloat mat_ambient[] = {0.0, 0.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {0.0, 0.0, 0.8, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}  // DrawPause
