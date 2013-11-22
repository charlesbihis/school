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


void Decepticon :: DrawRewind()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// rewind button face
		glNormal3f(0, 0, 1);
		glVertex3f(-15, 7.5, 2.5);
		glVertex3f(-15, -7.5, 2.5);
		glVertex3f(-27.5, 0, 2.5);
	glEnd();

	glBegin(display_mode);			// rewind button right edge
		glNormal3f(1, 0, 0);
		glVertex3f(-15, 7.5, 2.5);
		glVertex3f(-15, -7.5, 2.5);
		glVertex3f(-15, -7.5, 0);
		glVertex3f(-15, 7.5, 0);
	glEnd();

	glBegin(display_mode);			// rewind top left edge
		CalculateNormal(-12.5, -7.5, -2.5, -12.5, -7.5, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-15, 7.5, 2.5);
		glVertex3f(-27.5, 0, 2.5);
		glVertex3f(-27.5, 0, 0);
		glVertex3f(-15, 7.5, 0);
	glEnd();

	glBegin(display_mode);			// rewind bottom left edge
		CalculateNormal(-12.5, 7.5, 0, -12.5, 7.5, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(-15, -7.5, 2.5);
		glVertex3f(-27.5, 0, 2.5);
		glVertex3f(-27.5, 0, 0);
		glVertex3f(-15, -7.5, 0);
	glEnd();
}  // DrawRewind


void Decepticon :: DrawFastForward()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// fastforward button face
		glNormal3f(0, 0, 1);
		glVertex3f(15, 7.5, 2.5);
		glVertex3f(15, -7.5, 2.5);
		glVertex3f(27.5, 0, 2.5);
	glEnd();

	glBegin(display_mode);			// fastforward button left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(15, 7.5, 2.5);
		glVertex3f(15, -7.5, 2.5);
		glVertex3f(15, -7.5, 0);
		glVertex3f(15, 7.5, 0);
	glEnd();

	glBegin(display_mode);			// fastforward button top right edge
		CalculateNormal(12.5, -7.5, 0, 12.5, -7.5, -2.5);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(15, 7.5, 2.5);
		glVertex3f(27.5, 0, 2.5);
		glVertex3f(27.5, 0, 0);
		glVertex3f(15, 7.5, 0);
	glEnd();

	glBegin(display_mode);			// fastforward button bottom right edge
		CalculateNormal(12.5, 7.5, -2.5, 12.5, 7.5, 0);
		glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
		glVertex3f(15, -7.5, 2.5);
		glVertex3f(27.5, 0, 2.5);
		glVertex3f(27.5, 0, 0);
		glVertex3f(15, -7.5, 0);
	glEnd();
}  // DrawFastForward


void Decepticon :: DrawPlay()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// play button face
		glNormal3f(0, 0, 1);
		glVertex3f(-12.5, 1.5, 2.5);
		glVertex3f(-12.5, 7.5, 2.5);
		glVertex3f(12.5, 7.5, 2.5);
		glVertex3f(12.5, 1.5, 2.5);
	glEnd();

	glBegin(display_mode);			// play button left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(-12.5, 1.5, 2.5);
		glVertex3f(-12.5, 7.5, 2.5);
		glVertex3f(-12.5, 7.5, 0);
		glVertex3f(-12.5, 1.5, 0);
	glEnd();

	glBegin(display_mode);			// play button right edge
		glNormal3f(1, 0, 0);
		glVertex3f(12.5, 1.5, 2.5);
		glVertex3f(12.5, 7.5, 2.5);
		glVertex3f(12.5, 7.5, 0);
		glVertex3f(12.5, 1.5, 0);
	glEnd();

	glBegin(display_mode);			// play button top edge
		glNormal3f(0, 1, 0);
		glVertex3f(-12.5, 7.5, 2.5);
		glVertex3f(12.5, 7.5, 2.5);
		glVertex3f(12.5, 7.5, 0);
		glVertex3f(-12.5, 7.5, 0);
	glEnd();

	glBegin(display_mode);			// play button bottom edge
		glNormal3f(0, -1, 0);
		glVertex3f(-12.5, 2.5, 2.5);
		glVertex3f(12.5, 2.5, 2.5);
		glVertex3f(12.5, 2.5, 0);
		glVertex3f(-12.5, 2.5, 0);
	glEnd();
}  // DrawPlay


void Decepticon :: DrawStop()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// stop button face
		glNormal3f(0, 0, 1);
		glVertex3f(-12.5, -1.5, 2.5);
		glVertex3f(-12.5, -7.5, 2.5);
		glVertex3f(-1.5, -7.5, 2.5);
		glVertex3f(-1.5, -1.5, 2.5);
	glEnd();

	glBegin(display_mode);			// stop button left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(-12.5, -1.5, 2.5);
		glVertex3f(-12.5, -7.5, 2.5);
		glVertex3f(-12.5, -7.5, 0);
		glVertex3f(-12.5, -1.5, 0);
	glEnd();

	glBegin(display_mode);			// stop button right edge
		glNormal3f(1, 0, 0);
		glVertex3f(-1.5, -1.5, 2.5);
		glVertex3f(-1.5, -7.5, 2.5);
		glVertex3f(-1.5, -7.5, 0);
		glVertex3f(-1.5, -1.5, 0);
	glEnd();

	glBegin(display_mode);			// stop button bottom edge
		glNormal3f(0, -1, 0);
		glVertex3f(-12.5, -7.5, 2.5);
		glVertex3f(-1.5, -7.5, 2.5);
		glVertex3f(-1.5, -7.5, 0);
		glVertex3f(-12.5, -7.5, 0);
	glEnd();

	glBegin(display_mode);			// stop button top edge
		glNormal3f(0, 1, 0);
		glVertex3f(-12.5, -1.5, 2.5);
		glVertex3f(-1.5, -1.5, 2.5);
		glVertex3f(-1.5, -1.5, 0);
		glVertex3f(-12.5, -1.5, 0);
	glEnd();
}  // DrawStop


void Decepticon :: DrawPause()
{
	if (anti_aliasing)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth (1.5);
	}  // if statement

	ChangeColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	glBegin(display_mode);			// pause button face
		glNormal3f(0, 0, 1);
		glVertex3f(12.5, -1.5, 2.5);
		glVertex3f(12.5, -7.5, 2.5);
		glVertex3f(1.5, -7.5, 2.5);
		glVertex3f(1.5, -1.5, 2.5);
	glEnd();

	glBegin(display_mode);			// pause button right edge
		glNormal3f(1, 0, 0);
		glVertex3f(12.5, -1.5, 2.5);
		glVertex3f(12.5, -7.5, 2.5);
		glVertex3f(12.5, -7.5, 0);
		glVertex3f(12.5, -1.5, 0);
	glEnd();

	glBegin(display_mode);			// pause button left edge
		glNormal3f(-1, 0, 0);
		glVertex3f(1.5, -1.5, 2.5);
		glVertex3f(1.5, -7.5, 2.5);
		glVertex3f(1.5, -7.5, 0);
		glVertex3f(1.5, -1.5, 0);
	glEnd();

	glBegin(display_mode);			// pause button bottom edge
		glNormal3f(0, -1, 0);
		glVertex3f(12.5, -7.5, 2.5);
		glVertex3f(1.5, -7.5, 2.5);
		glVertex3f(1.5, -7.5, 0);
		glVertex3f(12.5, -7.5, 0);
	glEnd();

	glBegin(display_mode);			// pause button top edge
		glNormal3f(0, 1, 0);
		glVertex3f(12.5, -1.5, 2.5);
		glVertex3f(1.5, -1.5, 2.5);
		glVertex3f(1.5, -1.5, 0);
		glVertex3f(12.5, -1.5, 0);
	glEnd();

	//GLfloat mat_ambient[] = {0.0, 0.0, 1.0, 1.0};
	//GLfloat mat_diffuse[] = {0.0, 0.0, 0.8, 1.0};
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}  // DrawPause
