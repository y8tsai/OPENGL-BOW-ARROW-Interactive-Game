#include "Skybox.h"
#include "Globals.h"

static const std::string faces[6] = {
	"Resources\\Textures\\mnight_ft.png",
	"Resources\\Textures\\mnight_bk.png",
	"Resources\\Textures\\mnight_up.png",
	"Resources\\Textures\\mnight_dn.png",
	"Resources\\Textures\\mnight_rt.png",
	"Resources\\Textures\\mnight_lf.png"
};


Skybox::Skybox(float size){
	this->size = size;

	GLfloat vertices[] = {
		// front													 // each face is made up of 2 triangles
		-size, size, -size, -size, -size, -size, size, -size, -size, // each triple is a vertex, 
		size, -size, -size, size, size, -size, -size, size, -size,	 // each line is a triangle
						
		// left
		-size, -size, size, -size, -size, -size, -size, size, -size,
		-size, size, -size, -size, size, size, -size, -size, size,
		
		// right
		size, -size, -size, size, -size, size, size, size, size,
		size, size, size, size, size, -size, size, -size, -size,

		// back
		-size, -size, size, -size, size, size, size, size, size,
		size, size, size, size, -size, size, -size, -size, size,

		// top
		-size, size, -size, size, size, -size, size, size, size,
		size, size, size, -size, size, size, -size, size, -size,
		
		// bottom
		-size, -size, -size, -size, -size, size, size, -size, -size,
		size, -size, -size, -size, -size, size, size, -size, size
	};
	glGenBuffers(1, &model.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &model.vao);
	glBindVertexArray(model.vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	model.shaders = Program::LoadShaders("Models/Shaders/Skybox.vert", "Models/Shaders/Skybox.frag");
	model.texture = new Texture();
	
	GLuint cubemap;
	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	int width, height;
	unsigned char *img;
	for(int i = 0; i < 6; ++i) {
		img = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	model.texture->setID(cubemap);
	model.indexStart = 0;
	model.indexCount = 6 * 2 * 3;
	
}




Skybox::~Skybox(){

}


void Skybox::draw(DrawData& dd) {
	glDepthMask(GL_FALSE);
	glPushMatrix();

	// Making the skybox move with the camera as to achieve parallax effect
	mat4 trs = mat4().makeIdentity().setTranslate(Globals::camera.eye).makeTranspose();
	glMultMatrixf(trs.ptr());
	
	/* Enabling shaders for environmental mapping 
	 * @see skybox.vert, skybox.frag
	 *
	 */
	model.shaders->enable();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, model.texture->getID());
	glBindVertexArray(model.vao);
	glDrawArrays(model.type, model.indexStart, model.indexCount);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	model.shaders->disable();

	
	glPopMatrix();
	glDepthMask(GL_TRUE);
}

void Skybox::update(UpdateData& ud) {

}