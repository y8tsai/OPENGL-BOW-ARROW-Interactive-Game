#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Shader.h"
#include <vector>


// OpenGL program that links multiple shaders together
class Program {
public:
	static Program* LoadShaders(const char* vertFile, const char* fragFile);

	Program(const std::vector<Shader>& shaders);
	~Program();

	GLuint getHandle() const;
	void enable() const;
	void disable() const;

	GLint getAttribute(const GLchar* attrName) const;
	GLint getUniform(const GLchar* unifName) const;

private:
	GLuint handle;

	//  There can only be one, no copying
	Program(const Program&);
	const Program& operator=(const Program&);
};
#endif