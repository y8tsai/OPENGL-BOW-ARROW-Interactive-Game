#ifndef __GEODE_H__
#define __GEODE_H__

#include "Node.h"

#include <iostream>
#include <string>

class Geode : public Node {
public:
	void draw(mat4 C);
	virtual void render() = 0;

	std::string EID;	// Entity ID
};

#endif