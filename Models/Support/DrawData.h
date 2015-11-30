#ifndef CSE167_RenderData_h
#define CSE167_RenderData_h

#include "Program.h"
#include "Texture.h"

class DrawData {
public:  
    DrawData(void);
    ~DrawData(void);
    
	Program* shaders;
	Texture* texture;
	GLuint vbo;
	GLuint vao;
	GLenum type;
	GLint indexStart;
	GLint indexCount;
};

#endif
