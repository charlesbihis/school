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
}  // CalculateNormal


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
}  // Cylinder


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
}  // taperCyl
