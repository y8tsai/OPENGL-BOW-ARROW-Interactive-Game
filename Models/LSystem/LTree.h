#ifndef __LTREE_H__
#define __LTREE_H__

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "LSysParam.h"
#include "ProcMesh.h"
#include "Entity/EntityNode.h"
#include "math3d.h"

class LTree {
public:
	LTree(unsigned int randseed, LSysParam properties);
	void reset(unsigned int randseed);
	EntityNode* generate();
	

private:
	// Takes a starting rule and number of iterations, to generate
	// sequence based on ruleset given in properties
	std::string evalRule(std::string &rule, int iterations);

	// Takes final sequence to draw cylinders to represent model
	std::vector<CylinderMesh*>* draw(std::string tape);

	// Helper functions for drawing model
	CylinderMesh* drawForward();
	void yawLeft(GLfloat turnRadian);
	void yawRight(GLfloat turnRadian);

	unsigned int seed;
	LSysParam prop;

	
	float yaw;
	vec3 position;
};


#endif