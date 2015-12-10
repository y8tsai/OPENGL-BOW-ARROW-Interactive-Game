#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Particle.h"
#include "Utils/tga.h"
#include "math3d.h"
#include "SceneGraph/Base/MatrixTransform.h""

#define PARTICLES_ERROR_INVALID_PARAM		-5
#define PARTICLES_ERROR_LOADING_IMAGE		-4
#define PARTICLES_ERROR_MEMORY_PROBLEM		-3
#define	PARTICLES_ERROR_NOT_SAVED			-2
#define PARTICLES_ERROR_NOT_INITIALISED		-1
#define PARTICLES_OK						 0

class Particles : public MatrixTransform
{
public:
	Particles();
	Particles(int num, vec3 source);   //specify particle number and focal location in world space
	~Particles();

	void draw(mat4 C);
	void update(float t, float dt);

	bool markDelete;   

	int particlesLoadFromImage(char *filename); //used to load displacement map
	int numParticles;							//total number of particles
	Particle* particles;						//dynamic array of particles
	int particlesWidth, particlesLength;		//dimensions of the displacement map
	float* particlesHeights;					//between 0.0 to 1.0 (for initial velocity purposes)
};

#endif