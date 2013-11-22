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


void Decepticon :: DrawLowerArm()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	glTranslatef(0, -4, 0);
	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);				// upper arm joint bottom edge
		glNormal3f(0, 1, 0);
		glVertex3f(-1.5, 0, -5);
		glVertex3f(-1.5, 0, 5);
		glVertex3f(1.5, 0, 5);
		glVertex3f(1.5, 0, -5);
	glEnd();

	glBegin(display_mode);				// upper arm joint top edge
		glNormal3f(0, -1, 0);
		glVertex3f(-1.5, 12, -5);
		glVertex3f(-1.5, 12, 5);
		glVertex3f(1.5, 12, 5);
		glVertex3f(1.5, 12, -5);
	glEnd();

	glBegin(display_mode);				// upper arm joint front edge
		glNormal3f(0, 0, 1);
		glVertex3f(-1.5, 0, 5);
		glVertex3f(-1.5, 12, 5);
		glVertex3f(1.5, 12, 5);
		glVertex3f(1.5, 0, 5);
	glEnd();

	glBegin(display_mode);				// upper arm joint back edge
		glNormal3f(0, 0, -1);
		glVertex3f(-1.5, 0, -5);
		glVertex3f(-1.5, 12, -5);
		glVertex3f(1.5, 12, -5);
		glVertex3f(1.5, 0, -5);
	glEnd();

	glBegin(display_mode);				// upper arm joint left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(-1.5, 0, -5);
		glVertex3f(-1.5, 12, -5);
		glVertex3f(-1.5, 12, 5);
		glVertex3f(-1.5, 0, 5);
	glEnd();

	glBegin(display_mode);				// upper arm joint right edge
		glNormal3f(1, 0, 0);
		glVertex3f(1.5, 0, -5);
		glVertex3f(1.5, 12, -5);
		glVertex3f(1.5, 12, 5);
		glVertex3f(1.5, 0, 5);
	glEnd();

	glBegin(display_mode);				// upper arm raised upper face
		glNormal3f(0, 1, 0);
		glVertex3f(-10, 0, -10);
		glVertex3f(10, 0, -10);
		glVertex3f(10, 0, 10);
		glVertex3f(-10, 0, 10);
	glEnd();

	glBegin(display_mode);				// upper arm upper face
		glVertex3f(-15, -5, -15);			// same normal as last
		glVertex3f(15, -5, -15);
		glVertex3f(15, -5, 15);
		glVertex3f(-15, -5, 15);
	glEnd();

	glBegin(display_mode);				// upper arm raised lower face
		glNormal3f(0, -1, 0);
		glVertex3f(-7.5, -40, -7.5);
		glVertex3f(7.5, -40, -7.5);
		glVertex3f(7.5, -40, 7.5);
		glVertex3f(-7.5, -40, 7.5);
	glEnd();

	glBegin(display_mode);				// upper arm lower face
		glVertex3f(-15, -32.5, -15);		// same normal as last
		glVertex3f(15, -32.5, -15);
		glVertex3f(15, -32.5, 15);
		glVertex3f(-15, -32.5, 15);
	glEnd();

	glBegin(display_mode);				// upper arm top back edge
		CalculateNormal(20, 0, 0, 25, -5, -5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-10, 0, -10);
		glVertex3f(10, 0, -10);
		glVertex3f(15, -5, -15);
		glVertex3f(-15, -5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm top front edge
		CalculateNormal(25, -5, 5, 20, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-10, 0, 10);
		glVertex3f(10, 0, 10);
		glVertex3f(15, -5, 15);
		glVertex3f(-15, -5, 15);
	glEnd();

	glBegin(display_mode);				// upper arm top left edge
		CalculateNormal(-5, -5, 25, 0, 0, 20);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-10, 0, -10);
		glVertex3f(-10, 0, 10);
		glVertex3f(-15, -5, 15);
		glVertex3f(-15, -5, -15);
	glEnd();

	ChangeColor(1.0, 0.0, 0.0, 1.0, 0.8, 0.0, 0.0, 1.0);

	glBegin(display_mode);				// upper arm left face red stripe
		glNormal3f(-1, 0, 0);
		glVertex3f(-15.1, -25, -15.1);
		glVertex3f(-15.1, -25, 15.1);
		glVertex3f(-15.1, -32.5, 15.1);
		glVertex3f(-15.1, -32.5, -15.1);
	glEnd();

	glBegin(display_mode);				// upper arm right face red stripe
		glNormal3f(1, 0, 0);
		glVertex3f(15.1, -25, -15.1);
		glVertex3f(15.1, -25, 15.1);
		glVertex3f(15.1, -32.5, 15.1);
		glVertex3f(15.1, -32.5, -15.1);
	glEnd();

	glBegin(display_mode);				// upper arm back face red stripe
		glNormal3f(0, 0, -1);
		glVertex3f(-15.1, -25, -15.1);
		glVertex3f(15.1, -25, -15.1);
		glVertex3f(15.1, -32.5, -15.1);
		glVertex3f(-15.1, -32.5, -15.1);
	glEnd();

	glBegin(display_mode);				// upper arm front face red stripe
		glNormal3f(0, 0, 1);
		glVertex3f(-15.1, -25, 15.1);
		glVertex3f(15.1, -25, 15.1);
		glVertex3f(15.1, -32.5, 15.1);
		glVertex3f(-15.1, -32.5, 15.1);
	glEnd();

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);				// upper arm top right edge
		CalculateNormal(5, -5, 25, 0, 0, 20);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(10, 0, -10);
		glVertex3f(10, 0, 10);
		glVertex3f(15, -5, 15);
		glVertex3f(15, -5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm bottom left edge
		CalculateNormal(7.5, -7.5, 22.5, 0, 0, 30);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-15, -32.5, -15);
		glVertex3f(-15, -32.5, 15);
		glVertex3f(-7.5, -40, 7.5);
		glVertex3f(-7.5, -40, -7.5);
	glEnd();

	glBegin(display_mode);				// upper arm bottom right edge
		CalculateNormal(0, 0, 30, -7.5, -7.5, 7.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(15, -32.5, -15);
		glVertex3f(15, -32.5, 15);
		glVertex3f(7.5, -40, 7.5);
		glVertex3f(7.5, -40, -7.5);
	glEnd();

	glBegin(display_mode);				// upper arm bottom back edge
		CalculateNormal(30, 0, 0, 22.5, -7.5, 7.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-15, -32.5, -15);
		glVertex3f(15, -32.5, -15);
		glVertex3f(7.5, -40, -7.5);
		glVertex3f(-7.5, -40, -7.5);
	glEnd();

	glBegin(display_mode);				// upper arm bottom front edge
		CalculateNormal(22.5, -7.5, -7.5, 30, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-15, -32.5, 15);
		glVertex3f(15, -32.5, 15);
		glVertex3f(7.5, -40, 7.5);
		glVertex3f(-7.5, -40, 7.5);
	glEnd();

	//ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);				// upper arm left face
		glNormal3f(-1, 0, 0);
		glVertex3f(-15, -5, -15);
		glVertex3f(-15, -5, 15);
		glVertex3f(-15, -32.5, 15);
		glVertex3f(-15, -32.5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm right face
		glNormal3f(1, 0, 0);
		glVertex3f(15, -5, -15);
		glVertex3f(15, -5, 15);
		glVertex3f(15, -32.5, 15);
		glVertex3f(15, -32.5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm back face
		glNormal3f(0, 0, -1);
		glVertex3f(-15, -5, -15);
		glVertex3f(15, -5, -15);
		glVertex3f(15, -32.5, -15);
		glVertex3f(-15, -32.5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm front face
		glNormal3f(0, 0, 1);
		glVertex3f(-15, -5, 15);
		glVertex3f(15, -5, 15);
		glVertex3f(15, -32.5, 15);
		glVertex3f(-15, -32.5, 15);
	glEnd();

	glBegin(display_mode);				// upper arm wing inner face
		CalculateNormal(3, 40, -5, 3, 40, -25);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(9, -5, 15);
		glVertex3f(12, 35, 10);
		glVertex3f(12, 35, -10);
		glVertex3f(9, -5, -15);
	glEnd();

	glBegin(display_mode);				// upper arm wing outer face
		CalculateNormal(0, 0, -30, -1, 40, -25);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(15, -5, 15);
		glVertex3f(15, -5, -15);
		glVertex3f(14, 35, -10);
		glVertex3f(14, 35, 10);
	glEnd();

	glBegin(display_mode);				// upper arm wing front edge
		CalculateNormal(6, 0, 0, 5, 40, -5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(9, -5, 15);
		glVertex3f(15, -5, 15);
		glVertex3f(14, 35, 10);
		glVertex3f(12, 35, 10);
	glEnd();

	glBegin(display_mode);				// upper arm wing back edge
		CalculateNormal(5, 40, -25, 6, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(9, -5, -15);
		glVertex3f(15, -5, -15);
		glVertex3f(14, 35, -10);
		glVertex3f(12, 35, -10);
	glEnd();

	glBegin(display_mode);				// upper arm wing top edge
		CalculateNormal(2, 0, 20, 2, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(12, 35, -10);
		glVertex3f(14, 35, -10);
		glVertex3f(14, 35, 10);
		glVertex3f(12, 35, 10);
	glEnd();
}  // DrawLowerArm


void Decepticon :: SetRightElbowForwardAngle(int new_value)
{
	right_elbow_forward_angle = new_value;
}  // GetRightElbowForwardAngle


void Decepticon :: RaiseRightHand()
{
	if (right_elbow_forward_angle > -95)
	{
		right_elbow_forward_angle--;
		printf("Raising right hand.\n");
	}  // if statement
	else
	{
		printf("Cannot raise right hand further.\n");
	}  // else statement
}  // RaiseRightHand


void Decepticon :: LowerRightHand()
{
	if (right_elbow_forward_angle < 0)
	{
		right_elbow_forward_angle++;
		printf("Lowering right hand.\n");
	}  // if statement
	else
	{
		printf("Cannot lower right hand forward.\n");
	}  // else statement
}  // LowerRightHand


void Decepticon :: SetRightLowerArmRetract(int new_value)
{
	right_lower_arm_retract = new_value;
}  // SetRightLowerArmRetract


void Decepticon :: SetLeftElbowForwardAngle(int new_value)
{
	left_elbow_forward_angle = new_value;
}  // GetLeftElbowTwistAngle


void Decepticon :: RaiseLeftHand()
{
	if (left_elbow_forward_angle < 95)
	{
		left_elbow_forward_angle++;
		printf("Raising left hand.\n");
	}  // if statement
	else
	{
		printf("Cannot raise left hand further.\n");
	}  // else statement
}  // RaiseLeftHand


void Decepticon :: LowerLeftHand()
{
	if (left_elbow_forward_angle < 0)
	{
		left_elbow_forward_angle--;
		printf("Lowering right hand.\n");
	}  // if statement
	else
	{
		printf("Cannot lower left hand further.\n");
	}  // else statement
}  // LowerLeftHand


void Decepticon :: SetLeftLowerArmRetract(int new_value)
{
	left_lower_arm_retract = new_value;
}  // SetLeftLowerArmRetract
