#ifndef _PARTICLES_H
#define _PARTICLES_H

#include <stdlib.h>
#include <math.h>

typedef struct
{
				// colour
	float red;
	float green;
	float blue;
	float x;	// position 
	float y;
	float z;
	float vx;	// velocity  
	float vy;
	float vz;
	float lifespan; 
	float life;

} Particl; 

class ParticleSystem
{
	private: 
		Particl *particles;
		int maxNumParticles;

		float spread;
		float vx; 
		float vy;
		float vz;
		float ax;
		float ay;
		float az;
		float life;

		float RandomNum(float upperbound, float lowerbound);

	public:
		ParticleSystem(int maxNum, float spread, float life,
						float vx, float vy, float vz, 	
						float ax, float ay,	float az,
						float r, float g, float b);
		~ParticleSystem();

		void DrawParticles();
		void Update();
		void ResetParticle(int index);
		Particl GetParticle(int index);
		float r;
		float g;
		float b;
};

#endif
