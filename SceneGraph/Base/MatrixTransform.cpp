#include "MatrixTransform.h"
#include <iostream>
#include <GL/glut.h>

MatrixTransform::MatrixTransform() {
	visible = true;
	M.makeIdentity(); //make identity matrix
}

MatrixTransform::MatrixTransform(mat4 m2w) {
	visible = true;
	M = m2w;
}

MatrixTransform::~MatrixTransform() {

}

void MatrixTransform::draw(mat4 C) {
	C = C * M ;
	for( std::size_t i = 0; i < Group::children.size(); ++i ){
		Group::children.at(i)->draw(C);
	}
}


void MatrixTransform::update() {
	for( std::size_t i = 0; i < Group::children.size(); ++i ){
		Group::children.at(i)->update();
	}
}

mat4 MatrixTransform::getMatrix() {
	return M;
}

void MatrixTransform::setMatrix(mat4 newM) {
	M = newM;
}