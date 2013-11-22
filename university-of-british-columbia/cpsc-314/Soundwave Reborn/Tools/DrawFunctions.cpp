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

// *** Constants *** //
#define PI 3.14159265

const int NORMAL_VECTOR_SIZE = 3;
double normal_vector[NORMAL_VECTOR_SIZE];


void GetNormal(double ux, double uy, double uz, double vx, double vy, double vz)
{
	double length = 0;

	normal_vector[0] = (uy*vz - vy*uz);
	normal_vector[1] = (vx*uz - ux*vz);
	normal_vector[2] = (ux*vy - vx*uy);

	length = sqrt((normal_vector[0] * normal_vector[0]) + (normal_vector[1] * normal_vector[1]) + (normal_vector[2] * normal_vector[2]));

	normal_vector[0] = normal_vector[0] / length;
	normal_vector[1] = normal_vector[1] / length;
	normal_vector[2] = normal_vector[2] / length;
}  // GetNormal


void TaperedWireCylinder(float h, float r1, float r2, int nslices)
{
	int n;
	float dth = (2 * PI) / nslices;

	for (n = 0; n != nslices; n++)
	{
		glBegin(GL_LINE_LOOP);
			GetNormal((r2 * cos((n + 1) * dth)) - (r1 * cos(n * dth)), h, (r2 * sin((n + 1) * dth)) - (r1 * sin(n * dth)),
					 (r1 * cos((n + 1) * dth)) - (r1 * cos(n * dth)), 0, (r1 * sin((n + 1) * dth)) - (r1 * sin(n * dth)));
			glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
			glVertex3f(r1 * cos(n * dth), 0, r1 * sin(n * dth));
			glVertex3f(r1 * cos((n + 1) * dth), 0, r1 * sin((n + 1) * dth));
			glVertex3f(r2 * cos((n + 1) * dth), h, r2 * sin((n + 1) * dth));
			glVertex3f(r2 * cos(n * dth), h, r2 * sin(n * dth));
		glEnd();
	}  // for loop
}  // TaperedWireCylinder


void TaperedCylinder(float h, float r1, float r2, int nslices)
{
	int n;
	float dth = (2 * PI) / nslices;

	for (n = 0; n != nslices; n++)
	{
		glBegin(GL_POLYGON);
			GetNormal((r2 * cos((n + 1) * dth)) - (r1 * cos(n * dth)), h, (r2 * sin((n + 1) * dth)) - (r1 * sin(n * dth)),
					 (r1 * cos((n + 1) * dth)) - (r1 * cos(n * dth)), 0, (r1 * sin((n + 1) * dth)) - (r1 * sin(n * dth)));
			glNormal3f(normal_vector[0], normal_vector[1], normal_vector[2]);
			glVertex3f(r1 * cos(n * dth), 0, r1 * sin(n * dth));
			glVertex3f(r1 * cos((n + 1) * dth), 0, r1 * sin((n + 1) * dth));
			glVertex3f(r2 * cos((n + 1) * dth), h, r2 * sin((n + 1) * dth));
			glVertex3f(r2 * cos(n * dth), h, r2 * sin(n * dth));
		glEnd();
	}  // for loop
}  // TaperedCylinder
