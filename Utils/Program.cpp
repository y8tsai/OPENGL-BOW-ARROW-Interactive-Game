#include "Program.h"
#include <iostream>
#include <vector>

// static method
// Loads compiles shaders and dynamically allocate Program that links the shaders together
Program* Program::LoadShaders(const char* vertFile, const char* fragFile) {
	std::vector<Shader> shaders;
	shaders.push_back(Shader::shaderFromFile(vertFile, GL_VERTEX_SHADER));
	shaders.push_back(Shader::shaderFromFile(fragFile, GL_FRAGMENT_SHADER));
	return new Program(shaders);
}

Program::Program(const std::vector<Shader>& shaders) {
	handle = 0;

	if( shaders.size() <= 0 ){
		std::cerr << "No shaders given to program" << std::endl;
	}

	// create a program object
	handle = glCreateProgram();
	if( handle == 0 ){
		std::cerr << "Call to glCreateProgram failed\n" << std::endl;
	}

	// attach all the shaders
	for( int i = 0; i < shaders.size(); ++i ){
		glAttachShader(handle, shaders[i].getHandle());
	}

	// link all the shaders together
	glLinkProgram(handle);

	GLint result = GL_FALSE;
	glGetProgramiv(handle, GL_LINK_STATUS, &result);
	if( result == GL_FALSE ){
		GLint logLength;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);
		char *logInfo = new char[logLength + 1];
		glGetProgramInfoLog(handle, logLength, NULL, logInfo);
		std::cerr << "Program linking failed with reason:\n" << logInfo << std::endl;
		delete [] logInfo;

		glDeleteProgram(handle);
		handle = 0;
	}
}

Program::~Program() {
	if( handle != 0 ){
		glDeleteProgram(handle);
	}
}

GLuint Program::getHandle() const {
	return handle;
}

void Program::enable() const {
	glUseProgram(handle);
}

void Program::disable() const {
	glUseProgram(0);
}

GLint Program::getAttribute(const GLchar* attrName) const {
	GLint atr = glGetAttribLocation(handle, attrName);
	if( atr == -1){
		std::cerr << "Program attribute ( " << attrName << " ) not found!" << std::endl;
	}

	return atr;
}

GLint Program::getUniform(const GLchar* unifName) const {
	GLint ufm = glGetUniformLocation(handle, unifName);
	if( ufm == -1){
		std::cerr << "Program uniform ( " << unifName << " ) not found!" << std::endl;
	}

	return ufm;
}