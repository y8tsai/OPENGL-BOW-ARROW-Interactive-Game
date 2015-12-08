#include "DrawData.h"


DrawData::DrawData(void) {
	shaders = nullptr;
	texture = nullptr;
	vbo = 0;
	vao = 0;
	type = GL_TRIANGLES;
	indexStart = 0;
	indexCount = 0;
	multipleTex = 0;
}

DrawData::~DrawData(void) {
	if( shaders != nullptr ){
		delete shaders;
	}
	shaders = nullptr;
	if( texture != nullptr ){
		if( multipleTex ){
			delete[] texture;
		}else{
			delete texture;
		}
		texture = nullptr;
	}
}

void DrawData::EnableShader() {
	if( shaders != nullptr ){
		shaders->enable();
	}
}
void DrawData::DisableShader() {
	if( shaders != nullptr ){
		shaders->disable();
	}
}