#include "Tree.h"


Tree::Tree() {

}

Tree::~Tree() {

}

void Tree::draw(std::vector<CylinderMesh*>* parts) {
	glPushMatrix();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for( int i = 0; i < parts->size(); ++i ) {
		Verts *mesh = (*parts)[i]->ExportGLTriangleStrip();
		glColor3f(1.0f, 0.f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		for( int j = 0; j < mesh->size(); ++j ) {
			vec3 vert = (*mesh)[j];
			glVertex3f(vert.v[0], vert.v[1], vert.v[2]);
		}
		glEnd();
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//std::vector<DrawData*>::iterator iter = parts->begin();
	//while(iter != parts->end()) {
	//	//(*iter)->shaders->enable();
	//	//glActiveTexture(GL_TEXTURE0);
	//	//glBindTexture(GL_TEXTURE_2D, (*iter)->texture->getID());
	//	glBindVertexArray((*iter)->vao);
	//	glDrawElements(GL_TRIANGLE_STRIP, (*iter)->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);
	//	glBindVertexArray(0);
	//	//glBindTexture(GL_TEXTURE_2D, 0);
	//	//(*iter)->shaders->disable();
	//	++iter;
	//}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}