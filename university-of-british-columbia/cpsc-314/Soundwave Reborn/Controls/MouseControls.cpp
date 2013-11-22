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
		mouse_instance = new Mouse();	// create single instance

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

	if (camera_controller->IsFirstPerson())
		camera_controller->camera_target_x = (x - camera_controller->temp_x - WINDOW_WIDTH / 2) / -0.75;
	else
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
