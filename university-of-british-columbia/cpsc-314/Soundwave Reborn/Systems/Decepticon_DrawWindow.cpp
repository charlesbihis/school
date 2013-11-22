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


void Decepticon :: DrawWindow()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	GLfloat mat_transparent[] = {0.5, 0.5, 0.5, 0.5};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	glDepthMask (GL_TRUE);

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);				// window
		glNormal3f(0, 0, 1);
		glVertex3f(-30, 30, 0.1);
		glVertex3f(-30, 5, 0.1);
		glVertex3f(-27.5, 2.5, 0.1);
		glVertex3f(27.5, 2.5, 0.1);
		glVertex3f(30, 5, 0.1);
		glVertex3f(30, 30, 0.1);
	glEnd();

	glDisable (GL_BLEND);
	ChangeColor(1.0, 1.0, 0.0, 1.0, 0.8, 0.8, 0.0, 1.0);

	glBegin(display_mode);				// bottom left window face
		glNormal3f(0, 0, 1);
		glVertex3f(-32.5, 2.5, 2.5);
		glVertex3f(-30, 5, 2.5);
		glVertex3f(-27.5, 2.5, 2.5);
		glVertex3f(-30, 0, 2.5);
	glEnd();

	glBegin(display_mode);				// bottom right window face
		glNormal3f(0, 0, 1);
		glVertex3f(32.5, 2.5, 2.5);
		glVertex3f(30, 5, 2.5);
		glVertex3f(27.5, 2.5, 2.5);
		glVertex3f(30, 0, 2.5);
	glEnd();

	glBegin(display_mode);				// bottom window face
		glNormal3f(0, 0, 1);
		glVertex3f(-30, 0, 2.5);
		glVertex3f(30, 0, 2.5);
		glVertex3f(27.5, 2.5, 2.5);
		glVertex3f(-27.5, 2.5, 2.5);
	glEnd();

	glBegin(display_mode);				// top window face
		glNormal3f(0, 0, 1);
		glVertex3f(-32.5, 32.5, 2.5);
		glVertex3f(-30, 30, 2.5);
		glVertex3f(30, 30, 2.5);
		glVertex3f(32.5, 32.5, 2.5);
	glEnd();

	glBegin(display_mode);				// left window face
		glVertex3f(-32.5, 2.5, 2.5);
		glVertex3f(-32.5, 32.5, 2.5);
		glVertex3f(-30, 30, 2.5);
		glVertex3f(-30, 5, 2.5);
	glEnd();

	glBegin(display_mode);				// right window face
		glNormal3f(0, 0, 1);
		glVertex3f(32.5, 2.5, 2.5);
		glVertex3f(32.5, 32.5, 2.5);
		glVertex3f(30, 30, 2.5);
		glVertex3f(30, 5, 2.5);
	glEnd();

	glBegin(display_mode);					// bottom left outer rise
		CalculateNormal(2.5, -2.5, -2.5, 2.5, -2.5, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-32.5, 2.5, 2.5);
		glVertex3f(-30, 0, 2.5);
		glVertex3f(-30, 0, 0);
		glVertex3f(-32.5, 2.5, 0);
	glEnd();

	glBegin(display_mode);					// bottom right outer rise
		CalculateNormal(-2.5, -2.5, 0, -2.5, -2.5, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(32.5, 2.5, 2.5);
		glVertex3f(30, 0, 2.5);
		glVertex3f(30, 0, 0);
		glVertex3f(32.5, 2.5, 0);
	glEnd();

	glBegin(display_mode);					// bottom left inner rise
		CalculateNormal(2.5, -2.5, 0, 2.5, -2.5, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-30, 5, 2.5);
		glVertex3f(-27.5, 2.5, 2.5);
		glVertex3f(-27.5, 2.5, 0);
		glVertex3f(-30, 5, 0);
	glEnd();

	glBegin(display_mode);					// bottom right inner rise
		CalculateNormal(-2.5, -2.5, -2.5, -2.5, -2.5, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(30, 5, 2.5);
		glVertex3f(27.5, 2.5, 2.5);
		glVertex3f(27.5, 2.5, 0);
		glVertex3f(30, 5, 0);
	glEnd();

	glBegin(display_mode);					// left outer rise
		glNormal3f(-1, 0, 0);
		glVertex3f(-32.5, 2.5, 2.5);
		glVertex3f(-32.5, 32.5, 2.5);
		glVertex3f(-32.5, 32.5, 0);
		glVertex3f(-32.5, 2.5, 0);
	glEnd();

	glBegin(display_mode);					// right outer rise
		glNormal3f(1, 0, 0);
		glVertex3f(32.5, 2.5, 2.5);
		glVertex3f(32.5, 32.5, 2.5);
		glVertex3f(32.5, 32.5, 0);
		glVertex3f(32.5, 2.5, 0);
	glEnd();

	glBegin(display_mode);					// left inner rise
		glNormal3f(1, 0, 0);
		glVertex3f(-30, 5, 2.5);
		glVertex3f(-30, 30, 2.5);
		glVertex3f(-30, 30, 0);
		glVertex3f(-30, 5, 0);
	glEnd();

	glBegin(display_mode);					// right inner rise
		glNormal3f(-1, 0, 0);
		glVertex3f(30, 5, 2.5);
		glVertex3f(30, 30, 2.5);
		glVertex3f(30, 30, 0);
		glVertex3f(30, 5, 0);
	glEnd();

	glBegin(display_mode);					// upper outer rise
		glNormal3f(0, 1, 0);
		glVertex3f(-32.5, 32.5, 2.5);
		glVertex3f(32.5, 32.5, 2.5);
		glVertex3f(32.5, 32.5, 0);
		glVertex3f(-32.5, 32.5, 0);
	glEnd();

	glBegin(display_mode);					// upper inner rise
		glNormal3f(0, -1, 0);
		glVertex3f(-30, 30, 2.5);
		glVertex3f(30, 30, 2.5);
		glVertex3f(30, 30, 0);
		glVertex3f(-30, 30, 0);
	glEnd();

	glBegin(display_mode);					// lower inner rise
		glNormal3f(0, 1, 0);
		glVertex3f(-27.5, 2.5, 2.5);
		glVertex3f(27.5, 2.5, 2.5);
		glVertex3f(27.5, 2.5, 0);
		glVertex3f(-27.5, 2.5, 0);
	glEnd();

	glBegin(display_mode);					// lower outer rise
		glNormal3f(0, -1, 0);
		glVertex3f(-30, 0, 2.5);
		glVertex3f(30, 0, 2.5);
		glVertex3f(30, 0, 0);
		glVertex3f(-30, 0, 0);
	glEnd();
}  // DrawWindow
