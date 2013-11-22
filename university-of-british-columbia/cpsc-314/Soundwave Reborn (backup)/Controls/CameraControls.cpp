#include <stdio.h>
#include <gl\glut.h>
#include "../Controls/CameraControls.h"


namespace
{
	Camera* camera_instance = NULL;
}  // namespace


Camera* Camera :: ControlInstance()
{
	if (camera_instance == NULL)			// check if it is the first call
		camera_instance = new Camera();		// create single instance

	return camera_instance;				// address of single instance
}  // ControlInstance


Camera :: Camera()
{
	temp_y = 0;
	temp_x = 0;
	camera_position_x = 0;
	camera_position_y = 0;
	camera_target_x = 0;
	camera_target_y = 0;
	depth = 500;
}  // Camera