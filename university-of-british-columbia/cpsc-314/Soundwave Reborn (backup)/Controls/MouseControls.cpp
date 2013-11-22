#include <stdio.h>
#include <gl\glut.h>
#include "../Controls/MouseControls.h"
#include "../Controls/CameraControls.h"
#include "../Controls/KeyboardControls.h"

#define MINIMUM_ZOOM 1.0
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

namespace
{
  Mouse* mouse_instance = NULL;
  Camera *camera_controller = Camera :: ControlInstance();
  Keyboard *keyboard_controller = Keyboard :: ControlInstance();
}  // namespace


Mouse* Mouse :: ControlInstance()
{
  if (mouse_instance == NULL)			// check if it is the first call
    mouse_instance = new Mouse();		// create single instance

  return mouse_instance;				// address of single instance
}  // ControlInstance


Mouse :: Mouse()
{
}  // Mouse


void Mouse :: MouseMove(int x, int y)
{
	if (keyboard_controller->inverted)		// restrict rotation of viewpoint about y-axis to avoid viewing through floor
		camera_controller->camera_target_y = (y - camera_controller->temp_y - WINDOW_HEIGHT / 2) / 0.75;
	else									// restrict rotation of viewpoint about y-axis to avoid viewing through floor
		camera_controller->camera_target_y = (y - camera_controller->temp_y - WINDOW_HEIGHT / 2) / -0.75;
											// rotate about x-axis
	camera_controller->camera_target_x = (x - camera_controller->temp_x - WINDOW_WIDTH / 2) / 0.75;

	glutPostRedisplay();
}  // MouseMove


void Mouse :: MouseClick(int button, int state, int x, int y)
{
/*
	mouse_mode = button;
	mouse_state = state;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (keyboard_controller->inverted)
			camera_controller->temp_y = y - 0.2 * camera_controller->camera_target_y;
		else
			camera_controller->temp_y = y + 0.2 * camera_controller->camera_target_y;

		camera_controller->temp_x = x - 0.2 * camera_controller->camera_target_x;
	}  // if statement
	else if (button == GLUT_RIGHT_BUTTON)
	{
		camera_controller->temp_y = y - zoom_multiplier * camera_controller->depth;
	}  // else if statement
*/
}  // MouseClick
