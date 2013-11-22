#include <GL/glut.h>
#include "particles.h"

ParticleSystem::ParticleSystem(int maxNum, float spread, float life,
						float vx, float vy, float vz, 	
						float ax, float ay, float az, 
						float r, float g, float b)
{
		maxNumParticles = maxNum;
		particles = new Particl[maxNumParticles];
		
		this->spread = spread;
		this->ax = ax;
		this->ay = ay;
		this->az = az;

		this->vx = vx; 
		this->vy = vy;
		this->vz = vz;
		this->life = life;

		this->r = r;
		this->g = g;
		this->b = b;

		for(int i = 0; i < maxNumParticles; i++)
		{
			ResetParticle(i);
		}
}

ParticleSystem::~ParticleSystem()
{
	delete particles;
}

Particl ParticleSystem::GetParticle(int index)
{
	return particles[index];
}

void ParticleSystem::DrawParticles()
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glPointSize(1);
	glBegin(GL_POINTS);
	for(int i = 0; i < maxNumParticles; i++)
	{
		glNormal3f(0, 1, 0);
		//glColor3f(particles[i].red, particles[i].green, particles[i].blue);
		//glColor3f(0.75, 0.75, particles[i].blue);
		glColor3f(r, g, particles[i].blue);
		glVertex3f(particles[i].x, particles[i].y, particles[i].z);
	}
	glEnd();
	glPopMatrix();
}

void ParticleSystem::Update()
{
	for(int i = 0; i < maxNumParticles; i++)
	{
		if (particles[i].lifespan < life)
		{
			particles[i].x += particles[i].vx;
			particles[i].y += particles[i].vy;
			particles[i].z += particles[i].vz;
	
			particles[i].vx += ax;	
			particles[i].vy += ay;
			particles[i].vz += az;

			particles[i].lifespan += 1;
		}
		else
		{
			ResetParticle(i);
		}
	}
}

void ParticleSystem::ResetParticle(int index)
{
	particles[index].x = RandomNum(0.5*spread, -0.5*spread);
	particles[index].y = RandomNum(0.5*spread, -0.5*spread);
	particles[index].z = RandomNum(0.5*spread, -0.5*spread);
	
	particles[index].red = RandomNum(1, 0);
	particles[index].green = RandomNum(1, 0);
	particles[index].blue = RandomNum(1, 0);

	particles[index].vx = vx + RandomNum(spread/2, -spread/2);
	particles[index].vy = vy + RandomNum(spread, 0); 
	particles[index].vz = vz + RandomNum(spread/2, -spread/2);

	particles[index].lifespan = 0;
}

float ParticleSystem::RandomNum(float upperbound, float lowerbound)
{
	float random = 0;
	float range = upperbound - lowerbound; 
    random = lowerbound + (float)(range * rand() / (RAND_MAX));		
	
	return  random; 	
}
