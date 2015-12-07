#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Base/Geode.h"
#include "SceneGraph/Base/Group.h"
#include "Sphere.h"
#include "Cube.h"
#include "math3d.h"

class Player : public MatrixTransform
{
public:
	Player(); //create a player
	~Player();

	MatrixTransform* playerMT;
	MatrixTransform* bowMT;
	MatrixTransform* arrowMT;
	MatrixTransform* playerbodyMT;
	Sphere* player;
	Cube* bow;
	Cube* arrow;

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif