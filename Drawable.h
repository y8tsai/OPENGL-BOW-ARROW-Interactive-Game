#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "math3d.h"
#include "DrawData.h"
#include "UpdateData.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    mat4 toWorld;
    //Material material;
	vec3 center;

	float* maxValues;
	float* minValues;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
	virtual vec3 getCenter();
	virtual float* getMaxValues();
	virtual float* getMinValues();
    
};

#endif
