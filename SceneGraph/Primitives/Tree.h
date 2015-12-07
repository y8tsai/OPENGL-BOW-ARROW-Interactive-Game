#ifndef __TREE_H__
#define __TREE_H__

#include "SceneGraph/Base/Geode.h"
#include "math3d.h"

class Tree: public Geode {
public:
	Tree();
	Tree(std::string EntityID);
	~Tree();

	virtual void render();
	virtual void update();
};

#endif