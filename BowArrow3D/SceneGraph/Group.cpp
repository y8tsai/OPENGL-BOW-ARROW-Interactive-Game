#include "Group.h"
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void Group::addChild(Node* newNode)
{
	children.push_back(newNode);
}

void Group::removeChild(Node* node)
{
	for (int i = 0; i < children.size(); i++)
		if (children.at(i) == node) {
			delete children.at(i);
			break;
		}

	std::cout << "No such node was found." << std::endl;
}

void Group::draw(mat4 C)
{
	for (int i = 0; i < children.size(); i++)
		children.at(i)->draw(C);
}