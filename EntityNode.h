#pragma once
#include <string>
#include "Drawable.h"

class EntityNode {
public:
	EntityNode();
	EntityNode(std::string, DrawData&, MaterialData&, UpdateData&);
	~EntityNode();

	std::string name;
	DrawData drawData;
	MaterialData materialData;
	UpdateData updateData;

	EntityNode* parent;
	EntityNode* left;
	EntityNode* right;
};