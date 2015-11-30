#include "FogMT.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


FogMT::FogMT() {
	fogMT = new MatrixTransform();
	fog = new Sphere();
	fogMT->addChild(fog);
}

FogMT::~FogMT() {
	delete fog;
	delete fogMT;
}

void FogMT::update(){
	//fill in update logic
}

void FogMT::draw(mat4 C) {
	fogMT->draw(C);
}

void FogMT::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}