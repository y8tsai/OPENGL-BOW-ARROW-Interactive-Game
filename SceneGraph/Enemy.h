#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "MatrixTransform.h"
#include "Geode.h"
#include "Group.h"
#include "Sphere.h"
#include "Cube.h"
#include "math3d.h"

class Enemy : public MatrixTransform
{
public:
	Enemy(); //create a forest
	~Enemy();

	MatrixTransform* enemiesMT; //single instance
	MatrixTransform* enemyMT;  //many instance
	Sphere* enemy; //single instance

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif