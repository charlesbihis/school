#include <windows.h>
#include <stdio.h>
#include <gl\glut.h>
#include <math.h>
#include "Decepticon/Decepticon.h"
#include "Scene/Scene.h"
#include "MouseControls/MouseControls.h"
#include "KeyboardControls/KeyboardControls.h"
#include "CharacterControls/CharacterControls.h"
#include "CameraControls/CameraControls.h"
#include "Skybox/Skybox.h"
#include "Skybox/jpeglib.h"
#include "ParticleSystem/particles.h"



// *** Function Declarations *** //
void PrintHello();
void PrintHelp();
void Init(void);
void DisplayWindow(void);
void IdleWindow();
void ReshapeWindow(int w, int h);
void KeyListener(unsigned char key, int x, int y);
void SpecialKeyListener(int key, int x, int y);
void MouseListener(int button, int state, int x, int y);
void MotionListener(int x, int y);


// *** Constants *** //
#define MINIMUM_ZOOM 1.0
#define SKYBOX_MAX_TEXTURES 6
#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5


// *** Globals *** //
ParticleSystem *particleSystem;
Decepticon Soundwave;
Scene Cybertron;
Character *character_controller = Character :: ControlInstance();
Camera *camera_controller = Camera :: ControlInstance();
float angle = 0;
float depth = 300;
//float depth = 2500;
float zoom_multiplier = 0.25;		// the lower, the faster the zoom
int mouse_mode = 0;
int mouse_state = 0;
static int motion_x = 0;
static int motion_y = 0;
static int motion_temp_x = 0;
static int motion_temp_y = 0;
static int temp_y = 0;
static int temp_x = 0;
static int camera_position_x = 0;
static int camera_position_y = 0;
static int camera_target_x = 0;
static int camera_target_y = 0;
bool inverted = false;
unsigned int skybox_textures[SKYBOX_MAX_TEXTURES];

int main(int argc, char **argv)
{
  int windowsize_width = 700,
	  windowsize_height = 700,
	  windowposition_width = 0,
	  windowposition_height = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowsize_width, windowsize_height);
  glutInitWindowPosition(windowposition_width, windowposition_height);
  glutCreateWindow("Soundwave Reborn...");

  PrintHello();
  PrintHelp();
  Init();
  glutDisplayFunc(DisplayWindow);
  glutIdleFunc(IdleWindow);
  glutReshapeFunc(ReshapeWindow);
  glutKeyboardFunc(KeyListener);
  glutSpecialFunc(SpecialKeyListener);
  glutMouseFunc(MouseListener);
  glutPassiveMotionFunc(MotionListener);
  
  glutMainLoop();
  return 0; 
}


void PrintHello()
{
  printf ("***********************************************\n");
  printf ("**                 Soundwave                 **\n");
  printf ("***********************************************\n\n\n");
}  // PrintHello


void PrintHelp()
{
  printf("\n\n*** Help ***\n\n");
  printf("  mouse left click....control rotation\n");
  printf("  mouse right click...control zoom\n");
  printf("  space bar...........pause or resume animation\n");
  printf("  left arrow..........move camera left\n");
  printf("  right arrow.........move camera right\n");
  printf("  up arrow............move camera up\n");
  printf("  down arrow..........move camera down\n");
  printf("  page up.............increase rotate right speed\n");
  printf("  page down...........increase rotate left speed\n");
  printf("  home................view front\n");
  printf("  end.................view back\n");
  printf("  insert..............view right side\n");
  printf("  delete..............view left side\n");
  printf("  F1 key..............toggle wire frame\n");
  printf("  F2 key..............toggle anti-aliasing\n");
  printf("  'h'.................view help screen\n");
  printf("  ESC key.............quit\n\n");
}  // PrintHelp


void Init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.25);

  GLfloat light_position[] = {0.0, 50.0, 100.0, 0.0};
  GLfloat white_light[] = {0.35, 0.35, 0.35, 0.2};
  //GLfloat lmodel_ambient[] = {0.85, 0.85, 0.85, 1.0};
  GLfloat lmodel_ambient[] = {0.05, 0.05, 0.05, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LINE_SMOOTH);
  particleSystem = new ParticleSystem(400, 0.75, 0.000001, 0.000004, 0, 0, -0.02, 0);

  //NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

  //glEnable(GL_TEXTURE_2D);

  // Load the Skybox textures
  //JPEG_Skybox(skybox_textures,"front.jpg",  SKYFRONT);
  //JPEG_Skybox(skybox_textures,"back.jpg",   SKYBACK);
  //JPEG_Skybox(skybox_textures,"left.jpg",   SKYLEFT);
  //JPEG_Skybox(skybox_textures,"right.jpg",  SKYRIGHT);
  //JPEG_Skybox(skybox_textures,"up.jpg",     SKYUP);
  //JPEG_Skybox(skybox_textures,"down.jpg",   SKYDOWN);
}  // Init


void DisplayWindow(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// simultaneous clears are faster
  glColor3f(1.0, 1.0, 1.0);								// draw in white
  glLoadIdentity();

  //if (mouse_mode == GLUT_RIGHT_BUTTON && mouse_state == GLUT_DOWN)
  //{
  //  gluLookAt(camera_target_x, camera_target_y, depth,	// set camera back 'depth' units along the z-axis
	 //         camera_target_x, camera_target_y, 0,			// point camera at coordinates (camera_x, camera_y)
		//	  0.0, 1.0, 0.0);									// set positive on the y-axis as the up-vector
  //  camera_position_x = camera_target_x;
  //  camera_position_y = camera_target_y;
  //}
  //else
  /*
    gluLookAt(camera_position_x, camera_position_y, depth,	// set camera back 'depth' units along the z-axis
	          camera_target_x, camera_target_y, 0,			// point camera at coordinates (camera_x, camera_y)
	          0.0, 1.0, 0.0);									// set positive on the y-axis as the up-vector
  */

  gluLookAt(camera_controller->mPos.x,  camera_controller->mPos.y,  camera_controller->mPos.z,	
	  camera_controller->mView.x, camera_controller->mView.y, camera_controller->mView.z,	
	  camera_controller->mUp.x,   camera_controller->mUp.y,   camera_controller->mUp.z);


  /*
  glRotatef(camera_target_x / 4, 0, 1, 0);//////////////////////////////////////
  glRotatef(camera_target_y / -4, 1, 0, 0);////////////////////////////////////
  
  gluLookAt(0, 0, 1,	// set camera back 'depth' units along the z-axis
	  0, 0, 0,			// point camera at coordinates (camera_x, camera_y)
	  0.0, 1.0, 0.0);									// set positive on the y-axis as the up-vector
  */

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  glRotatef(angle, 0, 1, 0);								// allow rotate by 'angle' degrees with PAGE_UP and PAGE_DOWN
  //Draw_Skybox(0, 0, 0, 10000, 10000, 10000);	// Draw the Skybox
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);


  glPushMatrix();
    Soundwave.Draw();										// draw Soundwave
	glTranslatef(52.5, 50, 16);
	glDisable(GL_LIGHTING);
	particleSystem->DrawParticles();						// draw sparks
	glEnable(GL_LIGHTING);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, -217.5, 0);
    Cybertron.Draw();										// draw Cybertron Lab
  glPopMatrix();

  glutSwapBuffers();										// glutSwapBuffers() used for double buffers
}  // DisplayWindow


void IdleWindow()
{
  angle += character_controller->GetRotateSpeed();
  glutPostRedisplay();
  //DisplayWindow();
}


void ReshapeWindow(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);		// adjust pixel rectangle for drawing to be entire new window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 0.1, 50000.0);			// set perspectives for projection matrix (fovy = 60, aspec = 1.0, z-near = 0.1, z-far = 10000)
  glMatrixMode(GL_MODELVIEW);

  camera_controller->mWindowWidth = w;
  camera_controller->mWindowHeight = h;
}  // ReshapeWindow


void KeyListener(unsigned char key, int x, int y)
{
  switch(key) 
  {
    case 27:										// escape key
	  exit(0);
      break;
	case 'h':
	  PrintHelp();
	  break;
    case ' ':
      character_controller->PauseRotation();
	  break;
	case 'c':
	  character_controller->Reset();
	  Soundwave.Reset();
	  break;
	case 's':
	  Soundwave.RotateRightShoulderForward();
	  break;
	case 'S':
	  Soundwave.RotateRightShoulderBackward();
	  break;
	case 'd':
      particleSystem->Update();
      Soundwave.RotateLeftShoulderForward();
	  break;
	case 'D':
      particleSystem->Update();
	  Soundwave.RotateLeftShoulderBackward();
	  break;
	case 'z':
      Soundwave.TwistRightShoulderOutward();
	  break;
	case 'Z':
      Soundwave.TwistRightShoulderInward();
	  break;
	case 'x':
	  Soundwave.TwistLeftShoulderOutward();
	  break;
	case 'X':
	  Soundwave.TwistLeftShoulderInward();
	  break;
	case 'a':
      Soundwave.RaiseRightShoulder();
	  break;
	case 'A':
      Soundwave.LowerRightShoulder();
	  break;
	case 'f':
      Soundwave.RaiseLeftShoulder();
	  break;
	case 'F':
      Soundwave.LowerLeftShoulder();
	  break;
	case 'e':
      Soundwave.RaiseRightHand();
	  break;
	case 'E':
      Soundwave.LowerRightHand();
	  break;
	case 'r':
      Soundwave.RaiseLeftHand();
	  break;
	case 'R':
	  Soundwave.LowerLeftHand();
	  break;
	case 't':
      Soundwave.OpenWindow();
	  break;
	case 'T':
	  Soundwave.CloseWindow();
      break;
	case 'k':
      Soundwave.RaiseRightLeg();
	  break;
	case 'K':
	  Soundwave.LowerRightLeg();
	  break;
	case 'l':
      Soundwave.RaiseLeftLeg();
	  break;
	case 'L':
      Soundwave.LowerLeftLeg();
	  break;
	case 'j':
      Soundwave.RaiseRightLegOutward();
	  break;
	case 'J':
      Soundwave.LowerRightLegInward();
	  break;
	case ';':
      Soundwave.RaiseLeftLegOutward();
	  break;
	case ':':
	  Soundwave.LowerLeftLegInward();
	  break;
	case ',':
      Soundwave.BendRightKnee();
	  break;
	case '<':
      Soundwave.StraightenRightKnee();
	  break;
	case '.':
      Soundwave.BendLeftKnee();
	  break;
	case '>':
      Soundwave.StraightenLeftKnee();
	  break;
	case 'i':
      Soundwave.TwistRightLegOutward();
	  break;
	case 'I':
      Soundwave.TwistRightLegInward();
	  break;
	case 'o':
      Soundwave.TwistLeftLegOutward();
	  break;
	case 'O':
      Soundwave.TwistLeftLegInward();
	  break;
	case 'm':
	  Soundwave.RaiseRightFoot();
	  break;
	case 'M':
      Soundwave.LowerRightFoot();
	  break;
	case '/':
	  Soundwave.RaiseLeftFoot();
	  break;
	case '?':
      Soundwave.LowerLeftFoot();
	  break;
	case 'b':
      Soundwave.LeanForward();
	  break;
	case 'B':
      Soundwave.LeanBackward();
	  break;
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
    case '`':
	  Soundwave.Transform();
	  break;
	case '~':
	  Soundwave.Backflip();
	  break;
	default:
		printf("A key is pressed: %c\n", key);
      break;
    }  // switch statement
}


void SpecialKeyListener(int key, int x, int y)
{
  switch(key)
  {
	case GLUT_KEY_RIGHT:
	  //camera_position_x += 20;
	  //camera_target_x += 20;
      camera_controller->Rotate_View(0, CAMERASPEED, 0);
	  printf("Moving camera right.\n");
	  break;
	case GLUT_KEY_LEFT:
	  //camera_position_x -= 20;
	  //camera_target_x -= 20;
      camera_controller->Rotate_View(0, -CAMERASPEED, 0);
	  printf ("Moving camera left.\n");
	  break;
	case GLUT_KEY_DOWN:
	  //depth += 20;
      camera_controller->Move_Camera(-CAMERASPEED);
	  printf ("Moving camera down.\n");
	  break;
	case GLUT_KEY_UP:
	  //depth -= 20;
      camera_controller->Move_Camera(CAMERASPEED);
	  printf ("Moving camera up.\n");
	  break;
	case GLUT_KEY_F1:
      Soundwave.ToggleDisplayMode();
	  break;
	case GLUT_KEY_F2:
	  Soundwave.ToggleAntiAliasing();
	  break;
	case GLUT_KEY_F3:
	  character_controller->ToggleFog();
	  break;
	case GLUT_KEY_F5:
	  inverted = !inverted;
	  printf("Inverted look toggled %d.\n", inverted);
	  break;
	case GLUT_KEY_PAGE_UP:
      character_controller->IncreaseRotateSpeed();
	  break;
	case GLUT_KEY_PAGE_DOWN:
      character_controller->DecreaseRotateSpeed();
	  break;
	default:
	  printf("A special key is pressed: %c\n", key);
	  break;
  }  // switch statement
}  // ArrowListener


void MouseListener(int button, int state, int x, int y)
{
  mouse_mode = button;

  mouse_state = state;

  if (button == GLUT_LEFT_BUTTON)
  {
    if (inverted)
	  temp_y = y - 0.2 * camera_target_y;
	else
      temp_y = y + 0.2 * camera_target_y;

    temp_x = x - 0.2 * camera_target_x;
  }  // if statement
  else if (button == GLUT_RIGHT_BUTTON)
    temp_y = y - zoom_multiplier * depth;
}  // MouseListener


void MotionListener(int x, int y)
{
  camera_controller->Mouse_Move();

  if (mouse_mode == GLUT_LEFT_BUTTON)				// rotate camera about viewpoint
  {
    if (inverted)
      camera_target_y = (y - temp_y) / 0.2;			// restrict rotation of viewpoint about y-axis to avoid viewing through floor
	else
      camera_target_y = (y - temp_y) / -0.2;		// restrict rotation of viewpoint about y-axis to avoid viewing through floor
    
	camera_target_x = (x - temp_x) / 0.2;			// rotate about x-axis

	glutPostRedisplay();
  }  // if statement
  if (mouse_mode == GLUT_RIGHT_BUTTON)		// zoom
  {
    depth = (y - temp_y) / zoom_multiplier;
    if (depth < MINIMUM_ZOOM)
       depth = MINIMUM_ZOOM;

	glutPostRedisplay();
  }  // else if statement
}  // MotionListener


void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, skybox_textures[SKYFRONT]);
	glBegin(GL_QUADS);	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, skybox_textures[SKYBACK]);
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, skybox_textures[SKYLEFT]);
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, skybox_textures[SKYRIGHT]);
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, skybox_textures[SKYUP]);
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, skybox_textures
		[SKYDOWN]);
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();

}

