#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"

Cube::Cube()
{
   
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::update()
{
    //
}

void Cube::render()
{
	glPushMatrix();
	glColor3f(0.4, 0.8, 0.6);
	glutSolidCube(1.0); //render a unit cube
	glPopMatrix();
}