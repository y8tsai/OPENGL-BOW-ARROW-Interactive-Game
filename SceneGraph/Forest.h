#ifndef __FOREST_H__
#define __FOREST_H__

#include "MatrixTransform.h"
#include "Geode.h"
#include "Group.h"
#include "Sphere.h"
#include "Cube.h"
#include "math3d.h"

class Forest: public MatrixTransform {
public: 
	Forest(); //create a forest
	~Forest();

	MatrixTransform* forestMT;
	MatrixTransform* treeMT;
	Cube* tree;

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif