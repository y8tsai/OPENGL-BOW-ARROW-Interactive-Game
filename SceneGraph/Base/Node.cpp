#include "Node.h"

Node::Node() {
	cleanup = false;
	visible = true;
}
Node::~Node() {
	//do nothing
}

void Node::setMatrix(mat4 C) {
	//do nothing
}

mat4 Node::getMatrix() {
	return mat4();
}