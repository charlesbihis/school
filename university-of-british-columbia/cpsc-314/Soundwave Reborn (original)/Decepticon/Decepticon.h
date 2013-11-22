#ifndef DECEPTICON_H#define DECEPTICON_H
class Decepticon
{
  public:
    // *** Mutators *** //
    Decepticon();
	Decepticon(int boombox_form);
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

	// *** Accessors *** //
	float GetTransformPosition();
	int GetMAXSHOULDERSBACK();
	int GetMINSHOULDERSBACK();
	int GetMAXSHOULDERSROTATE();
	int GetMINSHOULDERSROTATE();
	int GetMAXTORSOLENGTH();
	int GetMINTORSOLENGTH();
	int GetMAXLEGTWISTANGLE();
	int GetMINLEGTWISTANGLE();
	int GetMAXLEGFORWARDANGLE();
	int GetMINLEGFORWARDANGLE();
	int GetMAXUPPERLEGLENGTH();
	int GetMINUPPERLEGLENGTH();
	int GetMAXLOWERLEGLENGTH();
	int GetMINLOWERLEGLENGTH();
	int GetMAXLEGDROP();
	int GetMINLEGDROP();
	int GetMAXLOWERARMRETRACT();
	int GetMINLOWERARMRETRACT();
	int GetMAXFOOTRETRACT();
	int GetMINFOOTRETRACT();
	int GetMAXKNEEANGLE();
	int GetMINKNEEANGLE();
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

	// *** Manipulators *** //
	void Draw();

	// *** Mutators *** //
	void Transform();
	void Backflip();

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
	void CalculateNormal(double ux, double uy, double uz, double vx, double vy, double vz);

	float transform_position;
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
	double normal_vector[NORMAL_VECTOR_SIZE];
	bool anti_aliasing;
	bool transformed;
    int display_mode;
	int window_angle;
	int bend_angle;
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
	int torso_length;
	int timestep;
	int hips_angle;
};  // class declaration

#endif