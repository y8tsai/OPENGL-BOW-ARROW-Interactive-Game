#ifndef __LIGHTMT_H__
#define __LIGHTMT_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Base/Geode.h"
#include "SceneGraph/Base/Group.h"
#include "SceneGraph/Primitives/Sphere.h"
#include "SceneGraph/Primitives/Cube.h"
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