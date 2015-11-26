#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <string>

/*
Shader type
GL_VERTEX_SHADER
GL_FRAGMENT_SHADER
*/


/*
Use shaderFromFile as factory method. 
Constructor will compile shader file with given filePath and type.
Stores a reference id, GLuint, of compiled shader that resides in GPU

Collect all the shaders in a list and pass it to Program for use, which
will batch process and link to whichever opengl context you specify
*/

class Shader {
public:
	static Shader shaderFromFile(const std::string &filePath, GLenum type);

	Shader(const std::string& src, GLenum type);
	~Shader();
	// Can be copied and assigned because they are reference counted
	// What does it mean to be reference counted? 
	// There will only be 1 instance of a given shader shared by all objects that need it
	// For each object that uses said shader, increment reference by 1
	// When object using shader falls out of scope or not needed, decrement reference by 1
	// When reference count is 0, garbage collect to save resources
	Shader(const Shader&); //copy constructor
	Shader& operator =(const Shader&); //assignment overload

	GLuint getHandle() const;
	unsigned int getRefCount() const;


private:
	GLuint handle;
	unsigned int* refCount;

	void retain();
	void release();
};


#endif