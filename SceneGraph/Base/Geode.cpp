#include "Geode.h"
#include <GL/glut.h>

Geode::~Geode() {
	// do nothing
}

void Geode::draw(mat4 C) {
	glMatrixMode(GL_MODELVIEW); //set to modelview
	glPushMatrix(); //conserve the matrix
	
	glMultMatrixf( C.makeTranspose().ptr() );
	render(); //render the shape
	
	glPopMatrix();
}

void Geode::prune() {
	// top levels will call this 
	// it will do nothing
	// and top level will delete this object
}