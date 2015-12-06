#include "MaterialData.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

MaterialData::MaterialData()
{
    //default Material properties 
	defaultDiffuseColor = new GLfloat[]{ 0.8f, 0.8f, 0.8f, 1.0f }; ;
	defaultSpecularColor = new GLfloat[]{ 0.0f, 0.0f, 0.0f, 1.0f }; 
	defaultEmissionColor = new GLfloat[]{ 0.0f, 0.0f, 0.0f, 1.0f };
	defaultAmbientColor = new GLfloat[]{ 0.2f, 0.2f, 0.2f, 1.0f };
	defaultShininess = 0;

	diffuseColor = defaultDiffuseColor;
	specularColor = defaultSpecularColor;
	emissionColor = defaultEmissionColor;
    ambientColor = defaultAmbientColor;
	shininess = defaultShininess;
}

MaterialData::MaterialData(GLfloat* diffuse, GLfloat* specular, GLfloat* emission, GLfloat* ambient, GLfloat Shininess)
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

	if (diffuseColor != defaultDiffuseColor) {  //pointer has been changed
		delete defaultDiffuseColor;
		delete defaultSpecularColor;
		delete defaultEmissionColor;
		delete defaultAmbientColor;

		delete diffuseColor;
		delete specularColor;
		delete emissionColor;
		delete ambientColor;
	}

	else {  //if the pointers weren't changed, just delete the same pointer
		delete defaultDiffuseColor;
		delete defaultSpecularColor;
		delete defaultEmissionColor;
		delete defaultAmbientColor;
	}
}

void MaterialData::setMaterial(GLfloat* diffuse, GLfloat* specular, GLfloat* emission, GLfloat* ambient, GLfloat Shininess)
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




