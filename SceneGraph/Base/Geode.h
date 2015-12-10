#ifndef __GEODE_H__
#define __GEODE_H__

#include "Node.h"

#include <iostream>
#include <string>

class Geode : public Node {
public:
	virtual ~Geode();
	void draw(mat4 C);
	virtual void render() = 0;
	void prune();

	std::string EID;	// Entity ID
	unsigned int PID;	// Physics ID
	unsigned int CID;	// Collision ID

};

#endif