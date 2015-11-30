#include "DrawData.h"


DrawData::DrawData(void)
{
	shaders = NULL;
	texture = NULL;
	vbo = 0;
	vao = 0;
	type = GL_TRIANGLES;
	indexStart = 0;
	indexCount = 0;
}

DrawData::~DrawData(void)
{
	delete shaders;
	delete texture;
}