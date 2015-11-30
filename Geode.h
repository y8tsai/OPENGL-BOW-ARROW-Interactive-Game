#pragma once
#ifndef CSE167_Geode_h
#define CSE167_Geode_h
#include "Node.h"

class Geode : public Node
{
public:
	void draw(mat4 C);
	virtual void render() = 0;
};

#endif