#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Geode.h"

class Cube : public Geode
{
    
public:
    
    float size;
    
    Cube();
    virtual ~Cube(void);
    
    virtual void update();
	virtual void render(); //render a unit cube
    
};

#endif

