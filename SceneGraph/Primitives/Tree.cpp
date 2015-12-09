#include "Tree.h"
#include "Globals.h"

Tree::Tree() {
	visible = true; // from Node
}

Tree::Tree(std::string EntityID) {
	visible = true; // from Node
	EID = EntityID;
}

Tree::~Tree() {

}

void Tree::render() {
	// (1) Grab data from EntityStore using EID
	EntityNode *data = Globals::EntityStore->find(EID);
	
	
	if( data != NULL ){
		// (2)[a] Setup draw calls and draw the object
		data->drawData.EnableShader();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, data->drawData.texture->getID());
		for( int i = 0; i < data->vertices->size(); ++i ) {
			Verts *mesh = (*data->vertices)[i];
			glBegin(GL_TRIANGLE_STRIP);
			for( int j = 0; j < mesh->size(); j+=2 ) {		
				glVertexAttrib2f(8, (*mesh)[j+1][0], (*mesh)[j+1][1]);
				glVertex3fv((*mesh)[j].ptr());
			}
			glEnd();
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(0);
		
		data->drawData.DisableShader();
		// (3) Unset any GL configs during call
	}
}

void Tree::update() {
	// Nothing to update, trees dont move
	// unless we were to do wind simulation
}