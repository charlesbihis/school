#include "particle.h"

class CSmoke : public CParticleSystem
{
protected:
	float expVel;
	CVector origin;
	CVector direction;

	virtual void OnInitialize(CParticle *p);
	virtual void OnUpdate(CParticle *p, float deltaTime);
public:
	CSmoke(CVector origin, GLuint texture);
	~CSmoke();
};