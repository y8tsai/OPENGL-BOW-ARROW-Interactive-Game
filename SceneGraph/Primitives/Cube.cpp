#include "Cube.h"

#include "Globals.h"
#include <GL/glut.h>
#include "SceneGraph/Creeper.h"


Cube::Cube() {
   
}

Cube::Cube(std::string EntityID) {
	visible = true;
	EID = EntityID;
	debug = false;
}

Cube::~Cube() {
	
}

void Cube::update() {

}

void Cube::render() {
	EntityNode *data = Globals::EntityStore->find(EID);
	glColor3f(1.f, 1.f, 1.f);
	if( data != NULL ){
		data->drawData.EnableShader();
		if( data->drawData.texture != nullptr ){
			if( data->drawData.multipleTex ){
				GLuint prog = data->drawData.shaders->getHandle();
				glUniform1i(glGetUniformLocation(prog, "SkinTex"), 0);
				glUniform1i(glGetUniformLocation(prog, "FaceTex"), 1);

				for( int i = 0; i < data->drawData.multipleTex; ++i ){
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, data->drawData.texture[i].getID());
				}
			}else{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, data->drawData.texture->getID());
			}
		}
		glBindVertexArray(data->drawData.vao);
		glDrawArrays(data->drawData.type, data->drawData.indexStart, data->drawData.indexCount);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(0);
		
		data->drawData.DisableShader();
	} else {
		glutSolidCube(1.f); //render a unit cube
	}
}