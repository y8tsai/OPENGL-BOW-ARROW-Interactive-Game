#pragma once
#ifndef CSE167_Node_h
#define CSE167_Node_h
#include "math3d.h"


class Node
{
public:
	vec3 center;
	float radius;
	bool cullingOn;

	virtual void draw(mat4 C) = 0; //pure virtual functions
	virtual void update() = 0; 
	virtual void drawBoundingSphere(vec3 C);

	/*culling not fully functional yet
	virtual bool culling(vec3 Center, float Radius);
	*/

	virtual void setMatrix(mat4 );
	virtual mat4 getMatrix();
};

#endif