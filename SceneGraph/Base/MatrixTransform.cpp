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
	std::list<Node*>::iterator it = children.begin();
	while( it != children.end() ) {
		if((*it)->visible){
			(*it)->draw(C);
		}
		++it;
	}
}


void MatrixTransform::update(float t, float dt) {
	
	std::list<Node*>::iterator it = children.begin();
	std::list<Node*>::iterator next;
	while( it != children.end() ) {
		if( (*it)->cleanup ){
			(*it)->prune();
			next = std::next(it, 1);
			Node *temp = *it;
			delete temp;
			Group::children.erase(it);
			it = next;
		} else {
			(*it)->update(t, dt);
			++it;
		}
	}
}

mat4 MatrixTransform::getMatrix() {
	return M;
}

void MatrixTransform::setMatrix(mat4 newM) {
	M = newM;
}