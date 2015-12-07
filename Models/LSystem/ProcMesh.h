#ifndef __PROCMESH_H__
#define __PROCMESH_H__

#include <iostream>
#include <vector>

#include "Entity/Properties/DrawData.h"
#include "math3d.h"

typedef std::vector<vec3> Verts;
typedef std::vector<Verts*> Mesh;

class CylinderMesh {
public:
	CylinderMesh();
	~CylinderMesh();

	void CreateCylinder(float h, float r, int stacks, int slices);
	void ClearOrientation();

	void Translate(vec3 translation);
	void Rotate(float deg, vec3 norm_axis);
	static CylinderMesh* Stitch(CylinderMesh *fst, CylinderMesh *snd);
	Verts* ExportGLTriangleStrip();

private:
	Verts* Interleave(Verts *bottom, Verts *top);

protected:
	vec3 pos;  //position to draw
	quat rot;  //rotation to draw
	mat4 m2w;  

	Mesh *raw_mesh;
};
#endif