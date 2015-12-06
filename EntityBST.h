#pragma once
#include "EntityNode.h"

class EntityBST {
private:
	
	int treeSize;
	EntityNode* successor(EntityNode*);

public:
	EntityNode* root;
	
	EntityBST();
	~EntityBST();
	int size();
	void insert(EntityNode* );
	void remove(EntityNode* );
	void remove(std::string); //remove by name, calls find and then remove
	EntityNode* find(std::string);

	void printAll(EntityNode* node);
};