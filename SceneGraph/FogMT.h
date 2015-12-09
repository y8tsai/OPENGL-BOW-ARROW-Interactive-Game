#ifndef __FOGMT_H__
#define __FOGMT_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Base/Geode.h"
#include "SceneGraph/Base/Group.h"
#include "SceneGraph/Primitives/Sphere.h"
#include "SceneGraph/Primitives/Cube.h"
#include "math3d.h"

class FogMT : public MatrixTransform
{
public:

	FogMT(); //create a forest
	~FogMT();

	MatrixTransform *fogMT;
	Sphere* fog;

	virtual void update(float t, float dt); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif
