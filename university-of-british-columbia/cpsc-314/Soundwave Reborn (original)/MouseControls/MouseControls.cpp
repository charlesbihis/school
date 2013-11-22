#include <stdio.h>
#include <gl\glut.h>
#include "../MouseControls/MouseControls.h"


namespace
{
  Mouse* mouse_instance = NULL;
}


Mouse* Mouse :: ControlInstance()
{
  if (mouse_instance == NULL)			// check if it is the first call
    mouse_instance = new Mouse();	// create single instance

  return mouse_instance;				// address of single instance
}  // MouseInstance


Mouse :: Mouse()
{
}  // Control
