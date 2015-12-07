#ifndef __NODE_H__
#define __NODE_H__

#include "math3d.h"

class Node {
public:
	virtual void draw(mat4 C) = 0; //pure virtual functions
	virtual void update() = 0;

	virtual void setMatrix(mat4 C);
	virtual mat4 getMatrix();

	bool visible;
};

#endif