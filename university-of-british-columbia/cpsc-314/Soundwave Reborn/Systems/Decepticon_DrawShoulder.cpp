/*
Author: Charles Bihis
Website: www.charlesbihis.com
Contact: admin@charlesbihis.com


Please read this Source Code License Agreement carefully before using
the source code.

You agree to indemnify, hold harmless and defend the author from and
against any loss, damage, claims or lawsuits, including attorney's
fees that arise or result from your use or distribution of the source
code.
	
THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT
ANY TECHNICAL SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. ALSO, THERE IS NO WARRANTY OF
NON-INFRINGEMENT, TITLE OR QUIET ENJOYMENT. IN NO EVENT SHALL THE AUTHOR
OR ITS SUPPLIERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include <stdio.h>
#include <gl\glut.h>
#include "Decepticon.h"


void Decepticon :: DrawShoulder()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	glTranslatef (0, -20, -15);
	ChangeColor(0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.8, 1.0);

	glBegin(display_mode);				// shoulder back
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -12.5);
		glVertex3f(0, 22.5, -12.5);
		glVertex3f(5, 27.5, -12.5);
		glVertex3f(20, 27.5, -12.5);
		glVertex3f(20, 10, -12.5);
		glVertex3f(7.5, 0, -12.5);
	glEnd();

	glBegin(display_mode);				// shoulder front
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 12.5);
		glVertex3f(0, 22.5, 12.5);
		glVertex3f(5, 27.5, 12.5);
		glVertex3f(20, 27.5, 12.5);
		glVertex3f(20, 10, 12.5);
		glVertex3f(7.5, 0, 12.5);
	glEnd();

	glBegin(display_mode);				// back inner shoulder edge
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, -12.5);
		glVertex3f(0, 22.5, -12.5);
		glVertex3f(0, 20, -10.5);
		glVertex3f(0, 0, -10.5);
	glEnd();

	glBegin(display_mode);				// front inner shoulder edge
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 12.5);
		glVertex3f(0, 22.5, 12.5);
		glVertex3f(0, 20, 10.5);
		glVertex3f(0, 0, 10.5);
	glEnd();

	glBegin(display_mode);				// top inner shoulder edge
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 22.5, -12.5);
		glVertex3f(0, 20, -10);
		glVertex3f(0, 20, 10);
		glVertex3f(0, 22.5, 12.5);
	glEnd();

	glBegin(display_mode);				// shoulder top left edge
		CalculateNormal(5, 5, 25, 5, 5, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(0, 22.5, -12.5);
		glVertex3f(5, 27.5, -12.5);
		glVertex3f(5, 27.5, 12.5);
		glVertex3f(0, 22.5, 12.5);
	glEnd();

	glBegin(display_mode);				// shoulder top edge
		glNormal3f(0, 1, 0);
		glVertex3f(5, 27.5, -12.5);
		glVertex3f(20, 27.5, -12.5);
		glVertex3f(20, 27.5, 12.5);
		glVertex3f(5, 27.5, 12.5);
	glEnd();

	glBegin(display_mode);				// shoulder right edge
		glNormal3f(1, 0, 0);
		glVertex3f(20, 27.5, -12.5);
		glVertex3f(20, 10, -12.5);
		glVertex3f(20, 10, 12.5);
		glVertex3f(20, 27.5, 12.5);
	glEnd();

	glBegin(display_mode);
		CalculateNormal(-1.95, -1.66, 25, -1.95, -1.66, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(20, 10, -12.5);
		glVertex3f(18.05, 8.34, -12.5);		// 18.05 = 10 - (2.5 * 12.5) / sqrt(256.25)
		glVertex3f(18.05, 8.34, 12.5);		// 8.34 = 10 - (2.5 *10) / sqrt(256.25)
		glVertex3f(20, 10, 12.5);
	glEnd();

	glBegin(display_mode);
		CalculateNormal(12.5, 10, 2.5, 12.5, 10, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(7.5, 0, -12.5);
		glVertex3f(20, 10, -12.5);
		glVertex3f(20, 10, -10.5);
		glVertex3f(7.5, 0, -10.5);
	glEnd();

	glBegin(display_mode);				// same normal as last calculation
		glVertex3f(7.5, 0, 12.5);
		glVertex3f(20, 10, 12.5);
		glVertex3f(20, 10, 10.5);
		glVertex3f(7.5, 0, 10.5);
	glEnd();

	glBegin(display_mode);
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, -12.5);
		glVertex3f(7.5, 0, -12.5);
		glVertex3f(7.5, 0, -10);
		glVertex3f(0, 0, -10);
	glEnd();

	glBegin(display_mode);				// same normal as last calculation
		glVertex3f(0, 0, 12.5);
		glVertex3f(7.5, 0, 12.5);
		glVertex3f(7.5, 0, 10);
		glVertex3f(0, 0, 10);
	glEnd();

	glBegin(display_mode);				// shoulder plate back face
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 12.5);
		glVertex3f(0, 22.5, 12.5);
		glVertex3f(15, 22.5, 12.5);
		glVertex3f(15, 6, 12.5);
		glVertex3f(7.5, 0, 12.5);
	glEnd();

	glBegin(display_mode);				// shoulder plate front face
		glVertex3f(0, 0, 15);				// same normal as last calculation
		glVertex3f(0, 22.5, 15);
		glVertex3f(15, 22.5, 15);
		glVertex3f(15, 6, 15);
		glVertex3f(7.5, 0, 15);
	glEnd();

	glBegin(display_mode);				// shoulder plate left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(0, 0, 12.5);
		glVertex3f(0, 22.5, 12.5);
		glVertex3f(0, 22.5, 15);
		glVertex3f(0, 0, 15);
	glEnd();

	glBegin(display_mode);				// shoulder plate top edge
		glNormal3f(0, 1, 0);
		glVertex3f(0, 22.5, 12.5);
		glVertex3f(15, 22.5, 12.5);
		glVertex3f(15, 22.5, 15);
		glVertex3f(0, 22.5, 15);
	glEnd();

	glBegin(display_mode);				// shoulder plate right edge
		glNormal3f(1, 0, 0);
		glVertex3f(15, 22.5, 12.5);
		glVertex3f(15, 6, 12.5);
		glVertex3f(15, 6, 15);
		glVertex3f(15, 22.5, 15);
	glEnd();

	glBegin(display_mode);				// shoulder plate bottom right edge
		CalculateNormal(-7.5, -6, 2.5, -7.5, -6, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(15, 6, 12.5);
		glVertex3f(7.5, 0, 12.5);
		glVertex3f(7.5, 0, 15);
		glVertex3f(15, 6, 15);
	glEnd();

	glBegin(display_mode);				// shoulder plate bottom edge
		glNormal3f(0, -1, 0);
		glVertex3f(0, 0, 12.5);
		glVertex3f(7.5, 0, 12.5);
		glVertex3f(7.5, 0, 15);
		glVertex3f(0, 0, 15);
	glEnd();
}  // DrawShoulder


void Decepticon :: SetRightShoulderBack(int new_value)
{
	right_shoulder_back = new_value;
}  // SetRightShoulderBack


void Decepticon :: SetRightShoulderRotate(int new_value)
{
	right_shoulder_rotate = new_value;
}  // SetRightShoulderRotate


void Decepticon :: SetRightShoulderForwardAngle(int new_value)
{
	right_shoulder_forward_angle = new_value;
}  // GetRightShoulderForwardAngle


void Decepticon :: RotateRightShoulderForward()
{
	right_shoulder_forward_angle = (right_shoulder_forward_angle - 1) % 360;
	printf("Rotating right shoulder forwards.\n");
}  // RotateRightShoulderForward


void Decepticon :: RotateRightShoulderBackward()
{
	right_shoulder_forward_angle = (right_shoulder_forward_angle + 1) % 360;
	printf("Rotating right shoulder backwards.\n");
}  // RotateRightShoulderBackard


void Decepticon :: SetRightShoulderOutwardAngle(int new_value)
{
	right_shoulder_outward_angle = new_value;
}  // GetRightShoulderOutwardAngle


void Decepticon :: RaiseRightShoulder()
{
	if (right_shoulder_outward_angle < 90)
	{
		right_shoulder_outward_angle++;
		printf("Raising right shoulder.\n");
	}  // if statement
	else
	{
		printf("Cannot raise right shoulder further.\n");
	}  // else statement
}  // RaiseRightShoulder


void Decepticon :: LowerRightShoulder()
{
	if (right_shoulder_outward_angle == 45 && right_shoulder_twist_angle != 0)
		printf("Cannot lower twisted right shoulder further...straighten first.\n");
	else if (right_shoulder_outward_angle >= 0)
	{
		right_shoulder_outward_angle--;
		printf("Lowering right shoulder.\n");
	}  // else if statement
	else
	{
		printf("Cannot lower right shoulder further.\n");
	}  // else statement
}  // LowerRightShoulder


void Decepticon :: SetRightShoulderTwistAngle(int new_value)
{
	right_shoulder_twist_angle = new_value;
}  // GetRightShoulderTwistAngle


void Decepticon :: TwistRightShoulderOutward()
{
	if (right_shoulder_outward_angle >= 45)
	{
		right_shoulder_twist_angle = (right_shoulder_twist_angle + 1) % 360;
		printf("Twisting right shoulder outwards.\n");
	}  // if statement
	else
	{
		printf ("Cannot twist right shoulder further.\n");
	}  // else statement
}  // TwistRightShoulderOutward


void Decepticon :: TwistRightShoulderInward()
{
	if (right_shoulder_outward_angle >= 45)
	{
		right_shoulder_twist_angle = (right_shoulder_twist_angle - 1) % 360;
		printf("Twisting right shoulder inwards.\n");
	}  // if statement
	else
	{
		printf ("Cannot twist right shoulder further.\n");
	}  // else statement
}  // TwistRightShoulderInward


void Decepticon :: SetLeftShoulderBack(int new_value)
{
	left_shoulder_back = new_value;
}  // SetLeftShoulderBack


void Decepticon :: SetLeftShoulderRotate(int new_value)
{
	left_shoulder_rotate = new_value;
}  // SetLeftShoulderRotate


void Decepticon :: SetLeftShoulderForwardAngle(int new_value)
{
	left_shoulder_forward_angle = new_value;
}  // GetLeftShoulderForwardAngle


void Decepticon :: RotateLeftShoulderForward()
{
	left_shoulder_forward_angle = (left_shoulder_forward_angle + 1) % 360;
	printf("Rotating left shoulder forwards.\n");
}  // RotateLeftShoulderForward


void Decepticon :: RotateLeftShoulderBackward()
{
	left_shoulder_forward_angle = (left_shoulder_forward_angle - 1) % 360;
	printf("Rotating left shoulder backwards.\n");
}  // RotateLeftShoulderBackard


void Decepticon :: SetLeftShoulderOutwardAngle(int new_value)
{
	left_shoulder_outward_angle = new_value;
}  // GetLeftShoulderOutwardAngle


void Decepticon :: RaiseLeftShoulder()
{
	if (left_shoulder_outward_angle < 90)
	{
		left_shoulder_outward_angle++;
		printf("Raising left shoulder.\n");
	}  // if statement
	else
	{
		printf("Cannot raise right shoulder further.\n");
	}  // else statement
}  // RaiseLeftShoulder


void Decepticon :: LowerLeftShoulder()
{
	if (left_shoulder_outward_angle <= 45 && left_shoulder_twist_angle != 0)
		printf("Cannot lower twisted left shoulder further...straighten first.\n");
	else if (left_shoulder_outward_angle >= 0)
	{
		left_shoulder_outward_angle--;
		printf("Lowering left shoulder.\n");
	}  // else if statement
	else
	{
		printf("Cannot lower left shoulder further.\n");
	}  // else statement
}  // LowerLeftShoulder


void Decepticon :: SetLeftShoulderTwistAngle(int new_value)
{
	left_shoulder_twist_angle = new_value;
}  // GetLeftShoulderTwistAngle


void Decepticon :: TwistLeftShoulderOutward()
{
	if (left_shoulder_outward_angle >= 45)
	{
		left_shoulder_twist_angle = (left_shoulder_twist_angle + 1) % 360;
		printf("Twisting left shoulder outwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist left shoulder further.\n");
	}  // else statement
}  // TwistLeftShoulderOutward


void Decepticon :: TwistLeftShoulderInward()
{
	if (left_shoulder_outward_angle >= 45)
	{
		left_shoulder_twist_angle = (left_shoulder_twist_angle - 1) % 360;
		printf("Twisting left shoulder inwards.\n");
	}  // if statement
	else
	{
		printf("Cannot twist left shoulder further.\n");
	}  // else statement
}  // TwistLeftShoulderInward
