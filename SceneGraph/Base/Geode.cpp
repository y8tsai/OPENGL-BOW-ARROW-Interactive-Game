#include "Geode.h"
#include <GL/glut.h>

void Geode::draw(mat4 C) {
	glMatrixMode(GL_MODELVIEW); //set to modelview
	glPushMatrix(); //conserve the matrix
	
	glMultMatrixf( C.makeTranspose().ptr() );
	render(); //render the shape
	
	glPopMatrix();
}