#include <stdio.h>
#include <gl\glut.h>
#include <math.h>
#include "Scene.h"
#include "../Draw/DrawFunctions.h"


Scene :: Scene()
{
  current_light = GL_LIGHT1;
}  // Scene


void Scene :: Draw()
{
  glPushMatrix();
    DrawFloor();
	DrawPlatform();
	DrawCageDome();
	DrawGlassDome();
  glPopMatrix();
}  // Draw


void Scene :: DrawSpotlight()
{
  GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat light_specular[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat light_position[] = {0, 15, 0, 1.0};
  GLfloat spot_direction[] = {-350, 700, 0};

  glLightfv(current_light, GL_AMBIENT, light_ambient);
  glLightfv(current_light, GL_DIFFUSE, light_diffuse);
  glLightfv(current_light, GL_SPECULAR, light_specular);
  glLightfv(current_light, GL_POSITION, light_position);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

  glLightf(current_light, GL_SPOT_CUTOFF, 45.0);
  glLightfv(current_light, GL_SPOT_DIRECTION, spot_direction);
  glLightf(current_light, GL_SPOT_EXPONENT, 2.0);

  glEnable(current_light);
  
  glPushMatrix();
    TaperedCylinder(13, 3, 3, 20);
    glTranslatef(0, 10, 0);
    glRotatef(45, 0, 0, 1);
    TaperedCylinder(0, 0, 12, 30);
    TaperedCylinder(20, 12, 12, 30);
    glTranslatef(0, 20, 0);
    TaperedCylinder(0, 0, 12, 30);
  glPopMatrix();
}  // DrawSpotlight


void Scene :: DrawFloorlight()
{
  GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  GLdouble y_clip_pane[4] = {0.0, 1.0, 0.0, 0.0};		// clip lower half (y < 0)
  GLdouble x_clip_pane[4] = {1.0, 0.0, 0.0, 0.0};		// clip left half (x < 0)

  glClipPlane(GL_CLIP_PLANE0, y_clip_pane);
  glClipPlane(GL_CLIP_PLANE1, x_clip_pane);
  glEnable(GL_CLIP_PLANE0);
  glEnable(GL_CLIP_PLANE1);

  glPushMatrix();
    glScalef(1.5, 0.75, 1);
    glutSolidSphere(12, 20, 20);
  glPopMatrix();

  glDisable(GL_CLIP_PLANE0);
  glDisable(GL_CLIP_PLANE1);
}  // DrawFloorlight



void Scene :: DrawFloor()
{
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.2, 0.2, 0.2, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  GLdouble y_clip_pane[4] = {0.0, -1.0, 0.0, 0.0};
  glClipPlane(GL_CLIP_PLANE0, y_clip_pane);
  glEnable(GL_CLIP_PLANE0);
  
  glPushMatrix();
    glScalef(1, 0.3, 1);
    glutSolidSphere(1000, 30, 30);
  glPopMatrix();

  glDisable(GL_CLIP_PLANE0);

  glPushMatrix();
    TaperedCylinder(0, 1000, 0, 30);

    glBegin(GL_POLYGON);
	  glNormal3f(0, 1, 0);
	  glVertex3f(-380, 0, 925);
	  glVertex3f(380, 0, 925);
	  glVertex3f(380, 0, 1525);
	  glVertex3f(-380, 0, 1525);
	glEnd();
  glPopMatrix();
}  // DrawFloor


void Scene :: DrawCageDome()
{
  GLdouble z_clip_pane[4] = {0.0, 0.0, -1.0, 925.0};
  GLdouble y_clip_pane[4] = {0.0, 1.0, 0.0, 0.0};
  glClipPlane(GL_CLIP_PLANE0, z_clip_pane);
  glClipPlane(GL_CLIP_PLANE4, y_clip_pane);
  glEnable(GL_CLIP_PLANE0);
  glEnable(GL_CLIP_PLANE4);

  glPushMatrix();
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
    DrawVerticalGirder();
    glRotatef(20, 0, 1, 0);
  glPopMatrix();

  glPushMatrix();
    DrawHorizontalGirder(-5);
	DrawHorizontalGirder(100);
	DrawHorizontalGirder(200);
	DrawHorizontalGirder(300);
	DrawHorizontalGirder(400);
	DrawHorizontalGirder(500);
	DrawHorizontalGirder(600);
	DrawHorizontalGirder(700);
	DrawHorizontalGirder(800);
	DrawHorizontalGirder(900);
	DrawHorizontalGirder(1000);
  glPopMatrix();
  
  glDisable(GL_CLIP_PLANE0);

  glPushMatrix();
    glTranslatef(0, 0, 700 + 225);
    glRotatef(90, 1, 0, 0);
    TaperedCylinder(600, 380, 380, 30);
  glPopMatrix();

  glDisable(GL_CLIP_PLANE4);
}  // DrawDome


void Scene :: DrawGlassDome()
{
  GLfloat mat_transparent[] = { 0.5, 0.5, 0.5, 0.7 };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
  glEnable (GL_BLEND);
  glDepthMask (GL_FALSE);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE);
  glDepthMask (GL_TRUE);

  GLdouble y_clip_pane[4] = {0.0, 1.0, 0.0, 0.0};
  glClipPlane(GL_CLIP_PLANE0, y_clip_pane);
  glEnable(GL_CLIP_PLANE0);
  
  glScalef(0.99, 0.99, 0.99);
  glutSolidSphere(1000, 30, 30);

  glDisable(GL_CLIP_PLANE0);
  glDisable (GL_BLEND);
}  // DrawGlassDome


void Scene :: DrawVerticalGirder()
{
  GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  GLdouble y_clip_pane[4] = {0.0, 1.0, 0.0, 0.0};		// clip lower half (y < 0)
  GLdouble x_clip_pane1[4] = {1.0, 0.0, 0.0, 25.0};
  GLdouble x_clip_pane2[4] = {-1.0, 0.0, 0.0, 25.0};

  glClipPlane(GL_CLIP_PLANE1, y_clip_pane);
  glClipPlane(GL_CLIP_PLANE2, x_clip_pane1);
  glClipPlane(GL_CLIP_PLANE3, x_clip_pane2);
  glEnable(GL_CLIP_PLANE1);
  glEnable(GL_CLIP_PLANE2);
  glEnable(GL_CLIP_PLANE3);

  glutSolidSphere(1000, 20, 20);

  glDisable(GL_CLIP_PLANE1);
  glDisable(GL_CLIP_PLANE2);
  glDisable(GL_CLIP_PLANE3);
}  // DrawGirder


void Scene :: DrawHorizontalGirder(double start_value)
{
  GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  GLdouble y_clip_pane1[4] = {0.0, 1.0, 0.0, -start_value};
  GLdouble y_clip_pane2[4] = {0.0, -1.0, 0.0, start_value + 25};

  glClipPlane(GL_CLIP_PLANE1, y_clip_pane1);
  glClipPlane(GL_CLIP_PLANE2, y_clip_pane2);
  glEnable(GL_CLIP_PLANE1);
  glEnable(GL_CLIP_PLANE2);

  glutSolidSphere(1000, 20, 20);

  glDisable(GL_CLIP_PLANE1);
  glDisable(GL_CLIP_PLANE2);
}  // DrawHorizontalGirder


void Scene :: DrawPlatform()
{
  GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 1.0};
  GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glPushMatrix();
    glTranslatef(0, 30, 0);
    TaperedCylinder(0, 185, 0, 30);
    glTranslatef(0, -6, 0);
    TaperedCylinder(6, 185, 185, 30);
    TaperedCylinder(0, 195, 0, 30);
    glTranslatef(0, -6, 0);
    TaperedCylinder(6, 195, 195, 30);
    TaperedCylinder(0, 205, 0, 30);
    glTranslatef(0, -6, 0);
    TaperedCylinder(6, 205, 205, 30);
    TaperedCylinder(0, 215, 0, 30);
    glTranslatef(0, -6, 0);
    TaperedCylinder(6, 215, 215, 30);
    TaperedCylinder(0, 225, 0, 30);
    glTranslatef(0, -6, 0);
    TaperedCylinder(6, 225, 225, 30);
  glPopMatrix();
  glPushMatrix();
    glRotatef(-45, 0, 1, 0);
    glTranslatef(185, 30, 0);
	current_light = GL_LIGHT1;
    DrawSpotlight();						// draw front right spotlight
  glPopMatrix();
  glPushMatrix();
    glRotatef(45, 0, 1, 0);
    glTranslatef(-185, 30, 0);
    glRotatef(180, 0, 1, 0);
    current_light = GL_LIGHT2;
    DrawSpotlight();							// draw front left spotlight
  glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 30, -185);
    glRotatef(90, 0, 1, 0);
	current_light = GL_LIGHT3;
    DrawSpotlight();							// draw back spotlight
  glPopMatrix();
}  // DrawPlatform


void Scene :: DrawPath()
{
  GLfloat mat_ambient[] = {0.8, 0.25, 0.25, 1.0};
  GLfloat mat_diffuse[] = {0.8, 0.25, 0.25, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glPushMatrix();
    glTranslatef(0, -217.0, 150);
	glBegin(GL_POLYGON);
	  glNormal3f(0, 1, 0);
	  glVertex3f(-50, 0, 0);
	  glVertex3f(50, 0, 0);
	  glVertex3f(50, 0, 5000);
	  glVertex3f(-50, 0, 5000);
	glEnd();
  glPopMatrix();
}  // DrawPath