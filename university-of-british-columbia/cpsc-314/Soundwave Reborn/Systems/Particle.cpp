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



#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "Particle.h"

ParticleSystem :: ParticleSystem(int max_particles, float spread, float lifespan, float vx, float vy, float vz, float ax, float ay, float az, float r, float g, float b)
{
	this->max_particles = max_particles;
	this->spread = spread;
	this->lifespan = lifespan;
	particles = new Particle[max_particles];

	this->ax = ax;
	this->ay = ay;
	this->az = az;

	this->vx = vx; 
	this->vy = vy;
	this->vz = vz;

	this->r = r;
	this->g = g;
	this->b = b;

	for(int i = 0; i < max_particles; i++)
	{
		ResetParticle(i);
	}  // for loop
}  // Particle


ParticleSystem :: ~ParticleSystem()
{
	delete particles;
}  // ~ParticleSystem


Particle ParticleSystem :: GetParticle(int index)
{
	return particles[index];
}  // GetParticle


void ParticleSystem :: DrawParticles()
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glPointSize(1);
	glBegin(GL_POINTS);
		for(int i = 0; i < max_particles; i++)
		{
			glNormal3f(0, 1, 0);
			//glColor3f(particles[i].red, particles[i].green, particles[i].blue);
			glColor3f(r, g, b);
			glVertex3f(particles[i].x, particles[i].y, particles[i].z);
		}  // for loop
	glEnd();
	glPopMatrix();
}  // DrawParticles


void ParticleSystem :: Update()
{
	// increment life of each particle
	for(int i = 0; i < max_particles; i++)
	{
		if (particles[i].life < lifespan)
		{
			particles[i].x += particles[i].vx;
			particles[i].y += particles[i].vy;
			particles[i].z += particles[i].vz;
	
			particles[i].vx += ax;	
			particles[i].vy += ay;
			particles[i].vz += az;

			particles[i].life += 1;
		}  // if statement
		else
		{
			ResetParticle(i);
		}  // else statement
	}  // for loop
}  // Update


void ParticleSystem :: ResetParticle(int index)
{
	particles[index].x = RandomNum(0.5 * spread, -0.5 * spread);
	particles[index].y = RandomNum(0.5 * spread, -0.5 * spread);
	particles[index].z = RandomNum(0.5 * spread, -0.5 * spread);
	
	particles[index].red = RandomNum(1, 0);
	particles[index].green = RandomNum(1, 0);
	particles[index].blue = RandomNum(1, 0);

	particles[index].vx = vx + RandomNum(spread/2, -spread/2);
	particles[index].vy = vy + RandomNum(spread, 0); 
	particles[index].vz = vz + RandomNum(spread/2, -spread/2);

	particles[index].life = 0;
}  // ResetParticle


float ParticleSystem :: RandomNum(float upperbound, float lowerbound)
{
	float random = 0;
	float range = upperbound - lowerbound; 
    random = lowerbound + (float)(range * rand() / (RAND_MAX));		
	
	return  random; 	
}  // RandomNum
