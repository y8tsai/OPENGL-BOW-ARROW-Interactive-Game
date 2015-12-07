#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "math3d.h"
#include "Models/Drawable.h"
#include <vector>

class Light : public Drawable
{
protected:
	// id:  0 = point light
	// id:  1 = spot light
	// id:  2 = directional light
    int bindID = -1;
    
public:
	vec3 pointLightPosition;
	vec3 spotLightPosition;
	vec3 directionLightPosition;

	//spotLight Properties
	vec3 spotLightDirection;
	float spot_cutoff;
	float exponentP;

	//Attenuation Properties
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
	MaterialData materialData; //contains material properties

public:
    
    Light();
    virtual ~Light(void);
    
	/* Drawable inherited draw functions*/
	virtual void draw(MaterialData&);
	virtual void draw(DrawData&);

	/* Light's own functions*/
	virtual void drawPoint();
	virtual void drawSpot();
	virtual void drawDirection();
	void setAttenuation(float constant, float linear, float quadratic);
    void bind(int);
    void unbind(void);
    
};

#endif
