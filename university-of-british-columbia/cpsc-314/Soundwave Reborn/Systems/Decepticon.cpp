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
#include <math.h>
#include "Decepticon.h"


namespace
{
	Decepticon* decepticon_instance = NULL;
}


Decepticon* Decepticon :: SystemInstance()
{
  if (decepticon_instance == NULL)			// check if it is the first call
    decepticon_instance = new Decepticon();	// create single instance

  return decepticon_instance;				// address of single instance
}  // SystemInstance

// ********************************************************************** //
// ****************************** Mutators ****************************** //
// ********************************************************************** //
Decepticon :: Decepticon()
{
	transform_position = 0;
	anti_aliasing = false;
	transformed = false;
	transforming = false;
	display_mode = GL_POLYGON;
	window_angle = 0;
	bend_angle = -5;
	hips_angle = 0;
	torso_length = 0;
	right_shoulder_back = 0;
	right_shoulder_rotate = 0;
	right_shoulder_forward_angle = 0;
	right_shoulder_outward_angle = 0;
	right_shoulder_twist_angle = 0;
	right_elbow_forward_angle = 0;
	right_lower_arm_retract = 0;
	right_leg_drop = 0;
	right_leg_forward_angle = 0;
	right_leg_outward_angle = 5;
	right_leg_twist_angle = 15;
	right_upper_leg_length = 0;
	right_lower_leg_length = 0;
	right_knee_angle = 0;
	right_foot_angle = -6;
	right_foot_retract = 0;
	left_shoulder_back = 0;
	left_shoulder_rotate = 0;
	left_shoulder_forward_angle = 0;
	left_shoulder_outward_angle = 0;
	left_shoulder_twist_angle = 0;
	left_elbow_forward_angle = 0;
	left_lower_arm_retract = 0;
	left_leg_drop = 0;
	left_leg_forward_angle = 0;
	left_leg_outward_angle = 5;
	left_leg_twist_angle = 15;
	left_upper_leg_length = 0;
	left_lower_leg_length = 0;
	left_knee_angle = 0;
	left_foot_angle = -6;
	left_foot_retract = 0;
}  // Decepticon


Decepticon :: Decepticon(int boombox_form)
{
	transform_position = -139.5;
	anti_aliasing = false;
	transformed = false;
	transforming = false;
	display_mode = GL_POLYGON;
	window_angle = 0;
	bend_angle = -5;
	hips_angle = 0;
	torso_length = MAX_TORSO_LENGTH;
	right_shoulder_back = MAX_SHOULDERS_BACK;
	right_shoulder_rotate = MAX_SHOULDERS_ROTATE;
	right_shoulder_forward_angle = 0;
	right_shoulder_outward_angle = 0;
	right_shoulder_twist_angle = 0;
	right_elbow_forward_angle = 0;
	right_lower_arm_retract = MAX_LOWER_ARM_RETRACT;
	right_leg_drop = MAX_LEG_DROP;
	right_leg_forward_angle = MAX_LEG_FORWARD_ANGLE;
	right_leg_outward_angle = 5;
	right_leg_twist_angle = MAX_LEG_TWIST_ANGLE;
	right_upper_leg_length = MAX_UPPER_LEG_LENGTH;
	right_lower_leg_length = MAX_LOWER_LEG_LENGTH;
	right_knee_angle = MAX_KNEE_ANGLE;
	right_foot_angle = -6;
	right_foot_retract = MAX_FOOT_RETRACT;
	left_shoulder_back = MAX_SHOULDERS_BACK;
	left_shoulder_rotate = MAX_SHOULDERS_ROTATE;
	left_shoulder_forward_angle = 0;
	left_shoulder_outward_angle = 0;
	left_shoulder_twist_angle = 0;
	left_elbow_forward_angle = 0;
	left_lower_arm_retract = MAX_LOWER_ARM_RETRACT;
	left_leg_drop = MAX_LEG_DROP;
	left_leg_forward_angle = MAX_LEG_FORWARD_ANGLE;
	left_leg_outward_angle = 5;
	left_leg_twist_angle = MAX_LEG_TWIST_ANGLE;
	left_upper_leg_length = MAX_UPPER_LEG_LENGTH;
	left_lower_leg_length = MAX_LOWER_LEG_LENGTH;
	left_knee_angle = MAX_KNEE_ANGLE;
	left_foot_angle = -6;
	left_foot_retract = MAX_FOOT_RETRACT;
}  // Decepticon



void Decepticon :: ToggleDisplayMode()
{
	if (display_mode == GL_LINE_LOOP)
	{
		display_mode = GL_POLYGON;
		printf("Displaying solid.\n");
	}  // if statement
	else
	{
		display_mode = GL_LINE_LOOP;
		printf("Displaying wire frame.\n");
	}  // else statement
}  // SetDisplayMode


void Decepticon :: ToggleAntiAliasing()
{
	anti_aliasing = !anti_aliasing;

	if (anti_aliasing)
		printf("Anti-aliasing ON.\n");
	else
		printf("Anti-aliasing OFF.\n");
}  // SetAntiAliasing


void Decepticon :: Reset()
{
	transform_position = 0;
	window_angle = 0;
	bend_angle = -5;
	hips_angle = 0;
	torso_length = 0;
	right_shoulder_back = 0;
	right_shoulder_rotate = 0;
	right_shoulder_forward_angle = 0;
	right_shoulder_outward_angle = 0;
	right_shoulder_twist_angle = 0;
	right_elbow_forward_angle = 0;
	right_lower_arm_retract = 0;
	right_leg_drop = 0;
	right_leg_forward_angle = 0;
	right_leg_outward_angle = 5;
	right_leg_twist_angle = 15;
	right_upper_leg_length = 0;
	right_lower_leg_length = 0;
	right_knee_angle = 0;
	right_foot_angle = -6;
	right_foot_retract = 0;
	left_shoulder_back = 0;
	left_shoulder_rotate = 0;
	left_shoulder_forward_angle = 0;
	left_shoulder_outward_angle = 0;
	left_shoulder_twist_angle = 0;
	left_elbow_forward_angle = 0;
	left_lower_arm_retract = 0;
	left_leg_drop = 0;
	left_leg_forward_angle = 0;
	left_leg_outward_angle = 5;
	left_leg_twist_angle = 15;
	left_upper_leg_length = 0;
	left_lower_leg_length = 0;
	left_knee_angle = 0;
	left_foot_angle = -6;
	left_foot_retract = 0;
}  // Reset


void Decepticon :: SetTransformPosition(float new_value)
{
	transform_position = new_value;
}  // SetTransformPosition


// *********************************************************************** //
// ****************************** Accessors ****************************** //
// *********************************************************************** //
bool Decepticon :: IsTransforming()
{
	return transforming;
}  // IsTransforming


float Decepticon :: GetTransformPosition()
{
	return transform_position;
}  // GetTransformPosition


int Decepticon :: GetWindowAngle()
{
	return window_angle;
}  // GetWindowAngle


int Decepticon :: GetBendAngle()
{
	return bend_angle;
}  // GetBendAngle


int Decepticon :: GetRightShoulderBack()
{
	return right_shoulder_back;
}  // GetRightShoulderBack


int Decepticon :: GetRightShoulderRotate()
{
	return right_shoulder_rotate;
}  // GetRightShoulderRotate


int Decepticon :: GetRightShoulderForwardAngle()
{
	return right_shoulder_forward_angle;
}  // GetRightShoulderForwardAngle


int Decepticon :: GetRightShoulderOutwardAngle()
{
	return right_shoulder_outward_angle;
}  // GetRightShoulderOutwardAngle


int Decepticon :: GetRightShoulderTwistAngle()
{
	return right_shoulder_twist_angle;
}  // GetRightShoulderTwistAngle


int Decepticon :: GetRightElbowForwardAngle()
{
	return right_elbow_forward_angle;
}  // GetRightElbowForwardAngle


int Decepticon :: GetRightLowerArmRetract()
{
	return right_lower_arm_retract;
}  // GetRightLowerArmRetract


int Decepticon :: GetRightUpperLegLength()
{
	return right_upper_leg_length;
}  // GetRightUpperLegLength


int Decepticon :: GetRightLowerLegLength()
{
	return right_lower_leg_length;
}  // GetRightLowerLegLength


int Decepticon :: GetRightLegDrop()
{
	return right_leg_drop;
}  // GetRightLegDrop


int Decepticon :: GetRightLegForwardAngle()
{
	return right_leg_forward_angle;
}  // GetRightLegForwardAngle


int Decepticon :: GetRightLegOutwardAngle()
{
	return right_leg_outward_angle;
}  // GetRightLegOutwardAngle


int Decepticon :: GetRightLegTwistAngle()
{
	return right_leg_twist_angle;
}  // GetRightLegTwistAngle


int Decepticon :: GetRightKneeAngle()
{
	return right_knee_angle;
}  // GetRightKneeAngle


int Decepticon :: GetRightFootAngle()
{
	return right_foot_angle;
}  // GetRightFootAngle


int Decepticon :: GetRightFootRetract()
{
	return right_foot_retract;
}  // GetRightFootRetract


int Decepticon :: GetLeftShoulderBack()
{
	return left_shoulder_back;
}  // GetLeftShoulderBack


int Decepticon :: GetLeftShoulderRotate()
{
	return left_shoulder_rotate;
}  // GetLeftShoulderRotate


int Decepticon :: GetLeftShoulderForwardAngle()
{
	return left_shoulder_forward_angle;
}  // GetLeftShoulderForwardAngle


int Decepticon :: GetLeftShoulderOutwardAngle()
{
	return left_shoulder_outward_angle;
}  // GetLeftShoulderOutwardAngle


int Decepticon :: GetLeftShoulderTwistAngle()
{
	return left_shoulder_twist_angle;
}  // GetLeftShoulderTwistAngle


int Decepticon :: GetLeftElbowForwardAngle()
{
	return left_elbow_forward_angle;
}  // GetLeftElbowTwistAngle


int Decepticon :: GetLeftLowerArmRetract()
{
	return left_lower_arm_retract;
}  // GetLeftLowerArmRetract


int Decepticon :: GetLeftUpperLegLength()
{
	return left_upper_leg_length;
}  // GetLeftUpperLegLength


int Decepticon :: GetLeftLowerLegLength()
{
	return left_lower_leg_length;
}  // GetLeftLowerLegLength


int Decepticon :: GetLeftLegForwardAngle()
{
	return left_leg_forward_angle;
}  // GetLeftForwardAngle


int Decepticon :: GetLeftLegOutwardAngle()
{
	return left_leg_outward_angle;
}  // GetLeftOutwardAngle


int Decepticon :: GetLeftLegDrop()
{
	return left_leg_drop;
}  // GetLeftLegDrop


int Decepticon :: GetLeftLegTwistAngle()
{
	return left_leg_twist_angle;
}  // GetLeftLegTwistAngle


int Decepticon :: GetLeftKneeAngle()
{
	return left_knee_angle;
}  // GetLeftKneeAngle


int Decepticon :: GetLeftFootAngle()
{
	return left_foot_angle;
}  // GetLeftFootAngle


int Decepticon :: GetLeftFootRetract()
{
	return left_foot_retract;
}  // GetLeftFootRetract


int Decepticon :: GetTorsoLength()
{
	return torso_length;
}  // GetTorsoLength


// ************************************************************************** //
// ****************************** Manipulators ****************************** //
// ************************************************************************** //
void Decepticon :: Draw()
{
	glPushMatrix();
		glTranslatef(0, transform_position, 0);
		glRotatef(-bend_angle, -1, 0, 0);

		glPushMatrix();
			glTranslatef(0, -torso_length, 0);
			DrawBody();												// draw body
			glPushMatrix();
				glTranslatef(0, 10, 20);
				glPushMatrix();
					glTranslatef(0, 10, -20);
					if (display_mode == GL_POLYGON)
					{
						GLfloat mat_ambient[] = {1.0, 0.0, 1.0, 1.0};
						GLfloat mat_diffuse[] = {1.0, 0.0, 1.0, 1.0};
						glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

						glutSolidTeapot(15);

						mat_ambient[0] = 0.0;
						mat_ambient[1] = 0.0;
						mat_ambient[2] = 1.0;
						mat_diffuse[0] = 0.0;
						mat_diffuse[1] = 0.0;
						mat_diffuse[2] = 0.8;
						glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
					}  // if statement
				glPopMatrix();
				glRotatef(window_angle, 1, 0, 0);
				DrawWindow();											// draw window
			glPopMatrix();
			glPushMatrix();
				glTranslatef(50, 47.5, 15);
				glRotatef(left_shoulder_forward_angle, -1, 0, 0);
				glRotatef(left_shoulder_outward_angle, 0, 0, 1);
				glTranslatef(0, 0, left_shoulder_back);
				glRotatef(left_shoulder_rotate, 0, 1, 0);
				DrawShoulder();											// draw left shoulder
				glPushMatrix();
					glTranslatef(0, 10, 0);
					glRotatef(left_shoulder_twist_angle, 0, 1, 0);
					DrawUpperArm();										// draw left upper arm
					glPushMatrix();
						glTranslatef(9, -40, 0);
						glRotatef(left_elbow_forward_angle, -1, 0, 0);
						glTranslatef(0, left_lower_arm_retract, 0);
						DrawLowerArm();									// draw left lower arm
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-50, 47.5, 15);
				glScalef(-1, 1, 1);
				glRotatef(right_shoulder_forward_angle, 1, 0, 0);
				glRotatef(right_shoulder_outward_angle, 0, 0, 1);
				glTranslatef(0, 0, right_shoulder_back);
				glRotatef(right_shoulder_rotate, 0, 1, 0);
				DrawShoulder();											// draw right shoulder
				glPushMatrix();
					glTranslatef(0, 10, 0);
					glRotatef(right_shoulder_twist_angle, 0, 1, 0);
					DrawUpperArm();										// draw right upper arm
					glPushMatrix();
						glTranslatef(9, -40, 0);
						glRotatef(right_elbow_forward_angle, 1, 0, 0);
						glTranslatef(0, right_lower_arm_retract, 0);
						DrawLowerArm();									// draw right lower arm
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glTranslatef(0, torso_length, 0);
			DrawTorso();												// draw torso
			glPushMatrix();
				glTranslatef(0, -15, 0);
				glRotatef(bend_angle, -1, 0, 0);
				glRotatef(hips_angle, -1, 0, 0);
				DrawHips();												// draw hips
				glPushMatrix();
					glTranslatef(0, -12.5, 15);
					DrawRewind();
					DrawFastForward();
					DrawPlay();
					DrawStop();
					DrawPause();
					glPushMatrix();
						glTranslatef(22.5, -5, -15);
						glTranslatef(0, left_leg_drop, 0);
						glRotatef(left_leg_twist_angle, 0, 1, 0);
						glRotatef(left_leg_forward_angle, -1, 0, 0);
						glRotatef(left_leg_outward_angle, 0, 0, 1);
						glTranslatef(0, left_upper_leg_length, 0);
						DrawUpperLeg();									// draw left upper leg
						glPushMatrix();
							glTranslatef(0, -65, 0);
							glTranslatef(0, left_lower_leg_length, 0);
							glRotatef(left_knee_angle, 1, 0, 0);
							DrawLowerLeg();								// draw left lower leg
							glTranslatef(0, -70, 5);
							glRotatef(left_foot_angle, 1, 0, 0);
							glTranslatef(0, 0, left_foot_retract);
							DrawFoot();									// draw left foot
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-22.5, -5, -15);
						glTranslatef(0, right_leg_drop, 0);
						glRotatef(right_leg_twist_angle, 0, -1, 0);
						glRotatef(right_leg_forward_angle, -1, 0, 0);
						glRotatef(right_leg_outward_angle, 0, 0, -1);
						glTranslatef(0, right_upper_leg_length, 0);
						DrawUpperLeg();									// draw right upper leg
						glPushMatrix();
							glTranslatef(0, -65, 0);
							glScalef(-1, 1, 1);
							glTranslatef(0, right_lower_leg_length, 0);
							glRotatef(right_knee_angle, 1, 0, 0);
							DrawLowerLeg();								// draw right lower leg
							glTranslatef(0, -70, 5);
							glRotatef(right_foot_angle, 1, 0, 0);
							glTranslatef(0, 0, right_foot_retract);
							DrawFoot();									// draw right foot
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}  // DrawSoundwave


void Decepticon :: CalculateNormal(float ux, float uy, float uz, float vx, float vy, float vz)
{
	double length = 0;

	normal_vector[0] = (uy*vz - vy*uz);
	normal_vector[1] = (vx*uz - ux*vz);
	normal_vector[2] = (ux*vy - vx*uy);

	length = sqrt((normal_vector[0] * normal_vector[0]) + (normal_vector[1] * normal_vector[1]) + (normal_vector[2] * normal_vector[2]));

	normal_vector[0] = normal_vector[0] / length;
	normal_vector[1] = normal_vector[1] / length;
	normal_vector[2] = normal_vector[2] / length;
}  // CalculateNormal


void Decepticon :: ChangeColor(float ambientR, float ambientG, float ambientB, float ambientA, float diffuseR, float diffuseG, float diffuseB, float diffuseA)
{
		// change ambient RGBA values
	mat_ambient[0] = ambientR;
	mat_ambient[1] = ambientG;
	mat_ambient[2] = ambientB;
	mat_ambient[3] = ambientA;
		// change diffuse RGBA values
	mat_diffuse[0] = diffuseR;
	mat_diffuse[1] = diffuseG;
	mat_diffuse[2] = diffuseB;
	mat_diffuse[3] = diffuseA;
		// set ambient and diffuse as new colors
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}  // ChangeColor


// ********************************************************************** //
// ****************************** Mutators ****************************** //
// ********************************************************************** //
void Decepticon :: Transform(bool step)
{
	if (transformed)		// if in boombox form, then untransform
	{
		if (!step)
			transforming = true;

		if (left_knee_angle < MIN_KNEE_ANGLE && right_knee_angle < MIN_KNEE_ANGLE)
		{
			left_knee_angle += 2;
			right_knee_angle += 2;

			if (left_leg_drop < MIN_LEG_DROP && right_leg_drop < MIN_LEG_DROP)
			{
				left_leg_drop++;
				right_leg_drop++;
				torso_length--;
			}  // inner if statement
			else if (torso_length > MAX_TORSO_LENGTH)
				torso_length--;
		}  // outer if statement

		if (left_knee_angle == MIN_KNEE_ANGLE && right_knee_angle == MIN_KNEE_ANGLE)
		{
			if (left_lower_leg_length > MIN_LOWER_LEG_LENGTH && right_lower_leg_length > MIN_LOWER_LEG_LENGTH)
			{
				left_lower_leg_length--;
				right_lower_leg_length--;
			}  // inner if statement
		}  // outer if statement

		if (left_lower_leg_length == MIN_LOWER_LEG_LENGTH && right_lower_leg_length == MIN_LOWER_LEG_LENGTH)
		{
			if (left_upper_leg_length > MIN_UPPER_LEG_LENGTH && right_upper_leg_length > MIN_UPPER_LEG_LENGTH)
			{
				left_upper_leg_length -= 2;
				right_upper_leg_length -= 2;
			}  // inner if statement
		}  // outer if statement

		if (left_upper_leg_length == MIN_UPPER_LEG_LENGTH && right_upper_leg_length == MIN_UPPER_LEG_LENGTH)
		{
			if (left_foot_retract > MIN_FOOT_RETRACT && right_foot_retract > MIN_FOOT_RETRACT)
			{
				left_foot_retract--;
				right_foot_retract--;
			}  // inner if statement
		}  // outer if statement

		if (left_foot_retract == MIN_FOOT_RETRACT && right_foot_retract == MIN_FOOT_RETRACT)
		{
			if (left_leg_forward_angle > MIN_LEG_FORWARD_ANGLE && right_leg_forward_angle > MIN_LEG_FORWARD_ANGLE)
			{
				left_leg_forward_angle -= 2;
				right_leg_forward_angle -= 2;
				transform_position =  (cos((double)left_leg_forward_angle * 0.0174532925) * 139.5) - 139.5;
			}  // inner if statement
		}  // outer if statement

		if (left_leg_forward_angle == MIN_LEG_FORWARD_ANGLE && right_leg_forward_angle == MIN_LEG_FORWARD_ANGLE)
		{
			if (left_leg_twist_angle > MIN_LEG_TWIST_ANGLE && right_leg_twist_angle > MIN_LEG_TWIST_ANGLE)
			{
				left_leg_twist_angle = (left_leg_twist_angle - 3) % 360;
				right_leg_twist_angle = (right_leg_twist_angle - 3) % 360;
			}  // inner if statement
		}  // outer if statement

		if (left_leg_twist_angle == MIN_LEG_TWIST_ANGLE && right_leg_twist_angle == MIN_LEG_TWIST_ANGLE)
		{
			if (left_shoulder_rotate > MIN_SHOULDERS_ROTATE && right_shoulder_rotate > MIN_SHOULDERS_ROTATE)
			{
				left_shoulder_rotate -= 3;
				right_shoulder_rotate -= 3;
			}  // inner if statement
		}  // outer if statement

		if (left_shoulder_rotate == MIN_SHOULDERS_ROTATE && right_shoulder_rotate == MIN_SHOULDERS_ROTATE)
		{
			if (left_shoulder_back < MIN_SHOULDERS_BACK && right_shoulder_back < MIN_SHOULDERS_BACK)
			{
				left_shoulder_back += 3;
				right_shoulder_back += 3;
			}  // inner if statement
		}  // outer if statement

		if (left_shoulder_back == MIN_SHOULDERS_BACK && right_shoulder_back == MIN_SHOULDERS_BACK)
		{
			if (left_lower_arm_retract > MIN_LOWER_ARM_RETRACT && right_lower_arm_retract > MIN_LOWER_ARM_RETRACT)
			{
				left_lower_arm_retract--;
				right_lower_arm_retract--;
			}
			else
			{
				transforming = false;
				transformed = !transformed;
			}  // else statement
		}  // if statement
	}  // if statement

	else					// else, transform into boombox form
	{
		if (!step)
			transforming = true;

		if (left_lower_arm_retract < MAX_LOWER_ARM_RETRACT && right_lower_arm_retract < MAX_LOWER_ARM_RETRACT)
		{
			left_lower_arm_retract++;
			right_lower_arm_retract++;
		}  // if statement

		if (left_lower_arm_retract ==MAX_LOWER_ARM_RETRACT && right_lower_arm_retract == MAX_LOWER_ARM_RETRACT)
		{
			if (left_shoulder_back > MAX_SHOULDERS_BACK && right_shoulder_back > MAX_SHOULDERS_BACK)
			{
				left_shoulder_back -= 3;
				right_shoulder_back -= 3;
			}  // inner if statement
		}  // outer if statement

		if (left_shoulder_back == MAX_SHOULDERS_BACK && right_shoulder_back == MAX_SHOULDERS_BACK)
		{
			if (left_shoulder_rotate < MAX_SHOULDERS_ROTATE && right_shoulder_rotate < MAX_SHOULDERS_ROTATE)
			{
				left_shoulder_rotate += 3;
				right_shoulder_rotate += 3;
			}  // inner if statement
		}  // outer if statement

		if (left_shoulder_rotate == MAX_SHOULDERS_ROTATE && right_shoulder_rotate == MAX_SHOULDERS_ROTATE)
		{
			if (left_leg_twist_angle < MAX_LEG_TWIST_ANGLE && right_leg_twist_angle < MAX_LEG_TWIST_ANGLE)
			{
				left_leg_twist_angle = (left_leg_twist_angle + 3) % 360;
				right_leg_twist_angle = (right_leg_twist_angle + 3) % 360;
			}  // inner if statement
		}  // outer if statement

		if (left_leg_twist_angle == MAX_LEG_TWIST_ANGLE && right_leg_twist_angle == MAX_LEG_TWIST_ANGLE)
		{
			if (left_leg_forward_angle < MAX_LEG_FORWARD_ANGLE && right_leg_forward_angle < MAX_LEG_FORWARD_ANGLE)
			{
				left_leg_forward_angle += 2;
				right_leg_forward_angle += 2;
				transform_position =  (cos((double)left_leg_forward_angle * 0.0174532925) * 139.5) - 139.5;
			}  // inner if statement
		}  // outer if statement

		if (left_leg_forward_angle == MAX_LEG_FORWARD_ANGLE && right_leg_forward_angle == MAX_LEG_FORWARD_ANGLE)
		{
			if (left_foot_retract < MAX_FOOT_RETRACT && right_foot_retract < MAX_FOOT_RETRACT)
			{
				left_foot_retract++;
				right_foot_retract++;
			}  // inner if statement
		}  // outer if statement

		if (left_foot_retract == MAX_FOOT_RETRACT && right_foot_retract == MAX_FOOT_RETRACT)
		{
			if (left_upper_leg_length < MAX_UPPER_LEG_LENGTH && right_upper_leg_length < MAX_UPPER_LEG_LENGTH)
			{
				left_upper_leg_length += 2;
				right_upper_leg_length += 2;
			}  // inner if statement
		}  // outer if statement

		if (left_upper_leg_length == MAX_UPPER_LEG_LENGTH && right_upper_leg_length == MAX_UPPER_LEG_LENGTH)
		{
			if (left_lower_leg_length < MAX_LOWER_LEG_LENGTH && right_lower_leg_length < MAX_LOWER_LEG_LENGTH)
			{
				left_lower_leg_length++;
				right_lower_leg_length++;
			}  // inner if statement
		}  // outer if statement

		if (left_lower_leg_length == MAX_LOWER_LEG_LENGTH && right_lower_leg_length == MAX_LOWER_LEG_LENGTH)
		{
			if (left_knee_angle > MAX_KNEE_ANGLE && right_knee_angle > MAX_KNEE_ANGLE)
			{
				left_knee_angle -= 2;
				right_knee_angle -= 2;

				if (left_leg_drop > MAX_LEG_DROP && right_leg_drop > MAX_LEG_DROP)
				{
					left_leg_drop--;
					right_leg_drop--;
					torso_length++;
				}  // inner inner if statement
				else if (torso_length < MAX_TORSO_LENGTH)
					torso_length++;
			}  // inner if statement
			else
			{
				transforming = false;
				transformed = !transformed;
			}  // else statement
		}  // outer if statement
	}  // else statement
}  // Transform
