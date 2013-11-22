#include "smoke.h"

CSmoke::CSmoke(CVector origin, GLuint texture) : 
CParticleSystem(100, texture)
{
	this->origin = origin;
}


CSmoke::~CSmoke()
{
}

void CSmoke::OnInitialize(CParticle *p)
{
	p->position = origin;
	
	p->size = 0.5f+FRAND/5;

	p->velocity.x = FRAND;
	p->velocity.y = FRAND;
	p->velocity.z = FRAND;
	p->velocity.Normalize(0.2f);

	p->color[0] = 1.0f;
	p->color[1] = 1.0f;
	p->color[2] = 1.0f;
	p->color[3] = 0.5f + 0.5f*FRAND;
}

void CSmoke::OnUpdate(CParticle *p, float deltaTime)
{
	p->color[3] = p->color[3] - 0.1f*deltaTime;
	p->size += 0.1f * deltaTime;
	p->velocity -= p->velocity * deltaTime * 0.2f;
	p->position += p->velocity * deltaTime;

	if(p->color[3]<=0.0f){
		OnInitialize(p);
	}
}
