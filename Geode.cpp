#include "Geode.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void Geode::draw(mat4 C)
{
	glMatrixMode(GL_MODELVIEW); //set to modelview
	glPushMatrix(); //conserve the matrix
	glMultMatrixf( C.ptr() );
	render(); //render the shape
	glPopMatrix();
}