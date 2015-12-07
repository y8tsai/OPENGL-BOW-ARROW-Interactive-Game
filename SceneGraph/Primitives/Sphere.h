#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "SceneGraph/Base/Geode.h"

class Sphere : public Geode
{
    
public:
	Sphere();

    virtual void update();
	virtual void render();// render a unit sphere
};

#endif
