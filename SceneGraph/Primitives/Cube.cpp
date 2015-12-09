#include "Cube.h"

#include "Globals.h"
#include <GL/glut.h>
#include "SceneGraph/Primitives/Creeper.h"


Cube::Cube() {
   
}

Cube::Cube(std::string EntityID, unsigned int cid) {
	EID = EntityID;
	CID = cid;
}

Cube::~Cube() {
	Globals::gPhysicsMgr.DeregisterPBody(CID);
}

void Cube::update(float t, float dt) {
	// Not used in cube AFAIK
}

void Cube::render() {
	EntityNode *data = Globals::EntityStore->find(EID);
	glColor3f(1.f, 1.f, 1.f);
	if( data != NULL ){
		data->drawData.EnableShader();
		if( data->drawData.texture != nullptr ){
			if( data->drawData.multipleTex && EID == Creeper::__headEID){
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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(0);
		
		data->drawData.DisableShader();
	} else {
		glutSolidCube(1.f); //render a unit cube
	}

	// janky but works, will take out bounding boxes from physics objects in a bit
	if( EID == "Arrow" && Globals::gPhysicsMgr.DebugDraw.__arrows ) {
		PBody *pb =Globals::gPhysicsMgr.GetPBody(CID);
		pb->bbox.DrawDebug();
	}
}