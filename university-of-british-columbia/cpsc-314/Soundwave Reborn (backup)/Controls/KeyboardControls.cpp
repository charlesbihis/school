#include <stdio.h>
#include <gl\glut.h>
#include <math.h>
#include "../Controls/KeyboardControls.h"
#include "../Controls/CameraControls.h"
#include "../Controls/CharacterControls.h"
#include "../Systems/Decepticon.h"
#include "../Systems/Scene.h"


namespace
{
	Keyboard* keyboard_instance = NULL;
	Camera *camera_controller = Camera :: ControlInstance();
	Character *character_controller = Character :: ControlInstance();
	Decepticon *soundwave = Decepticon :: DecepticonInstance();
	Scene *cybertron = Scene :: ControlInstance();
}  // namespace


Keyboard* Keyboard :: ControlInstance()
{
  if (keyboard_instance == NULL)		// check if it is the first call
    keyboard_instance = new Keyboard();	// create single instance

  return keyboard_instance;				// address of single instance
}  // KeyboardInstance


Keyboard :: Keyboard()
{
	cameraspeed = 0.03;
	inverted = false;
}  // Keyboard


void Keyboard :: InterpretKey(unsigned int key)
{
	switch(key) 
	{	
		// basic controls
		case 27:				// escape key
		case 'q':
			exit(0);
			break;
		case 'h':
			PrintBasicHelp();
			break;
		case 'H':
			PrintCharacterHelp();
			break;
		case ' ':
			character_controller->PauseRotation();
			break;
		case 8:					// backspace key
			character_controller->Reset();
			soundwave->Reset();
			break;
		// custom movements
		case '1':
			soundwave->Transform();
			break;
		case '2':
			soundwave->Transform();
			break;
		case '3':
			soundwave->Backflip();
			break;
		// arm movements
		case 's':
			soundwave->RotateLeftShoulderForward();
			break;
		case 'S':
			soundwave->RotateLeftShoulderBackward();
			break;
		case 'd':
			soundwave->RotateRightShoulderForward();
			break;
		case 'D':
			soundwave->RotateRightShoulderBackward();
			break;
		case 'a':
			soundwave->RaiseLeftShoulder();
			break;
		case 'A':
			soundwave->LowerLeftShoulder();
			break;
		case 'f':
			soundwave->RaiseRightShoulder();
			break;
		case 'F':
			soundwave->LowerRightShoulder();
			break;
		case 'x':
			soundwave->RaiseLeftHand();
			break;
		case 'X':
			soundwave->LowerLeftHand();
			break;
		case 'c':
			soundwave->RaiseRightHand();
			break;
		case 'C':
			soundwave->LowerRightHand();
			break;
		case 'w':
			soundwave->TwistLeftShoulderOutward();
			break;
		case 'W':
			soundwave->TwistLeftShoulderInward();
			break;
		case 'e':
			soundwave->TwistRightShoulderOutward();
			break;
		case 'E':
			soundwave->TwistRightShoulderInward();
			break;
		// leg movements
		case 'k':
			soundwave->RaiseLeftLeg();
			break;
		case 'K':
			soundwave->LowerLeftLeg();
			break;
		case 'l':
			soundwave->RaiseRightLeg();
			break;
		case 'L':
			soundwave->LowerRightLeg();
			break;
		case 'j':
			soundwave->RaiseLeftLegOutward();
			break;
		case 'J':
			soundwave->LowerLeftLegInward();
			break;
		case ';':
			soundwave->RaiseRightLegOutward();
			break;
		case ':':
			soundwave->LowerRightLegInward();
			break;
		case 'i':
			soundwave->TwistLeftLegOutward();
			break;
		case 'I':
			soundwave->TwistLeftLegInward();
			break;
		case 'o':
			soundwave->TwistRightLegOutward();
			break;
		case 'O':
			soundwave->TwistRightLegInward();
			break;
		case ',':
			soundwave->BendLeftKnee();
			break;
		case '<':
			soundwave->StraightenLeftKnee();
			break;
		case '.':
			soundwave->BendRightKnee();
			break;
		case '>':
			soundwave->StraightenRightKnee();
			break;
		case 'm':
			soundwave->RaiseLeftFoot();
			break;
		case 'M':
			soundwave->LowerLeftFoot();
			break;
		case '/':
			soundwave->RaiseRightFoot();
			break;
		case '?':
			soundwave->LowerRightFoot();
			break;
		// controls
		case '[':
			character_controller->ToggleFog();
			character_controller->IncreaseFogStart();
			character_controller->ToggleFog();
			break;
		case '{':
			character_controller->ToggleFog();
			character_controller->DecreaseFogStart();
			character_controller->ToggleFog();
			break;
		case ']':
			character_controller->ToggleFog();
			character_controller->IncreaseFogEnd();
			character_controller->ToggleFog();
			break;
		case '}':
			character_controller->ToggleFog();
			character_controller->DecreaseFogEnd();
			character_controller->ToggleFog();
			break;
		// extra movements		
		case 't':
			soundwave->OpenWindow();
			break;
		case 'T':
			soundwave->CloseWindow();
			break;
		case 'b':
			soundwave->LeanForward();
			break;
		case 'B':
			soundwave->LeanBackward();
			break;
		default:
			printf("A key is pressed: %c\n", key);
			break;
	}  // switch statement
}  // InterpretKey


void Keyboard :: InterpretSpecialKey(unsigned int special_key)
{
	switch(special_key)
	{
		case GLUT_KEY_LEFT:
			camera_controller->camera_position_x -= 10;
			camera_controller->camera_target_x -= 10;
			printf("Moving camera left.\n");
			break;
		case GLUT_KEY_RIGHT:
			camera_controller->camera_position_x += 10;
			camera_controller->camera_target_x += 10;
			printf("Moving camera right.\n");
			break;
		case GLUT_KEY_UP:
			camera_controller->depth -= 10;
			printf("Moving camera up.\n");
			break;
		case GLUT_KEY_DOWN:
			camera_controller->depth += 10;
			printf("Moving camera down.\n");
			break;
		case GLUT_KEY_F1:
			soundwave->ToggleDisplayMode();
			printf("Toggling display mode.\n");
			break;
		case GLUT_KEY_F2:
			soundwave->ToggleAntiAliasing();
			printf("Toggling anti-aliasing.\n");
			break;
		case GLUT_KEY_F3:
			character_controller->ToggleFog();
			printf("Toggling fog.\n");
			break;
		case GLUT_KEY_F4:
			inverted = !inverted;
			printf("Toggling look-inversion.\n");
			break;
		case GLUT_KEY_F5:
		case GLUT_KEY_F6:
		case GLUT_KEY_F7:
			cybertron->ToggleLight(special_key);
			break;
		case GLUT_KEY_PAGE_UP:
			character_controller->IncreaseRotateSpeed();
			printf("Increasing right-rotation speed.\n");
			break;
		case GLUT_KEY_PAGE_DOWN:
			character_controller->DecreaseRotateSpeed();
			printf("Increasing left-rotation speed.\n");
			break;
		default:
			printf("A special key is pressed: %c\n", special_key);
			break;
	}  // switch statement
}  // InterpretSpecialKey


void Keyboard :: PrintBasicHelp()
{
	printf("\n\n***** Basic Help *****\n\n");
	printf("  mouse.........................rotate view\n");
	printf("  esc...........................quit program\n");
	printf("  'h'...........................view basic help\n");
	printf("  'H'...........................view character help\n\n");

	printf("  '1'...........................transform to boombox (must be in robot form)\n");
	printf("  '2'...........................transform to robot (must be in boombox form)\n");
	printf("  '3'...........................backflip (must be in robot form)\n\n");

	printf("  left arrow....................move camera left along x-axis\n");
	printf("  right arrow...................move camera right along x-axis\n");
	printf("  up arrow......................move camera up along z-axis\n");
	printf("  down arrow....................move camera down along z-axis\n\n");

	printf("  page up.......................increase right-rotation speed\n");
	printf("  page down.....................increase left-rotation speed\n");
	printf("  spacebar......................pause/resume rotation\n\n");

	printf("  F1............................toggle wire-frame mode\n");
	printf("  F2............................toggle anti-aliasing\n");
	printf("  F3............................toggle fog\n");
	printf("  F4............................toggle look-inversion\n\n");

	printf("  F5............................toggle front-left spotlight\n");
	printf("  F6............................toggle front-right spotlight\n");
	printf("  F7............................toggle back spotlight\n\n");

	printf("  '[' / '{'.....................increase/decrease fog-start\n");
	printf("  ']' / '}'.....................increase/decrease fog-end\n");
}  // PrintBasicHelp


void Keyboard :: PrintCharacterHelp()
{
	printf("\n\n***** Character Help *****\n\n");
	printf("  mouse.........................rotate view\n");
	printf("  esc...........................quit program\n");
	printf("  'h'...........................view basic help\n");
	printf("  'H'...........................view character help\n\n");

	printf("Arm Movements\n");
	printf("  's' / 'S'.....................rotate left shoulder forwards/backwards\n");
	printf("  'd' / 'D'.....................rotate right shoulder forwards/backwards\n");
	printf("  'a' / 'A'.....................raise left arm\n");
	printf("  'f' / 'F'.....................raise right arm\n");
	printf("  'x' / 'X'.....................raise left hand\n");
	printf("  'c' / 'C'.....................raise right hand\n");
	printf("  'w' / 'W'.....................twist left shoulder inward/outward\n");
	printf("  'e' / 'E'.....................twist right shoulder inward/outward\n\n");

	printf("Leg Movements\n");
	printf("  'k' / 'K'.....................rotate left leg forwards/backwards\n");
	printf("  'l' / 'L'.....................rotate right leg forwards/backwards\n");
	printf("  'j' / 'J'.....................move left leg outwards/inwards\n");
	printf("  ';' / ':'.....................move right leg outwards/inwards\n");
	printf("  ',' / '<'.....................bend/straighten left knee\n");
	printf("  '.' / '>'.....................bend/straighten right knee\n");
	printf("  'm' / 'M'.....................raise/lower left foot\n");
	printf("  '/' / '?'.....................raise/lower right foot\n");
	printf("  'i' / 'I'.....................twist left leg outward/inward\n");
	printf("  'o' / 'O'.....................twist right leg outward/inward\n\n");

	printf("Extra Movements\n");
	printf("  't' / 'T'.....................open/close window\n");
	printf("  'b' / 'B'.....................bend forwards/backwards\n");
}  // PrintCharacterHelp
