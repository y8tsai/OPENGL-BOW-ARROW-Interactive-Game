#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__
#include "Node.h"
#include "MatrixTransform.h"
#include "math3d.h"

//objects in our scene
#include "Forest.h"
#include "Terrain.h"
#include "FogMT.h"
#include "LightMT.h"
#include "Player.h"
#include "Enemy.h"

class Scene : public MatrixTransform
{
public:
	Scene();
	~Scene();

	MatrixTransform* sceneMT;
	FogMT* fog;
	Forest* forest;
	Terrain* terrain;
	LightMT* light;
	Player* player;
	Enemy* enemy;

	virtual void update(); //update
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif