#include "MaterialData.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

//default Material properties 
static GLfloat defaultDiffuseColor[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static GLfloat defaultSpecularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat defaultEmissionColor[]= { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat defaultAmbientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat defaultShininess = 0;


MaterialData::MaterialData()
{
	diffuseColor = defaultDiffuseColor;
	specularColor = defaultSpecularColor;
	emissionColor = defaultEmissionColor;
    ambientColor = defaultAmbientColor;
	shininess = defaultShininess;
}

MaterialData::MaterialData(float* diffuse, float* specular, float* emission, float* ambient, float Shininess)
{
	//Set Material properties 
	diffuseColor = diffuse;
	specularColor = specular;
	emissionColor = emission;
	ambientColor = ambient;
	shininess = Shininess;
}

MaterialData::~MaterialData()
{
    //Delete any dynamically allocated memory/objects here
}

void MaterialData::setMaterial(float* diffuse, float* specular, float* emission, float* ambient, float Shininess)
{
	//Set Material properties 
	diffuseColor = diffuse;
	specularColor = specular;
	emissionColor = emission;
	ambientColor = ambient;
	shininess = Shininess;
}


void MaterialData::apply(void)
{
	//Set the MaterialData properties for ambient, diffuse, specular, emission, and shininess
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
}

void MaterialData::unapply(void)
{
	//Reset the MaterialData properties for ambient, diffuse, specular, emission, and shininess to default
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  defaultDiffuseColor );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultSpecularColor );
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  defaultEmissionColor );
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   defaultAmbientColor );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &defaultShininess );
}




