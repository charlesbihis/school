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

} Particle; 

class ParticleSystem
{
	private: 
		Particle *particles;
		int maxNumParticles;

		float spread;
		float vx; 
		float vy;
		float vz;
		float ax;
		float ay;
		float az;

		float RandomNum(float upperbound, float lowerbound);

	public:
		ParticleSystem(int maxNum, float spread,  
						float vx, float vy, float vz, 	
						float ax, float ay,	float az);
		~ParticleSystem();

		void DrawParticles();
		void Update();
		void ResetParticle(int index);
		Particle GetParticle(int index);
};

#endif
