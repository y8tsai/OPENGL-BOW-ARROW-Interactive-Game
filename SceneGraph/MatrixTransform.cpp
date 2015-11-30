#include "MatrixTransform.h"
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

MatrixTransform::MatrixTransform()
{
	M.makeIdentity(); //make identity matrix
	center = vec3(0.0, 0.0, 0.0);  //assume origin
	radius = 0; //dont draw anything
	cullingOn = false;
}

MatrixTransform::~MatrixTransform()
{
 //clear dynamic items
}

void MatrixTransform::draw(mat4 C)
{
	C = C * M ;
	int numberofRobots = 0;

	for (int i = 0; i < Group::children.size(); i++)
		Group::children.at(i)->draw(C);

/* 
		for (int i = 0; i < Group::children.size(); i++)
		{
			if (culling(Group::children.at(i)->center, Group::children.at(i)->radius))
			{
				numberofRobots++;
				Group::children.at(i)->draw(C);
				if (numberofRobots > 100)
					break;
			}
		}
*/
}


void MatrixTransform::update()
{
	//implement update logic
	for (int i = 0; i < children.size(); i++)
		children.at(i)->update();
}

mat4 MatrixTransform::getMatrix()
{
	return M;
}

void MatrixTransform::setMatrix(mat4 newM)
{
	M = newM;
}