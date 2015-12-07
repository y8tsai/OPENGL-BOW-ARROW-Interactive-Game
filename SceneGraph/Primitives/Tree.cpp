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
		for( int i = 0; i < data->parts->size(); ++i ) {
			Verts *mesh = (*data->parts)[i]->ExportGLTriangleStrip();
			glColor3f(1.0f, 0.f, 0.5f);
			glBegin(GL_TRIANGLE_STRIP);
			for( int j = 0; j < mesh->size(); ++j ) {
				vec3 vert = (*mesh)[j];
				glVertex3f(vert.v[0], vert.v[1], vert.v[2]);
			}
			glEnd();
		}

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