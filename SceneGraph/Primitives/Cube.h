#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Models/Drawable.h"
#include "SceneGraph/Base/Geode.h"

class Cube : public Geode {
public:
    
    float size;
    
    Cube();
    virtual ~Cube(void);
    
    virtual void update();
	virtual void render(); //render a unit cube
    
};

#endif

