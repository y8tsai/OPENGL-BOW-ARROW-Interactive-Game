#pragma once
#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Particle.h"
#include "math3d.h"

class Particles : public Drawable
{
public:
	Particles();
	Particles(int num, vec3 source);
	~Particles();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	int numParticles;
	Particle* particles; //dynamic array of particles
};

#endif