#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere()
{
	//
}

void Sphere::update()
{
    //
}



void Sphere::render()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 300, 300);  //render a unit sphere
	glPopMatrix();
}