#ifndef __NODE_H__
#define __NODE_H__

#include "math3d.h"
#include "Physics/Simulation.h"

class Node {
public:
	virtual void draw(mat4 C) = 0; //pure virtual functions
	virtual void update(float t, float dt) = 0;

	virtual void setMatrix(mat4 C);
	virtual mat4 getMatrix();

	bool visible;
	unsigned int CID;

protected:
	Node();
};

#endif