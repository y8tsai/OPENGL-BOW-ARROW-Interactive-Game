#ifndef __LTREE_H__
#define __LTREE_H__

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "LSysParam.h"
#include "DrawData.h"
#include "math3d.h"

class LTree {
public:
	LTree(unsigned int randseed, LSysParam properties);
	void reset(unsigned int randseed);
	DrawData* generate();
	

private:
	// Takes a starting rule and number of iterations, to generate
	// sequence based on ruleset given in properties
	std::string evalRule(std::string &rule, int iterations);

	// Takes final sequence to draw cylinders to represent model
	DrawData* draw(std::string tape);

	// Helper functions for drawing model
	void drawForward(GLfloat *vertices, int &vert_idx);
	void yawLeft(GLfloat turnRadian);
	void yawRight(GLfloat turnRadian);

	GLfloat* cylinderMesh(vec3 &position, GLfloat radius, GLfloat length);





	unsigned int seed;
	LSysParam prop;

	RuleMap *memo;
	char currentLv;

	vec3 heading;
	vec3 position;
	unsigned int numDraws;
};


#endif