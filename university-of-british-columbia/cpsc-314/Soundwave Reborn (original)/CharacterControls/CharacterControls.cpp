#include <stdio.h>
#include <gl\glut.h>
#include "CharacterControls.h"


namespace
{
  Character *control_instance = NULL;
}

// ********** Accessors ********** //
Character *Character :: ControlInstance()
{
  if (control_instance == NULL)		// check if it is the first call
    control_instance = new Character();	// create single instance

  return control_instance;				// address of single instance
}  // CharacterInstance


float Character :: GetRotateSpeed()
{
  return rotate_speed;
}  // GetRotateSpeed


float Character :: GetRotateSpeedOld()
{
  return rotate_speed_old;
}  // GetRotateSpeedOld


int Character :: GetFogStart()
{
  return fog_start;
}  // GetFogStart


int Character :: GetFogEnd()
{
  return fog_end;
}  // GetFogEnd


// ********** Manipulators ********** //

// ********** Mutators ********** //
void Character :: Reset()
{
  rotate_speed = 0.0f;
  rotate_speed_old = 0.0f;

  printf("Character controls reset.\n");
}  // Reset


void Character :: PauseRotation()
{
  if (rotate_speed != 0)
  {
    rotate_speed_old = rotate_speed;
    rotate_speed = 0;
	printf("Rotation paused.\n");
  }  // if statement
  else
  {
    rotate_speed = rotate_speed_old;
	printf("Rotation resumed.\n");
  }  // else statement
}  // PauseRotation


void Character :: IncreaseRotateSpeed()
{
  rotate_speed += 0.05;
  printf("Rotate speed increased\n");
}  // IncreaseRotateSpeed


void Character :: DecreaseRotateSpeed()
{
  rotate_speed -= 0.05;
  printf("Rotate speed decreased\n");
}  // DecreaseRotateSpeed


void Character :: ToggleFog()
{
	fog = !fog;

	if (fog)
	{
		printf("Fog ON.\n");
		glEnable(GL_FOG);
		{
			glClearColor(0.4, 0.4, 0.4, 1.0);					// sets clear color to dark blue
			GLfloat fogColor[4] = {0.4, 0.4, 0.4, 1.0};
			//fogMode = GL_EXP;
			glFogi (GL_FOG_MODE, GL_LINEAR);
			glFogfv (GL_FOG_COLOR, fogColor);
			glFogf (GL_FOG_DENSITY, 0.35);
			glHint (GL_FOG_HINT, GL_DONT_CARE);
			glFogf (GL_FOG_START, fog_start);
			glFogf (GL_FOG_END, fog_end);
		}  // fog parameters
	}  // if statement
	else
	{
		printf("Fog OFF.\n");
		glClearColor(0.0, 0.0, 0.0, 0.25);					// must be same color as was set in Init function
		glDisable(GL_FOG);
	}  // else statement
}  // ToggleFog


void Character :: SetFogStart(int new_value)
{
  fog_start = new_value;
}  // SetFogStart


void Character :: IncreaseFogStart()
{
  if (fog_start - fog_end > 25)
  {
    fog_start += 25;
    printf("Fog start increased to %d.\n", fog_start);
  }  // if statement
  else
    printf("Cannot increase fog start past fog endpoint.\n");
}  // IncreaseFogStart


void Character :: DecreaseFogStart()
{
  fog_start -= 25;
  printf("Fog start decreased to %d.\n", fog_start);
}  // DecreaseFogStart


void Character :: SetFogEnd(int new_value)
{
  fog_end = new_value;
}  // SetFogEnd


void Character :: IncreaseFogEnd()
{
  fog_end += 25;
  printf("Fog end increased to %d.\n", fog_end);
}  // IncreaseFogEnd


void Character :: DecreaseFogEnd()
{
  if (fog_start - fog_end > 25)
  {
    fog_end -= 25;
    printf("Fog end decreased to %d.\n", fog_end);
  }  // if statement
  else
    printf("Cannot decrease fog end past fog startpoint.\n");
}  // DecreaseFogEnd



// ********** Protected ********** //
Character :: Character()
{
  rotate_speed = 0.0f;
  rotate_speed_old = 0.0f;
  fog = false;
  fog_start = -1500;
  fog_end = 1500;
}  // Character
