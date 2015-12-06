#include "Texture.h"

Texture::Texture() {
	width = 0;
	height = 0;
	texid = 0;
}

Texture::Texture(const std::string filepath, int force_ch, unsigned int reuse, unsigned int flags) {
	texid = SOIL_load_OGL_texture( filepath.c_str(), force_ch, reuse, flags );
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	width = 0;
	height = 0;
	glDeleteTextures(GL_TEXTURE_2D, &texid);
}

GLuint Texture::getID() const {
	return texid;
}

void Texture::setID(GLuint newtexid) {
	texid = newtexid;
}


GLfloat Texture::getWidth() const {
	return width;
}

GLfloat Texture::getHeight() const {
	return height;
}