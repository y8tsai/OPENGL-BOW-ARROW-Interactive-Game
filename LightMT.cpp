#include "LightMT.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LightMT::LightMT() {
	lightMT = new MatrixTransform();
	light = new Sphere();

	lightMT->addChild(light);
}

LightMT::~LightMT() {
	delete light;
	delete lightMT;
}

void LightMT::update() {
	//add update logic
}

void LightMT::draw(mat4 C) {
	lightMT->draw(C);
}

void LightMT::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}