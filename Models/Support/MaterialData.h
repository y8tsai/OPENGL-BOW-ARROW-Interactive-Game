#ifndef __MATERIALDATA_H__
#define __MATERIALDATA_H__

#include "math3d.h"

class MaterialData
{
    
public:

	//Default properties
	GLfloat* defaultDiffuseColor;
	GLfloat* defaultSpecularColor;
	GLfloat* defaultEmissionColor;
	GLfloat* defaultAmbientColor;
	GLfloat defaultShininess;

    //Material properties 
	GLfloat* diffuseColor;
	GLfloat* specularColor;
	GLfloat* emissionColor;
	GLfloat* ambientColor;
	GLfloat shininess;
    
    MaterialData(void); //uses default openGL material settings
	MaterialData(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat* emission, GLfloat shininess); //copy constructor
    ~MaterialData(void);
    
	virtual void setMaterial(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat* emission, GLfloat shininess);

	//apply material with current setting 
    virtual void apply(void);

	//resets material settings to default
	virtual void unapply(void);
};

#endif
