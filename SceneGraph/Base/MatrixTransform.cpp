#include "MatrixTransform.h"
#include <iostream>
#include <GL/glut.h>

MatrixTransform::MatrixTransform() {
	M.makeIdentity(); //make identity matrix
}

MatrixTransform::MatrixTransform(mat4 m2w) {
	M = m2w;
}

MatrixTransform::~MatrixTransform() {
	prune();
}

void MatrixTransform::draw(mat4 C) {
	C = C * M ;
	for( std::size_t i = 0; i < Group::children.size(); ++i ){
		Group::children.at(i)->draw(C);
	}
}


void MatrixTransform::update(float t, float dt) {
	for( std::size_t i = 0; i < Group::children.size(); ++i ){
		Group::children.at(i)->update(t, dt);
	}
}

void MatrixTransform::prune() {
	for( std::size_t i = 0; i < Group::children.size(); ++i ){
		Group::children.at(i)->prune();
	}
	children.clear();
}

mat4 MatrixTransform::getMatrix() {
	return M;
}

void MatrixTransform::setMatrix(mat4 newM) {
	M = newM;
}