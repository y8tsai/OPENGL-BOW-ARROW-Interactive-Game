#ifndef __MTRXTRANS_H__
#define __MTRXTRANS_H__

#include "Group.h"
#include "math3d.h"

class MatrixTransform : public Group {
public: 
	MatrixTransform();
	MatrixTransform(mat4 m2w);
	virtual ~MatrixTransform();

	virtual void draw(mat4 C);
	virtual void update(float t, float dt);

	mat4 getMatrix();  //get its toWorld Matrix "M"
	void setMatrix(mat4 newM); //set its toWorld Matrix "M" with parameter

	mat4 M; //its toWorld matrix
};


#endif