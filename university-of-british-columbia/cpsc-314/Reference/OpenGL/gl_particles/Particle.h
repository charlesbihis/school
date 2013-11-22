#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <stdio.h>
#include "vector.h"

#define FRAND ((float)(rand()-rand())/RAND_MAX)

class CParticle
{
public:
	CParticle *next;

	CVector position;
	CVector velocity;
	CVector accelration;
	float color[4];
	float life;
	float size;
	bool died;

	CParticle();
};

class CParticleSystem
{
protected:
	CParticle			*firstParticle;
	GLuint				texture;
	
	virtual void OnInitialize(CParticle *p) = 0;
	virtual void OnUpdate(CParticle *p, float deltaTime) = 0;

public:
	CParticleSystem(int numParticles, GLuint texture);
	~CParticleSystem();

	void Initialize();
	void Update(float deltaTime);
	void Render();
};
