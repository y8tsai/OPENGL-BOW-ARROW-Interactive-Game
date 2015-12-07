#include "Group.h"
#include <iostream>
#include <GL/glut.h>

void Group::addChild(Node* newNode) {
	children.push_back(newNode);
}

void Group::removeChild(Node* node) {
	for( std::size_t i = 0; i < children.size(); ++i ){
		if( children.at(i) == node ){
			delete children.at(i);
			return;
		}
	}

	std::cout << "Group::removeChild -> No such node was found." << std::endl;
}

void Group::draw(mat4 C) {
	for( std::size_t i = 0; i < children.size(); ++i ){
		children.at(i)->draw(C);
	}
}