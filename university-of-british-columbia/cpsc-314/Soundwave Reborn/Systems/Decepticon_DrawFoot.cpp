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
	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

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
	{
		printf("Cannot raise right foot further.\n");
	}  // else statement
}  // RaiseRightFoot


void Decepticon :: LowerRightFoot()
{
	if (right_foot_angle > -45)
	{
		right_foot_angle--;
		printf("Lowering right foot.\n");
	}  // if statement
	else
	{
		printf("Cannot lower right foot further.\n");
	}  // else statement
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
