#include "Tree.h"
#include "Globals.h"


Tree::Tree(std::string EntityID) {
	visible = true; // from Node
	EID = EntityID;
	debug = false;
}

Tree::~Tree() {

}

void Tree::render() {
	// (1) Grab data from EntityStore using EID
	EntityNode *data = Globals::EntityStore->find(EID);
	
	
	if( data != NULL ){
		// (2)[a] Setup draw calls and draw the object
		data->drawData.shaders->enable();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, data->drawData.texture->getID());
		for( int i = 0; i < data->vertices->size(); ++i ) {
			Verts *mesh = (*data->vertices)[i];
			glBegin(GL_TRIANGLE_STRIP);
			for( int j = 0; j < mesh->size(); j+=2 ) {				
				glTexCoord2f((*mesh)[j+1][0], (*mesh)[j+1][1]);
				glVertex3fv((*mesh)[j].ptr());
			}
			glEnd();
		}
		/*		glTexCoord2f(0,1);	
		glVertex3f(1,1,0);
		glTexCoord2f(0,0);
		glVertex3f(1,0,0);
		
		glTexCoord2f(0.33,1);
		glVertex3f(0,1,1);
		glTexCoord2f(0.33,0);
		glVertex3f(0,0,1);
		
		glTexCoord2f(0.66,1);
		glVertex3f(-1,1,0);
		glTexCoord2f(0.66,0);
		glVertex3f(-1,0,0);
		
		glTexCoord2f(1, 1);
		glVertex3f(0,1,-1);
		glTexCoord2f(1, 0);
		glVertex3f(0,0,-1);
		
		glTexCoord2f(0,1);
		glVertex3f(1,1,0);
		glTexCoord2f(0,0);
		glVertex3f(1,0,0);*/
		glBindTexture(GL_TEXTURE_2D, 0);
		data->drawData.shaders->disable();
		// (2)[b] If debug is set, draw debug too
		if( debug ){
			
		}

		// (3) Unset any GL configs during call
	}
}

void Tree::update() {
	// Nothing to update, trees dont move
	// unless we were to do wind simulation
}