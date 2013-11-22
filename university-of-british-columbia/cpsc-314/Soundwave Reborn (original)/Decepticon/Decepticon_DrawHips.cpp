#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawHips()
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

  glBegin(display_mode);			// hips top face
    glNormal3f(0, 1, 0);
	glVertex3f(-32.5, 0, -15);
	glVertex3f(-35, 0, -12.5);
	glVertex3f(-35, 0, 12.5);
	glVertex3f(-32.5, 0, 15);
	glVertex3f(32.5, 0, 15);
	glVertex3f(35, 0, 12.5);
	glVertex3f(35, 0, -12.5);
	glVertex3f(32.5, 0, -15);
  glEnd();

  glBegin(display_mode);			// hips back face
    glVertex3f(-35, 0, -12.5);			// no normal needed (not visible - hidden behind 'hips back raised face)
	glVertex3f(-37.5, -20, -12.5);
	glVertex3f(-35, -20, -12.5);
	glVertex3f(-10, -28, -12.5);
	glVertex3f(10, -28, -12.5);
	glVertex3f(35, -20, -12.5);
	glVertex3f(37.5, -20, -12.5);
	glVertex3f(35, 0, -12.5);
  glEnd();

  glBegin(display_mode);			// hips front face
    glVertex3f(-35, 0, 12.5);			// no normal needed (not visible - hidden behind 'hips front raised face)
	glVertex3f(-37.5, -20, 12.5);
	glVertex3f(-35, -20, 12.5);
	glVertex3f(-10, -28, 12.5);
	glVertex3f(10, -28, 12.5);
	glVertex3f(35, -20, 12.5);
	glVertex3f(37.5, -20, 12.5);
	glVertex3f(35, 0, 12.5);
  glEnd();

  glBegin(display_mode);			// hips back raised face
    glNormal3f(0, 0, -1);
    glVertex3f(-32.5, 0, -15);
	glVertex3f(-35, -20, -15);
	glVertex3f(-10, -28, -15);
	glVertex3f(10, -28, -15);
	glVertex3f(35, -20, -15);
	glVertex3f(32.5, 0, -15);
  glEnd();

  glBegin(display_mode);			// hips front raised face
    glNormal3f(0, 0, 1);
    glVertex3f(-32.5, 0, 15);
	glVertex3f(-35, -20, 15);
	glVertex3f(-10, -28, 15);
	glVertex3f(10, -28, 15);
	glVertex3f(35, -20, 15);
	glVertex3f(32.5, 0, 15);
  glEnd();

  glBegin(display_mode);			// hips back left edge
    CalculateNormal(-5, -20, 2.5, -2.5, 0, 2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-32.5, 0, -15);
	glVertex3f(-35, 0, -12.5);
	glVertex3f(-37.5, -20, -12.5);
	glVertex3f(-35, -20, -15);
  glEnd();

  glBegin(display_mode);			// hips front left edge
    CalculateNormal(-2.5, 0, -2.5, -5, -20, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-32.5, 0, 15);
	glVertex3f(-35, 0, 12.5);
	glVertex3f(-37.5, -20, 12.5);
	glVertex3f(-35, -20, 15);
  glEnd();

  glBegin(display_mode);			// hips back right edge
    CalculateNormal(2.5, 0, 2.5, 5, -20, 2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(32.5, 0, -15);
	glVertex3f(35, 0, -12.5);
	glVertex3f(37.5, -20, -12.5);
	glVertex3f(35, -20, -15);
  glEnd();

  glBegin(display_mode);			// hips front right edge
    CalculateNormal(5, -20, -2.5, 2.5, 0, -2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(32.5, 0, 15);
	glVertex3f(35, 0, 12.5);
	glVertex3f(37.5, -20, 12.5);
	glVertex3f(35, -20, 15);
  glEnd();

  glBegin(display_mode);			// hips left face
    CalculateNormal(-2.5, -20, 0, -2.5, -20, 25);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-35, 0, -12.5);
	glVertex3f(-37.5, -20, -12.5);
	glVertex3f(-37.5, -20, 12.5);
	glVertex3f(-35, 0, 12.5);
  glEnd();

  glBegin(display_mode);			// hips right face
    CalculateNormal(2.5, -20, 25, 2.5, -20, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(35, 0, -12.5);
	glVertex3f(37.5, -20, -12.5);
	glVertex3f(37.5, -20, 12.5);
	glVertex3f(35, 0, 12.5);
  glEnd();

  glBegin(display_mode);			// hips left underside edge
    CalculateNormal(-2.5, 0, 27.5, -2.5, 0, 2.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-35, -20, -15);
	glVertex3f(-37.5, -20, -12.5);
	glVertex3f(-37.5, -20, 12.5);
	glVertex3f(-35, -20, 15);
  glEnd();

  glBegin(display_mode);			// hips right underside edge
    CalculateNormal(2.5, 0, 2.5, 2.5, 0, 27.5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(35, -20, -15);
	glVertex3f(37.5, -20, -12.5);
	glVertex3f(37.5, -20, 12.5);
	glVertex3f(35, -20, 15);
  glEnd();

  glBegin(display_mode);			// hips crotch back face
    CalculateNormal(16, -12, 9, 4, -12, 9);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, -28, -15);
	glVertex3f(-6, -40, -6);
	glVertex3f(6, -40, -6);
	glVertex3f(10, -28, -15);
  glEnd();

  glBegin(display_mode);			// hips crotch front face
    CalculateNormal(4, -12, -9, 16, -12, -9);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, -28, 15);
	glVertex3f(-6, -40, 6);
	glVertex3f(6, -40, 6);
	glVertex3f(10, -28, 15);
  glEnd();

  glBegin(display_mode);			// hips crotch left face
    CalculateNormal(4, -12, 9, 4, -12, 21);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, -28, -15);
	glVertex3f(-6, -40, -6);
    glVertex3f(-6, -40, 6);
	glVertex3f(-10, -28, 15);
  glEnd();

  glBegin(display_mode);			// hips crotch right face
    CalculateNormal(-4, -12, 21, -4, -12, 9);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(10, -28, -15);
	glVertex3f(6, -40, -6);
    glVertex3f(6, -40, 6);
	glVertex3f(10, -28, 15);
  glEnd();

  glBegin(display_mode);			// hips crotch bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(-6, -40, -6);
	glVertex3f(-6, -40, 6);
	glVertex3f(6, -40, 6);
	glVertex3f(6, -40, -6);
  glEnd();
}  // DrawHips


void Decepticon :: SetBendAngle(int new_value)
{
	bend_angle = new_value;
}  // SetBendAngle


void Decepticon :: LeanForward()
{
	if (bend_angle < 135)
	{
		bend_angle++;
		printf("Bending forward.\n");
	}  // if statement
	else
		printf("Cannot bend further.\n");
}  // LeanForward


void Decepticon :: LeanBackward()
{
	// restrictions commented out for backflip animation
	//if (bend_angle > -45)  
	{
		bend_angle--;
		printf("Bending backwards.\n");
	}  // if statement
	//else
		printf("Cannot bend further.\n");
}  // LeanBackward


void Decepticon :: RaiseHips()
{
  hips_angle++;
}  // RaiseHips


void Decepticon :: LowerHips()
{
  hips_angle--;
}  // RaiseHips