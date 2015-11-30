#pragma once
#ifndef __LIGHTMT_H__
#define __LIGHTMT_H__
#include "MatrixTransform.h"
#include "Geode.h"
#include "Group.h"
#include "Sphere.h"
#include "Cube.h"
#include "math3d.h"

class LightMT : public MatrixTransform
{
public:

	LightMT(); //create a forest
	~LightMT();

	MatrixTransform *lightMT;
	Sphere* light;

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif