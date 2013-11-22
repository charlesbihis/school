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
#include "Decepticon.h"


void Decepticon :: DrawTorso()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(0.0, 0.0, 0.8, 1.0, 0.0, 0.0, 0.5, 1.0);

	glBegin(display_mode);			// torso back face
		glVertex3f(-32.5, 0, -12.5);			// no normal needed (not visible - hidden behind 'torso back raised face')
		glVertex3f(32.5, 0, -12.5);
		glVertex3f(27.5, -20, -7.5);
		glVertex3f(-27.5, -20, -7.5);
	glEnd();

	glBegin(display_mode);			// torso front face
		glVertex3f(-32.5, 0, 12.5);			// no normal needed (not visible - hidden behind 'torso front raised face')
		glVertex3f(32.5, 0, 12.5);
		glVertex3f(27.5, -20, 7.5);
		glVertex3f(-27.5, -20, 7.5);
	glEnd();

	glBegin(display_mode);			// torso back raised face
		CalculateNormal(50, 0, 0, 55, -20, 5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-27.5, 0, -15);
		glVertex3f(27.5, 0, -15);
		glVertex3f(22.5, -20, -10);
		glVertex3f(-22.5, -20, -10);
	glEnd();

	glBegin(display_mode);			// torso front raised face
		CalculateNormal(55, -20, -5, 50, 0, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-27.5, 0, 15);
		glVertex3f(27.5, 0, 15);
		glVertex3f(22.5, -20, 10);
		glVertex3f(-22.5, -20, 10);
	glEnd();

	glBegin(display_mode);			// torso back left edge
		CalculateNormal(0, -20, 7.5, -5, 0, 2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-27.5, 0, -15);
		glVertex3f(-32.5, 0, -12.5);
		glVertex3f(-27.5, -20, -7.5);
		glVertex3f(-22.5, -20, -10);
	glEnd();

	glBegin(display_mode);			// torso front left edge
		CalculateNormal(-5, 0, -2.5, 0, -20, -7.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-27.5, 0, 15);
		glVertex3f(-32.5, 0, 12.5);
		glVertex3f(-27.5, -20, 7.5);
		glVertex3f(-22.5, -20, 10);
	glEnd();

	glBegin(display_mode);			// torso back right edge
		CalculateNormal(5, 0, 2.5, 0, -20, 7.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(27.5, 0, -15);
		glVertex3f(32.5, 0, -12.5);
		glVertex3f(27.5, -20, -7.5);
		glVertex3f(22.5, -20, -10);
	glEnd();

	glBegin(display_mode);			// torso front right edge
		CalculateNormal(0, -20, -7.5, 5, 0, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(27.5, 0, 15);
		glVertex3f(32.5, 0, 12.5);
		glVertex3f(27.5, -20, 7.5);
		glVertex3f(22.5, -20, 10);
	glEnd();

	glBegin(display_mode);			// torso left face
		CalculateNormal(5, -20, 5, 0, 0, 25);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-32.5, 0, -12.5);
		glVertex3f(-32.5, 0, 12.5);
		glVertex3f(-27.5, -20, 7.5);
		glVertex3f(-27.5, -20, -7.5);
	glEnd();

	glBegin(display_mode);			// torso right face
		CalculateNormal(0, 0, 25, -5, -20, 5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(32.5, 0, -12.5);
		glVertex3f(32.5, 0, 12.5);
		glVertex3f(27.5, -20, 7.5);
		glVertex3f(27.5, -20, -7.5);
	glEnd();

	ChangeColor(0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.8, 1.0);
}  // DrawTorso


void Decepticon :: SetTorsoLength(int new_value)
{
	torso_length = new_value;
}  // SetTorsoLength
