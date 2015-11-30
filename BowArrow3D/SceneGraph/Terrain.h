#ifndef __TERRAIN__H__
#define __TERRAIN__H__

#include "Drawable.h"
#include "Geode.h"

class Terrain : public Geode
{

public:

	float size;

	Terrain(); //create a terrain
	~Terrain();

	virtual void update();
	virtual void render(); //render the terrain
};

#endif
