#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Base/Node.h"
#include "math3d.h"

//objects in our scene
#include "Terrain.h"

class Scene : public MatrixTransform{
public:
	Scene();
	~Scene();

	MatrixTransform* sceneMT;
	Terrain* terrain;

	void addChild(Node *n);
	virtual void draw(mat4 C); // draw function
	virtual void update(float t, float dt);
};

#endif