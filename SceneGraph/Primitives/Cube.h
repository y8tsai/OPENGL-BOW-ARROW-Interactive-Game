#ifndef __CUBE_H__
#define __CUBE_H__

#include "SceneGraph/Base/Geode.h"

class Cube : public Geode {
public:
	Cube();
	Cube(std::string EntityID);
	~Cube();

	void render();
    virtual void update();
	
};

#endif