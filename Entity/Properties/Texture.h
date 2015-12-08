#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <string>
#include <SOIL2.h>

// SOIL will do all the loading of image formats for us.
// This class wraps SOIL library to hold information on texture, such as:
// texture ID
// dimensions

// Can use getID() to get ID and specify additional texture parameters

class Texture {
public:

	Texture();
	Texture(GLuint textureID, GLfloat w = 0.f, GLfloat h = 0.f);
	Texture(const std::string filepath, int force_ch = SOIL_LOAD_AUTO, unsigned int reuse = SOIL_CREATE_NEW_ID, unsigned int flags = 0);
	~Texture();

	GLuint getID() const;
	void setID(GLuint newtexid);
	GLfloat getWidth() const;
	GLfloat getHeight() const;

private:
	GLuint texid;
	GLfloat width;
	GLfloat height;
};


#endif
