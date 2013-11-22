#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawUpperLeg()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	glScalef(1.08, 1.08, 1.08);
	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// upper leg back face
		glNormal3f(0, 0, -1);
		glVertex3f(-10, 15, -10);
		glVertex3f(-10, -55, -10);
		glVertex3f(10, -55, -10);
		glVertex3f(10, 15, -10);
	glEnd();

	glBegin(display_mode);			// upper leg front left face
		glNormal3f(0, 0, 1);
		glVertex3f(-10, 15, 10);
		glVertex3f(-10, -42.5, 10);
		glVertex3f(-2.5, -25, 10);
		glVertex3f(-2.5, 15, 10);
	glEnd();

	glBegin(display_mode);			// upper leg front right face
		glNormal3f(0, 0, 1);
		glVertex3f(10, 15, 10);
		glVertex3f(10, -42.5, 10);
		glVertex3f(2.5, -25, 10);
		glVertex3f(2.5, 15, 10);
	glEnd();

	glBegin(display_mode);			// upper leg front middle face
		glNormal3f(0, 0, 1);
		glVertex3f(-2.5, -25, 10);
		glVertex3f(-10, -42.5, 10);
		glVertex3f(10, -42.5, 10);
		glVertex3f(2.5, -25, 10);
	glEnd();

	glBegin(display_mode);			// upper leg left face
		glNormal3f(-1, 0, 0);
		glVertex3f(-10, 15, 10);
		glVertex3f(-10, 15, -10);
		glVertex3f(-10, -55, -10);
		glVertex3f(-10, -42.5, 10);
	glEnd();

	glBegin(display_mode);			// upper leg right face
		glNormal3f(1, 0, 0);
		glVertex3f(10, 15, 10);
		glVertex3f(10, 15, -10);
		glVertex3f(10, -55, -10);
		glVertex3f(10, -42.5, 10);
	glEnd();

	glBegin(display_mode);			// upper leg bottom left edge
		CalculateNormal(2.5, -12.5, -20, 2.5, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-10, -42.5, 10);
		glVertex3f(-7.5, -42.5, 10);
		glVertex3f(-7.5, -55, -10);
		glVertex3f(-10, -55, -10);
	glEnd();

	glBegin(display_mode);			// upper leg bottom right edge
		CalculateNormal(-2.5, 0, 0, -2.5, -12.5, -20);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(10, -42.5, 10);
		glVertex3f(7.5, -42.5, 10);
		glVertex3f(7.5, -55, -10);
		glVertex3f(10, -55, -10);
	glEnd();

	glBegin(display_mode);			// upper leg hip-joint left edge
		glNormal3f(1, 0, 0);
		glVertex3f(-2.5, 15, 10);
		glVertex3f(-2.5, -25, 10);
		glVertex3f(-2.5, -22.5, 7.5);
		glVertex3f(-2.5, 15, 7.5);
	glEnd();

	glBegin(display_mode);			// upper leg hip-joint right edge
		glNormal3f(-1, 0, 0);
		glVertex3f(2.5, 15, 10);
		glVertex3f(2.5, -25, 10);
		glVertex3f(2.5, -22.5, 7.5);
		glVertex3f(2.5, 15, 7.5);
	glEnd();

	glBegin(display_mode);			// upper leg hip-joint bottom edge
		CalculateNormal(5, 2.5, 0, 5, 2.5, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-2.5, -25, 10);
		glVertex3f(2.5, -25, 10);
		glVertex3f(2.5, -22.5, 7.5);
		glVertex3f(-2.5, -22.5, 7.5);
	glEnd();

	glBegin(display_mode);			// kneecap top front plate
		CalculateNormal(15, -7.5, 5, 15, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-7.5, -42.5, 10);
		glVertex3f(7.5, -42.5, 10);
		glVertex3f(7.5, -50, 15);
		glVertex3f(-7.5, -50, 15);
	glEnd();

	glBegin(display_mode);			// kneecap bottom front plate
		CalculateNormal(15, -25, -5, 15, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-7.5, -50, 15);
		glVertex3f(7.5, -50, 15);
		glVertex3f(7.5, -67.5, 10);
		glVertex3f(-7.5, -67.5, 10);
	glEnd();

	glBegin(display_mode);			// kneecap back plate
		glNormal3f(0, 0, -1);
		glVertex3f(-7.5, -55, -10);
		glVertex3f(7.5, -55, -10);
		glVertex3f(7.5, -67.5, -10);
		glVertex3f(-7.5, -67.5, -10);
	glEnd();

	glBegin(display_mode);			// kneecap left face
		glNormal3f(-1, 0, 0);
		glVertex3f(-7.5, -42.5, 10);
		glVertex3f(-7.5, -55, -10);
		glVertex3f(-7.5, -67.5, -10);
		glVertex3f(-7.5, -67.5, 10);
		glVertex3f(-7.5, -50, 15);
	glEnd();

	glBegin(display_mode);			// kneecap right face
		glNormal3f(1, 0, 0);
		glVertex3f(7.5, -42.5, 10);
		glVertex3f(7.5, -55, -10);
		glVertex3f(7.5, -67.5, -10);
		glVertex3f(7.5, -67.5, 10);
		glVertex3f(7.5, -50, 15);
	glEnd();

	glBegin(display_mode);			// kneecap bottom face
		glNormal3f(0, -1, 0);
		glVertex3f(-7.5, -67.5, 10);
		glVertex3f(-7.5, -67.5, -10);
		glVertex3f(7.5, -67.5, -10);
		glVertex3f(7.5, -67.5, 10);
	glEnd();
}  // DrawUpperLeg


void Decepticon :: SetRightUpperLegLength(int new_value)
{
	right_upper_leg_length = new_value;
}  // SetRightUpperLegLength


void Decepticon :: SetRightLegForwardAngle(int new_value)
{
	right_leg_forward_angle = new_value;
}  // SetRightLegForwardAngle


void Decepticon :: RaiseRightLeg()
{
	if (right_leg_forward_angle < 90)
	{
		right_leg_forward_angle++;
		printf("Rotate right leg forward.\n");
	}  // if statement
	else
	{
		printf("Cannot rotate leg further forward.\n");
	}  // else statement
}  // RaiseRightLeg


void Decepticon :: LowerRightLeg()
{
	if (right_leg_forward_angle > -60)
	{
		right_leg_forward_angle--;
		printf("Lowering right leg.\n");
	}  // if statement
	else
	{
		printf("Cannot lower leg further.\n");
	}  // else statement
}  // LowerRightLeg


void Decepticon :: SetRightLegOutwardAngle(int new_value)
{
	right_leg_outward_angle = new_value;
}  // SetRightLegOutwardAngle


void Decepticon :: RaiseRightLegOutward()
{
	if (right_leg_outward_angle < 80)
	{
		right_leg_outward_angle++;
		printf("Raising right leg outwards.\n");
	}  // if statement
	else
	{
		printf("Cannot raise leg further.\n");
	}  // else statement
}  // RaiseRightLegOutward


void Decepticon :: LowerRightLegInward()
{
	if (right_leg_outward_angle > -3)
	{
		right_leg_outward_angle--;
		printf("Lowering Right leg.\n");
	}  // if statement
	else
	{
		printf("Cannot lower leg further.\n");
	}  // else statement
}  // LowerRightLegInward


void Decepticon :: SetRightLegTwistAngle(int new_value)
{
	right_leg_twist_angle = new_value;
}  // SetRightLegTwistAngle


void Decepticon :: TwistRightLegOutward()
{
	if (right_leg_twist_angle < 90)
	{
		right_leg_twist_angle++;
		printf("Twisting right leg outwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist right leg further.\n");
	}  // else statement
}  // TwistRightLegOutward


void Decepticon :: TwistRightLegInward()
{
	if (right_leg_twist_angle > 0)
	{
		right_leg_twist_angle--;
		printf("Twisting right leg inwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist right leg further.\n");
	}  // else statement
}  // TwistRightLegInward


void Decepticon :: SetLeftUpperLegLength(int new_value)
{
	left_upper_leg_length = new_value;
}  // SetLeftUpperLegLength


void Decepticon :: SetLeftLegForwardAngle(int new_value)
{
	left_leg_forward_angle = new_value;
}  // SetLeftLegForwardAngle


void Decepticon	:: RaiseLeftLeg()
{
	if (left_leg_forward_angle < 90)
	{
		left_leg_forward_angle++;
		printf("Rotating left leg forward.\n");
	}  // if statement
	else
	{
		printf("Cannot raise leg further forward.\n");
	}  // else statement
}  // RaiseLeftLeg


void Decepticon :: LowerLeftLeg()
{
	if (left_leg_forward_angle > -60)
	{
		left_leg_forward_angle--;
		printf("Lowering left leg.\n");
	}  // if statement
	else
	{
		printf("Cannot lower leg further.\n");
	}  // else statement
}  // LowerLeftLeg


void Decepticon :: SetLeftLegOutwardAngle(int new_value)
{
	left_leg_outward_angle = new_value;
}  // SetLeftLegOutwardAngle


void Decepticon :: RaiseLeftLegOutward()
{
	if (left_leg_outward_angle < 80)
	{
		left_leg_outward_angle++;
		printf("Raising left leg outwards.\n");
	}  // if statement
	else
	{
		printf("Cannot raise leg further.\n");
	}  // else statement
}  // RaiseLeftLegOutward


void Decepticon :: LowerLeftLegInward()
{
	if (left_leg_outward_angle > -3)
	{
		left_leg_outward_angle--;
		printf("Lowering left leg.\n");
	}  // if statement
	else
	{
		printf("Cannot lower leg further.\n");
	}  // else statement
}  // LowerLeftLegInward


void Decepticon :: SetLeftLegTwistAngle(int new_value)
{
	left_leg_twist_angle = new_value;
}  // SetLeftLegTwistAngle


void Decepticon :: TwistLeftLegOutward()
{
	if (left_leg_twist_angle < 90)
	{
		left_leg_twist_angle++;
		printf("Twisting left leg outwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist left leg further.\n");
	}  // else statement
}  // TwistLeftLegOutward


void Decepticon :: TwistLeftLegInward()
{
	if (left_leg_twist_angle > 0)
	{
		left_leg_twist_angle--;
		printf("Twisting left leg inwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist left leg further.\n");
	}  // else statement
}  // TwistLeftLegInward
