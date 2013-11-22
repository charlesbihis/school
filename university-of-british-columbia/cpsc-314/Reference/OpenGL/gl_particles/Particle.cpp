#include "particle.h"

CParticle::CParticle()
{
	next = NULL;
}

CParticleSystem::CParticleSystem(int numParticles, GLuint texture)
{
	firstParticle = NULL;
	srand(GetTickCount());
	this->texture = texture;
	CParticle *p;
	for(int i=0;i<numParticles;i++){
		p = new CParticle();
		p->next = firstParticle;
		firstParticle = p;
	}
}

CParticleSystem::~CParticleSystem()
{
	if(firstParticle==NULL)return;

	CParticle *p = firstParticle, *q = firstParticle->next;
	while(q){
		delete p;
		p = q;
		q = q->next;
	}
	delete p;
}

void CParticleSystem::Initialize()
{
	CParticle *p = firstParticle;
	while(p){
		OnInitialize(p);
		p = p->next;
	}
}

void CParticleSystem::Update(float deltaTime)
{
	CParticle *p = firstParticle;
	while(p){
		p->velocity += p->accelration *deltaTime;
		p->position += p->velocity * deltaTime;
		OnUpdate(p, deltaTime);
		p = p->next;
	}
}

void CParticleSystem::Render()
{
	float viewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

	CVector right(viewMatrix[0], viewMatrix[4], viewMatrix[8]);
	CVector up(viewMatrix[1], viewMatrix[5], viewMatrix[9]);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	CParticle *p = firstParticle;
	glBegin(GL_QUADS);
	while(p)
	{
		GLfloat size = p->size/2;
		CVector pos = p->position;
		glColor4fv(p->color);		
		glTexCoord2f(0.0, 0.0); glVertex3fv((pos + (right + up) * -size).v);
		glTexCoord2f(1.0, 0.0); glVertex3fv((pos + (right - up) * size).v);
		glTexCoord2f(1.0, 1.0); glVertex3fv((pos + (right + up) * size).v);
		glTexCoord2f(0.0, 1.0); glVertex3fv((pos + (up - right) * size).v);

		p = p->next;
	}
	glEnd();
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}



