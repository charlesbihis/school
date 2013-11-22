#include <stdio.h>
#include <gl\glut.h>
#include "../KeyboardControls/KeyboardControls.h"


namespace
{
  Keyboard* keyboard_instance = NULL;
}


Keyboard* Keyboard :: ControlInstance()
{
  if (keyboard_instance == NULL)		// check if it is the first call
    keyboard_instance = new Keyboard();	// create single instance

  return keyboard_instance;				// address of single instance
}  // KeyboardInstance


Keyboard :: Keyboard()
{
}  // Control
