#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "math3d.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "MaterialData.h"  //newly added for materials
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    mat4 toWorld;
    //Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
	virtual void draw(MaterialData&);
    virtual void update(UpdateData&);


	vec3 center;
	float* maxValues;
	float* minValues;

	// For Collision
	virtual vec3 getCenter();
	virtual float* getMaxValues();
	virtual float* getMinValues();
    
};

#endif
