#ifndef PARTICLE_H
#define PARTICLE_H


typedef struct
{
		// colour
	float red;
	float green;
	float blue;
		// position
	float x;
	float y;
	float z;
		// velocity
	float vx;
	float vy;
	float vz;
		// lifespan
	float life;

} Particle; 


class ParticleSystem
{
	public:
		ParticleSystem(int maxNum, float spread, float lifespan, float vx, float vy, float vz, float ax, float ay,	float az, float r, float g, float b);
		~ParticleSystem();
		void DrawParticles();
		void Update();
		void ResetParticle(int index);
		Particle GetParticle(int index);

		float r;
		float g;
		float b;

	private: 
		Particle *particles;
		int max_particles;
		float spread;
		float vx; 
		float vy;
		float vz;
		float ax;
		float ay;
		float az;
		float lifespan;

		float RandomNum(float upperbound, float lowerbound);
};

#endif
