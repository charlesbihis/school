#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawFoot()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  glScalef(1, 1, 0.85);

  GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);			// foot toe plate
    CalculateNormal(20, 5, -2.5, 0, 5, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, 0, 40);
	glVertex3f(-10, 5, 37.5);
	glVertex3f(10, 5, 37.5);
	glVertex3f(10, 0, 40);
  glEnd();

  glBegin(display_mode);			// foot top ramp
    CalculateNormal(20, 5, -27.5, 0, 5, -27.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, 5, 37.5);
	glVertex3f(-10, 10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 5, 37.5);
  glEnd();

  glBegin(display_mode);			// foot top face
    glNormal3f(0, 1, 0);
	glVertex3f(-10, 10, 10);
	glVertex3f(-10, 10, -15);
	glVertex3f(10, 10, -15);
	glVertex3f(10, 10, 10);
  glEnd();

  glBegin(display_mode);			// foot back face
    CalculateNormal(20, 0, 0, 20, -10, -5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, 10, -15);
	glVertex3f(10, 10, -15);
	glVertex3f(10, 0, -20);
	glVertex3f(-10, 0, -20);
  glEnd();

  glBegin(display_mode);			// foot left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-10, 0, 40);
	glVertex3f(-10, 5, 37.5);
	glVertex3f(-10, 10, 10);
	glVertex3f(-10, 10, -15);
	glVertex3f(-10, 0, -20);
  glEnd();

  glBegin(display_mode);			// foot right face
    glNormal3f(1, 0, 0);
    glVertex3f(10, 0, 40);
	glVertex3f(10, 5, 37.5);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, -15);
	glVertex3f(10, 0, -20);
  glEnd();

  glBegin(display_mode);			// foot bottom face
    glNormal3f(0, -1, 0);
	glVertex3f(-10, 0, 40);
	glVertex3f(10, 0, 40);
	glVertex3f(10, 0, -20);
	glVertex3f(-10, 0, -20);
  glEnd();

  glBegin(display_mode);			// foot top piece top slanted plate
    CalculateNormal(10, 0, 0, 10, 7.5, -15);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-5, 7.5, 25);
	glVertex3f(5, 7.5, 25);
	glVertex3f(5, 15, 10);
	glVertex3f(-5, 15, 10);
  glEnd();

  glBegin(display_mode);			// foot top piece top plate
    glNormal3f(0, 1, 0);
    glVertex3f(-5, 15, 10);
	glVertex3f(5, 15, 10);
	glVertex3f(5, 15, -5);
	glVertex3f(-5, 15, -5);
  glEnd();

  glBegin(display_mode);			// foot top piece left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-5, 7.5, 25);
	glVertex3f(-5, 15, 10);
	glVertex3f(-5, 15, -5);
	glVertex3f(-5, 10, -10);
  glEnd();

  glBegin(display_mode);			// foot top piece right face
    glNormal3f(1, 0, 0);
    glVertex3f(5, 7.5, 25);
	glVertex3f(5, 15, 10);
	glVertex3f(5, 15, -5);
	glVertex3f(5, 10, -10);
  glEnd();

  glBegin(display_mode);			// foot top piece back face
    CalculateNormal(10, 5, 5, 10, 0, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-5, 10, -10);
	glVertex3f(5, 10, -10);
	glVertex3f(5, 15, -5);
	glVertex3f(-5, 15, -5);
  glEnd();
}  // DrawFoot


void Decepticon :: SetRightFootAngle(int new_value)
{
	right_foot_angle = new_value;
}  // SetRightFootAngle


void Decepticon :: RaiseRightFoot()
{
	if (right_foot_angle < 45)
	{
		right_foot_angle++;
		printf("Raising right foot.\n");
	}  // if statement
	else
		printf("Cannot raise right foot further.\n");
}  // RaiseRightFoot


void Decepticon :: LowerRightFoot()
{
	if (right_foot_angle > -45)
	{
		right_foot_angle--;
		printf("Lowering right foot.\n");
	}  // if statement
	else
		printf("Cannot lower right foot further.\n");
}  // LowerRightFoot


void Decepticon :: SetRightFootRetract(int new_value)
{
	right_foot_retract = new_value;
}  // SetRightFootRetract


void Decepticon :: SetLeftFootAngle(int new_value)
{
	left_foot_angle = new_value;
}  // SetLeftFootAngle


void Decepticon :: RaiseLeftFoot()
{
	if (left_foot_angle < 45)
	{
		left_foot_angle++;
		printf("Raising left foot.\n");
	}  // if statement
	else
		printf("Cannot raise left foot further.\n");
}  // RaiseLeftFoot


void Decepticon :: LowerLeftFoot()
{
	if (left_foot_angle > -45)
	{
		left_foot_angle--;
		printf("Lowering left foot.\n");
	}  // if statement
	else
		printf("Cannot lower left foot further.\n");
}  // LowerLeftFoot


void Decepticon :: SetLeftFootRetract(int new_value)
{
	left_foot_retract = new_value;
}  // SetLeftFootRetract
