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
#include "../Controls/CameraControls.h"


namespace
{
	Camera* camera_instance = NULL;
}  // namespace


Camera* Camera :: ControlInstance()
{
	if (camera_instance == NULL)		// check if it is the first call
		camera_instance = new Camera();	// create single instance

	return camera_instance;				// address of single instance
}  // ControlInstance


Camera :: Camera()
{
	switching_views = false;
	first_person = false;
	temp_y = 0;
	temp_x = 0;
	camera_position_x = 0;
	camera_position_y = 0;
	camera_target_x = 0;
	camera_target_y = 0;
	camera_target_z = 0;
	depth = 500;
}  // Camera


void Camera :: ToggleView()
{
	if (first_person)
	{
		switching_views = true;

		if (camera_position_x < 0)
			camera_position_x++;
		else
			camera_position_x--;

		if (camera_position_y < 0)
			camera_position_y++;
		else
			camera_position_y--;

		if (camera_target_x < 0)
			camera_target_x++;
		else
			camera_target_x--;

		if (camera_target_y < 0)
			camera_target_y++;
		else
			camera_target_y--;

		if (camera_target_z < 0)
			camera_target_z++;
		else
			camera_target_z--;

		if (depth < 500)
			depth++;
		else
			depth--;

		if (camera_position_x == 0 && camera_position_y == 0 && camera_target_x == 0 &&
			camera_target_y == 0 && camera_target_z == 0 && depth == 500)
		{
			first_person = !first_person;
			switching_views = false;
		}  // if statement
	}  // if statement
	else
	{
		switching_views = true;

		if (camera_position_x < 0)
			camera_position_x++;
		else
			camera_position_x--;

		if (camera_position_y < 80)
			camera_position_y++;
		else
			camera_position_y--;

		if (camera_target_x < 0)
			camera_target_x++;
		else
			camera_target_x--;

		if (camera_target_y < 0)
			camera_target_y++;
		else
			camera_target_y--;

		if (camera_target_z < 500)
			camera_target_z++;
		else
			camera_target_z--;

		if (depth < 20)
			depth++;
		else
			depth--;

		if (camera_position_x == 0 && camera_position_y == 80 && camera_target_x == 0 &&
			camera_target_y == 0 && camera_target_z == 500 && depth == 20)
		{
			first_person = !first_person;
			switching_views = false;
		}  // if statement
	}  // else statement
}  // ToggleView


bool Camera :: IsFirstPerson()
{
	return first_person;
}  // IsFirstPerson