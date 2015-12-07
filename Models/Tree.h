#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <vector>

#include "Entity/Properties/DrawData.h"
#include "LSystem/ProcMesh.h"

class Tree {
public:
	Tree();
	~Tree();

	void draw(std::vector<CylinderMesh*>* parts);

};

#endif