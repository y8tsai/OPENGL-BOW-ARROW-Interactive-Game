#pragma once
#ifndef CSE167_MatrixTransform_h
#define CSE167_MatrixTransform_h
#include "Group.h"
#include "math3d.h"


class MatrixTransform : public Group
{
public: 
	MatrixTransform();
	~MatrixTransform();

	mat4 M; //its toWorld matrix
	void draw(mat4 C);
	virtual void update();
	mat4 getMatrix();  //get its toWorld Matrix "M"
	void setMatrix(mat4 newM); //set its toWorld Matrix "M" with parameter
};


#endif