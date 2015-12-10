#ifndef __TREE_H__
#define __TREE_H__

#include "SceneGraph/Base/Geode.h"
#include "math3d.h"

class Tree: public Geode {
public:
	Tree();
	Tree(std::string EntityID, unsigned int pid, unsigned int cid);
	~Tree();

	void render();
	void update(float t, float dt);
};

#endif