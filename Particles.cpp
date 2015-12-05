#include "Particles.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Particles::Particles(){
	numParticles = 1000;
	vec3 source(0, 0, 0);
	particles = new Particle[numParticles];
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].CreateParticle(source);
	}

}

Particles::Particles(int num, vec3 source) {
	numParticles = num;
	particles = new Particle[numParticles];
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].CreateParticle(source);
	}

}

Particles::~Particles() {
	delete particles;  //free memory of dynamic particles array
}

void Particles::draw(DrawData&) {
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].DrawObjects(); //render the particles
	}
}

void Particles::update(UpdateData&) {
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].EvolveParticle(); //update the particles
	}
}
