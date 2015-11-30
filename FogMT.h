#pragma once
#ifndef __FOGMT_H__
#define __FOGMT_H__
#include "MatrixTransform.h"
#include "Geode.h"
#include "Group.h"
#include "Sphere.h"
#include "Cube.h"
#include "math3d.h"

class FogMT : public MatrixTransform
{
public:

	FogMT(); //create a forest
	~FogMT();

	MatrixTransform *fogMT;
	Sphere* fog;

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif
