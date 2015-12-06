#ifndef __MATERIALDATA_H__
#define __MATERIALDATA_H__

#include "math3d.h"

class MaterialData
{
    
public:

    //Material properties 
	float* diffuseColor;
	float* specularColor;
	float* emissionColor;
	float* ambientColor;
	float shininess;
    
    MaterialData(void); //uses default openGL material settings
	MaterialData(float* ambient, float* diffuse, float* specular, float* emission, float shininess); //copy constructor
    ~MaterialData(void);
    
	virtual void setMaterial(float* ambient, float* diffuse, float* specular, float* emission, float shininess);

	//apply material with current setting 
    virtual void apply(void);

	//resets material settings to default
	virtual void unapply(void);
};

#endif
