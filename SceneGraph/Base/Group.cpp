#include "Group.h"
#include <iostream>
#include <GL/glut.h>
#include <algorithm>

void Group::addChild(Node* newNode) {
	children.push_back(newNode);
}

void Group::removeChild(Node* node) {
	//for( std::size_t i = 0; i < children.size(); ++i ){
	//	if( children.at(i) == node ){
	//		children.at(i);
	//		return;
	//	}
	//}

	std::cout << "Group::removeChild -> No such node was found." << std::endl;
}

void Group::draw(mat4 C) {
	std::list<Node*>::iterator it = children.begin();
	while( it != children.end() ) {
		(*it)->draw(C);
	}
}

void Group::prune() {
	std::list<Node*>::iterator it = children.begin();
	while( it != children.end() ) {
		(*it)->prune();
		std::list<Node*>::iterator next = std::next(it, 1);
		delete (*next);
	}
	children.clear();
}