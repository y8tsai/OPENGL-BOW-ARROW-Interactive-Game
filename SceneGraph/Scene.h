#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Base/Node.h"
#include "math3d.h"

//objects in our scene
//#include "Forest.h"
#include "Terrain.h"
//#include "FogMT.h"
//#include "LightMT.h"
//#include "Player.h"
//#include "Enemy.h"

class Scene : public MatrixTransform{
public:
	Scene();
	~Scene();

	MatrixTransform* sceneMT;
	Terrain* terrain;

	//FogMT* fog;
	
	//LightMT* light;
	//Player* player;
	//Enemy* enemy;
	void addChild(Node *n);
	virtual void draw(mat4 C); // draw function
	virtual void drawBoundingSphere(vec3 C); // draw bounding spheres
};

#endif