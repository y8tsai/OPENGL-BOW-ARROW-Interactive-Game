#ifndef CSE167_RenderData_h
#define CSE167_RenderData_h

#include "Utils/Program.h"
#include "Entity/Properties/Texture.h"

class DrawData {
public:  
    DrawData(void);
    ~DrawData(void);

	void EnableShader();
	void DisableShader();
    
	Program* shaders;
	Texture* texture;
	int multipleTex;
	GLuint vbo;
	GLuint vao;
	GLenum type;
	GLint indexStart;
	GLint indexCount;
};

#endif
