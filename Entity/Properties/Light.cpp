#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Light::Light()
{
	//Default Settings
    constantAttenuation = 0.5;
    linearAttenuation = 0.5;
    quadraticAttenuation = 1.0;

	pointLightPosition = vec3(0, 0, 0);
	spotLightPosition = vec3(0, 0, 0);
	directionLightPosition = vec3(0, 10.0, 0);

	spotLightDirection = vec3(0.0, 0.0, -1.0);
	spot_cutoff = 30.0;
	exponentP = 4.0;

	materialData = MaterialData(); //set default properties
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
	// id:  0 = point light
	// id:  1 = spot light
	// id:  2 = directional light

    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, materialData.ambientColor );
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, materialData.diffuseColor );
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, materialData.specularColor );
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
	glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, constantAttenuation);
    //Add support for Linear Attenuation
	glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, linearAttenuation);
	//add support for quadratic attenuation
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    

	//Setup spotlight direction, angle, and exponent here
	switch (bindID) {

	case 0:
	{
		glLightfv(GL_LIGHT0 + bindID, GL_POSITION, pointLightPosition.ptr());
		drawPoint(); //draws pointlight as a sphere
		break;
	}
	case 1:
	{
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_CUTOFF, spot_cutoff);
		glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, spotLightDirection.ptr() );
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_EXPONENT, exponentP);
		glLightfv(GL_LIGHT0 + bindID, GL_POSITION, spotLightPosition.ptr());
		drawSpot(); //draws spotLight as a sphere
		break;
	}

	case 2:
		glLightfv(GL_LIGHT0 + bindID, GL_POSITION, directionLightPosition.ptr());
		//drawDirection(); //draws directionalLight, not actually implemented
		break;
	}

}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}

void Light::drawPoint()
{

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	mat4 makeTrans;
	makeTrans.translate(pointLightPosition);
	glMultMatrixf(makeTrans.ptr());
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.5, 1000, 1000);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::drawSpot()
{
	//Draw the spotlight

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	mat4 makeTrans;
	makeTrans.translate(spotLightPosition);
	glMultMatrixf(makeTrans.ptr());
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 1000, 1000);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::drawDirection()
{

}

void Light::draw(MaterialData& matData)
{
	materialData = matData;
	bind(bindID);
}

void Light::draw(DrawData& drawData)
{
	bind(bindID);
}

void Light::setAttenuation(float constant, float linear, float quadratic)
{
	constantAttenuation = constant;
	linearAttenuation = linear;
	quadraticAttenuation = quadratic;
}