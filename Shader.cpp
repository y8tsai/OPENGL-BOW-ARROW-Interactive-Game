#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

/* static */
Shader Shader::shaderFromFile(const std::string& filePath, GLenum type) {
	std::ifstream fileStream(filePath.c_str(), std::ios::in | std::ios::binary);
	if( !fileStream.is_open() ){
		std::cerr << "Failed to open file: " << filePath << std::endl;
	}

	std::stringstream buffer;
	buffer << fileStream.rdbuf();
	fileStream.close();

	Shader shader(buffer.str(), type);
	return shader;
}


Shader::Shader(const std::string& filesrc, GLenum type) : handle(0), refCount(NULL) {
	handle = glCreateShader(type);
	if( handle == 0 ){
		std::cerr << "Call to glCreateShader failed" << std::endl;
	}

	const char* src = filesrc.c_str();
	glShaderSource(handle, 1, &src, NULL);
	glCompileShader(handle);

	GLint result = GL_FALSE;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &result);

	if( result == GL_FALSE ){		
		GLint logLength;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
		
		char *logStr = new char[logLength + 1];
		glGetShaderInfoLog(handle, logLength, NULL, logStr);
		std::cerr << "Shader failed to compile with reason:\n" << logStr << std::endl;
		delete [] logStr;

		glDeleteShader(handle); 
		handle = 0;
		return;
	}
	refCount = new unsigned int;
	*refCount = 1;
}

Shader::~Shader() {
	if( refCount ){
		release();
	}
}

Shader::Shader(const Shader& b) {
	handle = b.handle;
	refCount = b.refCount;
	retain();
}

GLuint Shader::getHandle() const {
	return handle;
}

unsigned int Shader::getRefCount() const {
	if( !refCount ){
		return 0;
	}
	return *refCount;
}

Shader& Shader::operator=(const Shader& b) {
	release();
	handle = b.handle;
	refCount = b.refCount;
	retain();
	return *this;
}

void Shader::retain() {
	*refCount += 1;
}

void Shader::release() {
	*refCount -= 1;
	if( *refCount == 0 ){
		glDeleteShader(handle);
		handle = 0;
		delete refCount;
		refCount = NULL;
	}
}