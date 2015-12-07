#ifndef __ENTITY_NODE_H__
#define __ENTITY_NODE_H__

#include <string>
#include "Models/Drawable.h"
#include "LSystem/ProcMesh.h"

class EntityNode {
public:
	EntityNode();
	EntityNode(std::string, DrawData&, MaterialData&, UpdateData&);
	~EntityNode();

	std::string name;
	DrawData drawData;
	MaterialData materialData;
	UpdateData updateData;
	std::vector<Verts*>* vertices;


	EntityNode* parent;
	EntityNode* left;
	EntityNode* right;
};

#endif