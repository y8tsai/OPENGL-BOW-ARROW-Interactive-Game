#include "Terrain.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math3d.h"

Terrain::Terrain() {

}

Terrain::~Terrain() {

}

void Terrain::update() {
	//fill in update logic
}

void Terrain::render() {
	glPushMatrix();
	glColor3f(0.4, 0.8, 0.6);
	glutSolidCube(1.0); //render a unit cube
	glPopMatrix();
}