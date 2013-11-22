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



#ifndef DECEPTICON_H#define DECEPTICON_H
class Decepticon
{
  public:
	static Decepticon* SystemInstance();

    // ***** Mutators ***** //
	void SetTransformPosition(float new_value);
	void ToggleDisplayMode();
	void ToggleAntiAliasing();
	void Reset();

	void SetWindowAngle(int new_value);						// in Decepticon_DrawBody.cpp
	void OpenWindow();
	void CloseWindow();
	
	void SetTorsoLength(int new_value);						// in Decepticon_DrawTorse.cpp

	void SetBendAngle(int new_value);						// in Decepticon_DrawHips.cpp
	void LeanForward();
	void LeanBackward();
	void RaiseHips();
	void LowerHips();
	
	void SetRightShoulderBack(int new_value);				// in Decepticon_DrawShoulder.cpp
	void SetRightShoulderRotate(int new_value);
	void SetRightShoulderForwardAngle(int new_value);
	void RotateRightShoulderForward();
	void RotateRightShoulderBackward();
	void SetRightShoulderOutwardAngle(int new_value);
	void RaiseRightShoulder();
	void LowerRightShoulder();
	void SetRightShoulderTwistAngle(int new_value);
	void TwistRightShoulderOutward();
	void TwistRightShoulderInward();
	void SetLeftShoulderBack(int new_value);
	void SetLeftShoulderRotate(int new_value);
	void SetLeftShoulderForwardAngle(int new_value);
	void RotateLeftShoulderForward();
	void RotateLeftShoulderBackward();
	void SetLeftShoulderOutwardAngle(int new_value);
	void RaiseLeftShoulder();
	void LowerLeftShoulder();
	void SetLeftShoulderTwistAngle(int new_value);
	void TwistLeftShoulderOutward();
	void TwistLeftShoulderInward();

	void SetRightElbowForwardAngle(int new_value);			// in Decepticon_DrawLowerArm.cpp
	void RaiseRightHand();
	void LowerRightHand();
	void SetRightLowerArmRetract(int new_value);
	void SetLeftElbowForwardAngle(int new_value);
	void RaiseLeftHand();
	void LowerLeftHand();
	void SetLeftLowerArmRetract(int new_value);
	
	void SetRightUpperLegLength(int new_value);				// in Decepticon_DrawUpperLeg.cpp
	void SetRightLegForwardAngle(int new_value);
	void RaiseRightLeg();
	void LowerRightLeg();
	void SetRightLegOutwardAngle(int new_value);
	void RaiseRightLegOutward();
	void LowerRightLegInward();
	void SetRightLegTwistAngle(int new_value);
	void TwistRightLegOutward();
	void TwistRightLegInward();
	void SetLeftUpperLegLength(int new_value);
	void SetLeftLowerLegLength(int new_value);
	void RaiseLeftLeg();
	void LowerLeftLeg();
	void SetLeftLegOutwardAngle(int new_value);
	void RaiseLeftLegOutward();
	void LowerLeftLegInward();
	void SetLeftLegTwistAngle(int new_value);
	void TwistLeftLegOutward();
	void TwistLeftLegInward();

	void SetRightLowerLegLength(int new_value);				// in Decepticon_DrawLowerLeg.cpp
	void SetRightLegDrop(int new_value);
	void SetRightKneeAngle(int new_value);
	void BendRightKnee();
	void StraightenRightKnee();
	void SetLeftLegDrop(int new_value);
	void SetLeftLegForwardAngle(int new_value);
	void SetLeftKneeAngle(int new_value);
	void BendLeftKnee();
	void StraightenLeftKnee();

	void SetRightFootAngle(int new_value);					// in Decepticon_DrawFoot.cpp
	void RaiseRightFoot();
	void LowerRightFoot();
	void SetRightFootRetract(int new_value);
	void SetLeftFootAngle(int new_value);
	void RaiseLeftFoot();
	void LowerLeftFoot();
	void SetLeftFootRetract(int new_value);

	// ***** Accessors ***** //
	bool IsTransforming();
	float GetTransformPosition();
	int GetWindowAngle();
	int GetBendAngle();
	int GetRightShoulderBack();
	int GetRightShoulderRotate();
	int GetRightShoulderForwardAngle();
	int GetRightShoulderOutwardAngle();
	int GetRightShoulderTwistAngle();
	int GetRightElbowForwardAngle();
	int GetRightLowerArmRetract();
	int GetRightUpperLegLength();
	int GetRightLowerLegLength();
	int GetRightLegDrop();
	int GetRightLegForwardAngle();
	int GetRightLegOutwardAngle();
	int GetRightLegTwistAngle();
	int GetRightKneeAngle();
	int GetRightFootAngle();
	int GetRightFootRetract();
	int GetLeftShoulderBack();
	int GetLeftShoulderRotate();
	int GetLeftShoulderForwardAngle();
	int GetLeftShoulderOutwardAngle();
	int GetLeftShoulderTwistAngle();
	int GetLeftElbowForwardAngle();
	int GetLeftLowerArmRetract();
	int GetLeftUpperLegLength();
	int GetLeftLowerLegLength();
	int GetLeftLegForwardAngle();
	int GetLeftLegOutwardAngle();
	int GetLeftLegDrop();
	int GetLeftLegTwistAngle();
	int GetLeftKneeAngle();
	int GetLeftFootAngle();
	int GetLeftFootRetract();
	int GetTorsoLength();

	// ***** Manipulators ***** //
	void Draw();

	// ***** Mutators ***** //
	void Transform(bool step = false);

	const static int MAX_SHOULDERS_BACK = -27.5;
	const static int MIN_SHOULDERS_BACK = 0;
	const static int MAX_SHOULDERS_ROTATE = 90;
	const static int MIN_SHOULDERS_ROTATE = 0;
	const static int MAX_TORSO_LENGTH = 15;
	const static int MIN_TORSO_LENGTH = 0;
	const static int MAX_LEG_TWIST_ANGLE = 90;
	const static int MIN_LEG_TWIST_ANGLE = 0;
	const static int MAX_LEG_FORWARD_ANGLE = 90;
	const static int MIN_LEG_FORWARD_ANGLE = 0;
	const static int MAX_UPPER_LEG_LENGTH = 20;
	const static int MIN_UPPER_LEG_LENGTH = 0;
	const static int MAX_LOWER_LEG_LENGTH = 7;
	const static int MIN_LOWER_LEG_LENGTH = 0;
	const static int MAX_LEG_DROP = -10;
	const static int MIN_LEG_DROP = 0;
	const static int MAX_LOWER_ARM_RETRACT = 8;
	const static int MIN_LOWER_ARM_RETRACT = 0;
	const static int MAX_FOOT_RETRACT = 5;
	const static int MIN_FOOT_RETRACT = 0;
	const static int MAX_KNEE_ANGLE = -90;
	const static int MIN_KNEE_ANGLE = 0;
	const static int NORMAL_VECTOR_SIZE = 3;

  private:
   	void DrawBody();
	void DrawWindow();
	void DrawShoulder();
	void DrawUpperArm();
	void DrawLowerArm();
	void DrawTorso();
	void DrawHips();
	void DrawRewind();
	void DrawFastForward();
	void DrawPlay();
	void DrawStop();
	void DrawPause();
	void DrawUpperLeg();
	void DrawLowerLeg();
	void DrawFoot();
	void Setup();
	void Spring();
	void CalculateNormal(float ux, float uy, float uz, float vx, float vy, float vz);
	void ChangeColor(float ambientR, float ambientG, float ambientB, float ambientA, float diffuseR, float diffuseG, float diffuseB, float diffuseA);

	double normal_vector[NORMAL_VECTOR_SIZE];
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	float transform_position;
	bool anti_aliasing;
	bool transformed;
	bool transforming;
    int display_mode;
	int window_angle;
	int bend_angle;
	int hips_angle;
	int torso_length;
	int right_shoulder_back;
	int right_shoulder_rotate;
	int right_shoulder_forward_angle;
    int right_shoulder_outward_angle;
    int right_shoulder_twist_angle;
    int right_elbow_forward_angle;
	int right_lower_arm_retract;
	int right_upper_leg_length;
	int right_lower_leg_length;
	int right_leg_drop;
	int right_leg_forward_angle;
	int right_leg_outward_angle;
	int right_leg_twist_angle;
	int right_knee_angle;
	int right_foot_angle;
	int right_foot_retract;
	int left_shoulder_back;
	int left_shoulder_rotate;
	int left_shoulder_forward_angle;
    int left_shoulder_outward_angle;
    int left_shoulder_twist_angle;
    int left_elbow_forward_angle;
	int left_lower_arm_retract;
	int left_upper_leg_length;
    int left_lower_leg_length;
	int left_leg_drop;
    int left_leg_forward_angle;
	int left_leg_outward_angle;
	int left_leg_twist_angle;
	int left_knee_angle;
	int left_foot_angle;
	int left_foot_retract;

  protected:
	Decepticon();
	Decepticon(int boombox_form);
};  // class declaration

#endif