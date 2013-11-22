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



#include <windows.h>
#include <stdio.h>
#include <gl\glut.h>
#include <math.h>

#include "Controls/CameraControls.h"
#include "Controls/CharacterControls.h"
#include "Controls/KeyboardControls.h"
#include "Controls/MouseControls.h"

#include "Systems/Decepticon.h"
#include "Systems/Scene.h"
#include "Systems/Particle.h"

#include "Tools/Skybox.h"
#include "Tools/jpeglib.h"


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
#define SKYBOX_MAX_TEXTURES 6
#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK 1						// Give Back  ID = 1
#define SKYLEFT 2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP 4							// Give Up    ID = 4
#define SKYDOWN 5						// Give Down  ID = 5
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700


// *** Globals *** //
Decepticon *soundwave = Decepticon :: SystemInstance();
Camera *camera_controller = Camera :: ControlInstance();
Character *character_controller = Character :: ControlInstance();
Keyboard *keyboard_controller = Keyboard :: ControlInstance();
Mouse *mouse_controller = Mouse :: ControlInstance();
Scene *cybertron = Scene :: ControlInstance();

ParticleSystem *sparks_big;
ParticleSystem *sparks_small;
ParticleSystem *smoke_big;
ParticleSystem *smoke_small;

float angle = 0;


int main(int argc, char **argv)
{
	int windowsize_width = WINDOW_WIDTH,
		windowsize_height = WINDOW_HEIGHT,
		windowposition_width = 0,
		windowposition_height = 0;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowsize_width, windowsize_height);
	glutInitWindowPosition(windowposition_width, windowposition_height);
	glutCreateWindow("Soundwave Reborn...");

	PrintHello();
	keyboard_controller->PrintBasicHelp();
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
}  // main


void PrintHello()
{
	printf("********************************************\n");
	printf("**            Soundwave Reborn            **\n");
	printf("********************************************\n\n");
}  // PrintHello


void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.25);

	GLfloat light_position[] = {0.0, 50.0, 100.0, 0.0};
	GLfloat white_light[] = {0.35, 0.35, 0.35, 0.2};
	GLfloat lmodel_ambient[] = {0.15, 0.15, 0.15, 1.0};

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
	sparks_big = new ParticleSystem(50, 0.58, 50, 0.000001, 0.000004, 0, 0, -0.02, 0, 0.75, 0.75, 0);
	sparks_small = new ParticleSystem(20, 0.23, 30, 0.000001, 0.000004, 0, 0, -0.02, 0, 0.75, 0.75, 0);
	smoke_big = new ParticleSystem(50, 0.58, 50, 0.00000001, 0.00000004, 0, 0, 0.02, 0, 0.75, 0.75, 0);
	smoke_small = new ParticleSystem(20, 0.23, 30, 0.00000001, 0.00000004, 0, 0, 0.02, 0, 0.75, 0.75, 0);


	glEnable(GL_TEXTURE_2D);

	// Load the Skybox textures
	JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/front.jpg", SKYFRONT);
	JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/back.jpg", SKYBACK);
	JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/left.jpg", SKYLEFT);
	JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/right.jpg", SKYRIGHT);
	JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/up.jpg", SKYUP);
	//JPEG_Skybox(cybertron->skybox_textures, "./Assets/Textures/space/down.jpg", SKYDOWN);
}  // Init


void DisplayWindow(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// simultaneous clears are faster
	glColor3f(1.0, 1.0, 1.0);								// draw in white
	glLoadIdentity();

	gluLookAt(camera_controller->camera_position_x, camera_controller->camera_position_y, camera_controller->depth,	// set camera back 'depth' units along the z-axis
			  camera_controller->camera_target_x, camera_controller->camera_target_y, camera_controller->camera_target_z,			// point camera at coordinates (camera_x, camera_y)
			  0.0, 1.0, 0.0);								// set positive on the y-axis as the up-vector

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glRotatef(angle, 0, 1, 0);								// allow rotate by 'angle' degrees with PAGE_UP and PAGE_DOWN
	cybertron->DrawSkybox(0, 0, 0, 10000, 10000, 10000);	// draw the Skybox
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPushMatrix();
		soundwave->Draw();									// draw Soundwave
		glTranslatef(40, -90, 10);
		glDisable(GL_LIGHTING);
		sparks_big->DrawParticles();						// draw sparks
		sparks_small->DrawParticles();						// draw sparks
		glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-32, 67, 42);
		//smoke_big->DrawParticles();						// draw smoke
		//smoke_small->DrawParticles();						// draw smoke
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -217.5, 0);
		cybertron->Draw();									// draw Cybertron Lab
	glPopMatrix();

	glutSwapBuffers();										// glutSwapBuffers() used for double buffers
}  // DisplayWindow


void IdleWindow()
{
	angle += character_controller->GetRotateSpeed();
	
	if (soundwave->IsTransforming())
		soundwave->Transform();

	if (camera_controller->switching_views)
		camera_controller->ToggleView();

	sparks_big->Update();
	sparks_small->Update();
	//smoke_big->Update();
	//smoke_small->Update();
	glutPostRedisplay();
  //DisplayWindow();
}


void ReshapeWindow(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);				// adjust pixel rectangle for drawing to be entire new window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 50000.0);				// set perspectives for projection matrix (fovy = 60, aspec = 1.0, z-near = 0.1, z-far = 10000)
	glMatrixMode(GL_MODELVIEW);
}  // ReshapeWindow


void KeyListener(unsigned char key, int x, int y)
{
	keyboard_controller->InterpretKey(key);
}  // KeyListener


void SpecialKeyListener(int special_key, int x, int y)
{
	keyboard_controller->InterpretSpecialKey(special_key);
}  // SpecialKeyListener


void MouseListener(int button, int state, int x, int y)
{
	mouse_controller->MouseClick(button, state, x, y);
}  // MouseListener


void MotionListener(int x, int y)
{
	mouse_controller->MouseMove(x, y);
}  // MotionListener
