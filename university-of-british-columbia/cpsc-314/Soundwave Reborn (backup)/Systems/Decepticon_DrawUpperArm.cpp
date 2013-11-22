#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawUpperArm()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	glBegin(display_mode);			// upper arm back face
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -8);
		glVertex3f(0, -40, -8);
		glVertex3f(7, -40, -8);
		glVertex3f(7, -30, -8);
		glVertex3f(11, -30, -8);
		glVertex3f(11, -40, -8);
		glVertex3f(18, -40, -8);
		glVertex3f(18, 0, -8);
	glEnd();

	glBegin(display_mode);			// upper arm front face
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 8);
		glVertex3f(0, -40, 8);
		glVertex3f(7, -40, 8);
		glVertex3f(7, -30, 8);
		glVertex3f(11, -30, 8);
		glVertex3f(11, -40, 8);
		glVertex3f(18, -40, 8);
		glVertex3f(18, 0, 8);
	glEnd();

	glBegin(display_mode);			// upper arm left face
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, -8);
		glVertex3f(0, -40, -8);
		glVertex3f(0, -40, 8);
		glVertex3f(0, 0, 8);
	glEnd();

	glBegin(display_mode);			// upper arm right face
		glNormal3f(1, 0, 0);
		glVertex3f(18, 0, -8);
		glVertex3f(18, -40, -8);
		glVertex3f(18, -40, 8);
		glVertex3f(18, 0, 8);
	glEnd();

	glBegin(display_mode);			// upper arm back raised face
		glNormal3f(0, 0, -1);
		glVertex3f(2, 0, -10);
		glVertex3f(2, -37, -10);
		glVertex3f(7, -37, -10);
		glVertex3f(7, -30, -10);
		glVertex3f(11, -30, -10);
		glVertex3f(11, -37, -10);
		glVertex3f(16, -37, -10);
		glVertex3f(16, 0, -10);
	glEnd();

	glBegin(display_mode);			// upper arm front raised face
		glNormal3f(0, 0, 1);
		glVertex3f(2, 0, 10);
		glVertex3f(2, -37, 10);
		glVertex3f(7, -37, 10);
		glVertex3f(7, -30, 10);
		glVertex3f(11, -30, 10);
		glVertex3f(11, -37, 10);
		glVertex3f(16, -37, 10);
		glVertex3f(16, 0, 10);
	glEnd();

	glBegin(display_mode);			// upper arm front left edge
		CalculateNormal(2, -37, 2, 0, -40, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(0, 0, 8);
		glVertex3f(0, -40, 8);
		glVertex3f(2, -37, 10);
		glVertex3f(2, 0, 10);
	glEnd();

	glBegin(display_mode);			// upper arm back left edge
		CalculateNormal(2, -37, -2, 0, -40, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(0, 0, -8);
		glVertex3f(0, -40, -8);
		glVertex3f(2, -37, -10);
		glVertex3f(2, 0, -10);
	glEnd();

	glBegin(display_mode);			// upper arm front right edge
		CalculateNormal(-2, -37, 2, 0, -40, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(18, 0, 8);
		glVertex3f(18, -40, 8);
		glVertex3f(16, -37, 10);
		glVertex3f(16, 0, 10);
	glEnd();

	glBegin(display_mode);			// upper arm back right edge
		CalculateNormal(-2, -37, 8, 0, -40, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(18, 0, -8);
		glVertex3f(18, -40, -8);
		glVertex3f(16, -37, -10);
		glVertex3f(16, 0, -10);
	glEnd();

	glBegin(display_mode);				// upper arm lower front left edge
		CalculateNormal(7, 3, 2, 2, 3, 2);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(0, -40, 8);
		glVertex3f(2, -37, 10);
		glVertex3f(7, -37, 10);
		glVertex3f(7, -40, 8);
	glEnd();

	glBegin(display_mode);				// upper arm lower front right edge
		CalculateNormal(-7, 3, 2, -2, 3, 2);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(18, -40, 8);
		glVertex3f(16, -37, 10);
		glVertex3f(11, -37, 10);
		glVertex3f(11, -40, 8);
	glEnd();

	glBegin(display_mode);				// upper arm lower back left edge
		CalculateNormal(7, 3, -2, 2, 3, -2);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(0, -40, -8);
		glVertex3f(2, -37, -10);
		glVertex3f(7, -37, -10);
		glVertex3f(7, -40, -8);
	glEnd();

	glBegin(display_mode);				// upper arm lower back right edge
		CalculateNormal(-7, 3, -2, -2, 3, -2);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(18, -40, -8);
		glVertex3f(16, -37, -10);
		glVertex3f(11, -37, -10);
		glVertex3f(11, -40, -8);
	glEnd();

	glBegin(display_mode);				// upper arm inside left edge
		glNormal3f(1, 0, 0);
		glVertex3f(7, -30, -10);
		glVertex3f(7, -37, -10);
		glVertex3f(7, -40, -8);
		glVertex3f(7, -40, 8);
		glVertex3f(7, -37, 10);
		glVertex3f(7, -30, 10);
	glEnd();

	glBegin(display_mode);				// upper arm inside right edge
		glNormal3f(1, 0, 0);
		glVertex3f(11, -30, -10);
		glVertex3f(11, -37, -10);
		glVertex3f(11, -40, -8);
		glVertex3f(11, -40, 8);
		glVertex3f(11, -37, 10);
		glVertex3f(11, -30, 10);
	glEnd();

	glBegin(display_mode);				// upper arm inside upper edge
		glNormal3f(0, -1, 0);
		glVertex3f(7, -30, -10);
		glVertex3f(7, -30, 10);
		glVertex3f(11, -30, 10);
		glVertex3f(11, -30, -10);
	glEnd();

	glBegin(display_mode);				// upper arm bottom edge
		glNormal3f(0, -1, 0);
		glVertex3f(0, -40, -8);
		glVertex3f(7, -40, -8);
		glVertex3f(7, -40, 8);
		glVertex3f(0, -40, 8);
	glEnd();

	glBegin(display_mode);				// same normal as last
		glVertex3f(11, -40, -8);
		glVertex3f(18, -40, -8);
		glVertex3f(18, -40, 8);
		glVertex3f(11, -40, 8);
	glEnd();
}  // DrawUpperArm
