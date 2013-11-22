#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawLowerLeg()
{
  if (anti_aliasing)
  {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1.5);
  }  // if statement

  glScalef(1.1, 1.1, 1.1);

  GLfloat mat_ambient[] = {0.0, 0.0, 1.0, 1.0};
  GLfloat mat_diffuse[] = {0.0, 0.0, 0.8, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glBegin(display_mode);				// lower leg back left edge
    glNormal3f(0, 0, -1);
    glVertex3f(-12.5, 5, -10);
	glVertex3f(-7.5, 5, -10);
	glVertex3f(-7.5, -10, -10);
	glVertex3f(-12.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg top left edge
    glNormal3f(0, 1, 0);
    glVertex3f(-12.5, 5, -10);
	glVertex3f(-7.5, 5, -10);
	glVertex3f(-7.5, 5, 10);
	glVertex3f(-12.5, 5, 10);
  glEnd();

  glBegin(display_mode);				// lower leg front left edge
    CalculateNormal(5, -15, 5, 5, 0, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-12.5, 5, 10);
	glVertex3f(-7.5, 5, 10);
	glVertex3f(-7.5, -10, 17.5);
	glVertex3f(-12.5, -10, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg bottom left edge
    glNormal3f(0, -1, 0);
    glVertex3f(-7.5, -10, 17.5);
	glVertex3f(-12.5, -10, 17.5);
	glVertex3f(-12.5, -10, -10);
	glVertex3f(-7.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg back right edge
    glNormal3f(0, 0, -1);
    glVertex3f(12.5, 5, -10);
	glVertex3f(7.5, 5, -10);
	glVertex3f(7.5, -10, -10);
	glVertex3f(12.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg top right edge
    glNormal3f(0, 1, 0);
    glVertex3f(12.5, 5, -10);
	glVertex3f(7.5, 5, -10);
	glVertex3f(7.5, 5, 10);
	glVertex3f(12.5, 5, 10);
  glEnd();

  glBegin(display_mode);				// lower leg front right edge
    CalculateNormal(-5, 0, 0, -5, -15, 5);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(12.5, 5, 10);
	glVertex3f(7.5, 5, 10);
	glVertex3f(7.5, -10, 17.5);
	glVertex3f(12.5, -10, 17.5);
  glEnd();

//  glBegin(display_mode);				// lower leg bottom right edge
//    glVertex3f(7.5, -10, 15);				// no normal needed
//	glVertex3f(12.5, -10, 15);
//	glVertex3f(12.5, -10, -10);
//	glVertex3f(7.5, -10, -10);
//  glEnd();

  glBegin(display_mode);				// lower leg shin plate back face
    glNormal3f(0, 0, -1);
    glVertex3f(-10, -10, -10);
	glVertex3f(-10, -45, -10);
	glVertex3f(12.5, -45, -10);
	glVertex3f(12.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg shin plate front face
    glNormal3f(0, 0, 1);
    glVertex3f(-10, -10, 25);
	glVertex3f(-10, -30, 25);
	glVertex3f(12.5, -30, 25);
	glVertex3f(12.5, -10, 25);
  glEnd();

  glBegin(display_mode);				// lower leg shin plate top face
    glNormal3f(0, 1, 0);
    glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 25);
	glVertex3f(12.5, -10, 25);
	glVertex3f(12.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg shin plate slanted face
    CalculateNormal(22.5, -7.5, -5, 22.5, 0, 0);
	glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
    glVertex3f(-10, -30, 25);
	glVertex3f(12.5, -30, 25);
	glVertex3f(12.5, -42.5, 17.5);
	glVertex3f(-10, -42.5, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate top edge
    glNormal3f(0, 1, 0);
    glVertex3f(-12.5, -30, -10);
	glVertex3f(-12.5, -30, 17.5);
	glVertex3f(-10, -30, 17.5);
	glVertex3f(-10, -30, -10);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate front edge
    glNormal3f(0, 0, 1);
    glVertex3f(-10, -30, 17.5);
	glVertex3f(-12.5, -30, 17.5);
	glVertex3f(-12.5, -70, 17.5);
	glVertex3f(-10, -70, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate back edge
    glNormal3f(0, 0, -1);
    glVertex3f(-10, -30, -10);
	glVertex3f(-12.5, -30, -10);
	glVertex3f(-12.5, -70, -10);
	glVertex3f(-10, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate inner edge
    glNormal3f(1, 0, 0);
    glVertex3f(-10, -30, 17.5);
	glVertex3f(-10, -30, -10);
	glVertex3f(-10, -70, -10);
	glVertex3f(-10, -70, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate outer edge
    glNormal3f(-1, 0, 0);
    glVertex3f(-12.5, -30, 17.5);
	glVertex3f(-12.5, -30, -10);
	glVertex3f(-12.5, -70, -10);
	glVertex3f(-12.5, -70, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg inside plate bottom edge
    glNormal3f(0, -1, 0);
    glVertex3f(-12.5, -70, -10);
	glVertex3f(-12.5, -70, 17.5);
	glVertex3f(-10, -70, 17.5);
	glVertex3f(-10, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg flat front face
    glNormal3f(0, 0, 1);
    glVertex3f(-10, -42.5, 17.5);
	glVertex3f(-10, -45, 17.5);
	glVertex3f(12.5, -45, 17.5);
	glVertex3f(12.5, -42.5, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg flat bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(12.5, -45, 17.5);
	glVertex3f(12.5, -45, -10);
	glVertex3f(-10, -45, -10);
	glVertex3f(-10, -45, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg right plate inside face
    glNormal3f(-1, 0, 0);
    glVertex3f(10, -45, -10);
	glVertex3f(10, -70, -10);
	glVertex3f(10, -70, 15);
	glVertex3f(10, -45, 15);
  glEnd();

  glBegin(display_mode);				// lower leg right plate outside face
    glNormal3f(1, 0, 0);
    glVertex3f(12.5, -45, -10);
	glVertex3f(12.5, -70, -10);
	glVertex3f(12.5, -70, 17.5);
	glVertex3f(12.5, -45, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg right plate bottom edge
    glNormal3f(0, -1, 0);
    glVertex3f(10, -70, -10);
	glVertex3f(10, -70, 17.5);
	glVertex3f(12.5, -70, 17.5);
	glVertex3f(12.5, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg right face
    glNormal3f(1, 0, 0);
    glVertex3f(12.5, -10, -10);
	glVertex3f(12.5, -10, 25);
	glVertex3f(12.5, -30, 25);
	glVertex3f(12.5, -42.5, 17.5);
	glVertex3f(12.5, -70, 17.5);
	glVertex3f(12.5, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 25);
	glVertex3f(-10, -30, 25);
	glVertex3f(-10, -42.5, 17.5);
	glVertex3f(-10, -70, 17.5);
	glVertex3f(-10, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg right place front edge
    glNormal3f(0, 0, 1);
    glVertex3f(10, -45, 17.5);
	glVertex3f(12.5, -45, 17.5);
	glVertex3f(12.5, -70, 17.5);
	glVertex3f(10, -70, 17.5);
  glEnd();

  glBegin(display_mode);				// lower leg right place back edge
    glNormal3f(0, 0, -1);
    glVertex3f(10, -45, -10);
	glVertex3f(12.5, -45, -10);
	glVertex3f(12.5, -70, -10);
	glVertex3f(10, -70, -10);
  glEnd();

  glBegin(display_mode);				// lower leg hip joint left plate left face
    glNormal3f(-1, 0, 0);
    glVertex3f(-12.5, 5, -10);
	glVertex3f(-12.5, 5, 10);
	glVertex3f(-12.5, -10, 17.5);
	glVertex3f(-12.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg hip joint left plate right face
	glNormal3f(1, 0, 0);
    glVertex3f(-7.5, 5, -10);
	glVertex3f(-7.5, 5, 10);
	glVertex3f(-7.5, -10, 17.5);
	glVertex3f(-7.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg hip joint right plate left face
    glNormal3f(-1, 0, 0);
    glVertex3f(7.5, 5, -10);
	glVertex3f(7.5, 5, 10);
	glVertex3f(7.5, -10, 17.5);
	glVertex3f(7.5, -10, -10);
  glEnd();

  glBegin(display_mode);				// lower leg hip joint right plate right face
    glNormal3f(1, 0, 0);
    glVertex3f(12.5, 5, -10);
	glVertex3f(12.5, 5, 10);
	glVertex3f(12.5, -10, 17.5);
	glVertex3f(12.5, -10, -10);
  glEnd();

}  // DrawLowerLeg


void Decepticon :: SetRightLowerLegLength(int new_value)
{
	right_lower_leg_length = new_value;
}  // SetRightLowerLegLength


void Decepticon :: SetRightLegDrop(int new_value)
{
	right_leg_drop = new_value;
}  // SetRightLegDrop


void Decepticon :: SetRightKneeAngle(int new_value)
{
	right_knee_angle = new_value;
}  // SetRightKneeAngle


void Decepticon :: BendRightKnee()
{
	if (right_knee_angle < 135)
	{
		right_knee_angle++;
		printf("Bending right knee.\n");
	}  // if statement
	else
		printf("Cannot bend right knee further.\n");
}  // BendRightKnee


void Decepticon :: StraightenRightKnee()
{
	if (right_knee_angle > 0)
	{
		right_knee_angle--;
		printf("Straightening right knee.\n");
	}  // if statement
	else
		printf("Cannot straighten right knee further.\n");
}  // StraightenRightKnee


void Decepticon :: SetLeftLowerLegLength(int new_value)
{
	left_lower_leg_length = new_value;
}  // SetLeftLowerLegLength


void Decepticon :: SetLeftLegDrop(int new_value)
{
	left_leg_drop = new_value;
}  // SetLeftLegDrop


void Decepticon :: SetLeftKneeAngle(int new_value)
{
	left_knee_angle = new_value;
}  // SetLeftKneeAngle


void Decepticon :: BendLeftKnee()
{
	if (left_knee_angle < 135)
	{
		left_knee_angle++;
		printf("Bending left knee.\n");
	}  // if statement
	else
		printf("Cannot bend left knee further.\n");
}  // BendLeftKnee


void Decepticon :: StraightenLeftKnee()
{
	if (left_knee_angle > 0)
	{
		left_knee_angle--;
		printf("Straightening left knee.\n");
	}  // if statement
	else
		printf("Cannot straighten left knee further.\n");
}  // StraightenLeftKnee
