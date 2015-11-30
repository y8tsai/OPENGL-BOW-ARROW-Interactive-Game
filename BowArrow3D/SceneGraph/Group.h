#pragma once
#ifndef CSE167_Group_h
#define CSE167_Group_h

#include "Node.h"
#include "math3d.h"
#include <vector>

class Group : public Node
{
public:
	std::vector<Node*> children;
	void addChild(Node*);
	void removeChild(Node*);
	virtual void draw(mat4 C);
};


#endif