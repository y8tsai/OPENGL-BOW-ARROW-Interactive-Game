#include "Arrow.h"
#include "Globals.h"

#include "Models/ArrowModel.h"

std::string Arrow::__ArrowEID = "";
const float Arrow::lifetime = 1000.f; //Not Used

// Static Factory Method
Arrow* Arrow::MakeArrow(mat4 m2w, vec3 init_v, quat rot) {
	if( __ArrowEID == "" ) {
		__ArrowEID = "Arrow";
		EntityNode *ArrowEN = CreateEntity(__ArrowEID, ArrowModel::Shaft, sizeof(ArrowModel::Shaft));
		Globals::EntityStore->insert(ArrowEN);
	}

	// Each geode object has it's own physics body unlike Entity used for drawing
	Fizzix::PBody *pb = new Fizzix::PBody(m2w.getTranslate(), init_v, 1.f);
	pb->SetAABB(ArrowModel::BoundingBox[0], ArrowModel::BoundingBox[1]);
	unsigned int collision_id = Globals::gPhysicsMgr.RegisterPBody(pb);

	Arrow *projectile = new Arrow(m2w, __ArrowEID, collision_id);

	return projectile;
}

 EntityNode* Arrow::CreateEntity(std::string eid, const GLvoid *verts, GLsizeiptr vertsize) {
	EntityNode *arrowEN = new EntityNode();
	arrowEN->name = eid;
	arrowEN->drawData.type = GL_TRIANGLES;
	arrowEN->drawData.indexStart = 0;
	arrowEN->drawData.indexCount = 2*3*6;
	
	glGenVertexArrays(1, &arrowEN->drawData.vao);
	glBindVertexArray(arrowEN->drawData.vao);
	glGenBuffers(1, &arrowEN->drawData.vbo);

	glBindBuffer(GL_ARRAY_BUFFER, arrowEN->drawData.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ArrowModel::Shaft), ArrowModel::Shaft, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (const GLvoid*)0 );

	glEnableVertexAttribArray(3); 
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,  6*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	
	glBindVertexArray(0);
	
	return arrowEN;
 }

Arrow::Arrow(): MatrixTransform() {
	model = nullptr;
}

Arrow::Arrow(mat4 m2w, std::string EntityID, unsigned int cid): MatrixTransform(m2w) {
	model = new Cube(EntityID, cid);
}

Arrow::~Arrow() {
	if( model != nullptr ) {
		delete model;
	}
	model = nullptr;
}

void Arrow::draw( mat4 C ) {
	if( visible ) {
		model->draw(C * M);
	}
}

void Arrow::update(float t, float dt) {
	Fizzix::PBody *info = Globals::gPhysicsMgr.GetPBody(model->CID);
	if( !info->staticBody) {
		vec3 currPstn = info->position;
		float boundaryX = (float)Globals::SceneGraph->terrain->terrainGridWidth/2.f;
		float boundaryZ = (float)Globals::SceneGraph->terrain->terrainGridLength/2.f;
		float hitFloor = Globals::SceneGraph->terrain->terrainGetHeight((int)currPstn[0], (int)currPstn[2]);
		if( currPstn[0] > boundaryX || currPstn[0] < -boundaryX || currPstn[2] < -boundaryZ || currPstn[2] > boundaryZ) {
			cleanup = true;
			visible = false;
			info->staticBody = true;	
		}

		if( currPstn[1] < hitFloor) {
			info->position[1] = hitFloor;
			info->staticBody = true;
			info->velocity = vec3(); //loses all momentum
			cleanup = true;
			// will be scenegraph's job to delete
		}
		M.setTranslate( info->position );
	}
}


//void Arrow::draw(DrawData& dd) {
//	
//	glLineWidth(1.0f);
//	glBegin(GL_LINES);
//	for(std::size_t i=0; i < debug_trace.size();++i) {
//		glColor3fv(tracecolor.ptr());
//		vec3 trace = debug_trace[i];
//		glVertex3fv( trace.ptr() );
//	}
//}
//
//void Arrow::update(UpdateData& ud) {
//	// mark delete if out of playing field
//	if(abs(position.v[0]) > 100.f || abs(position.v[1]) > 100.f || abs(position.v[2]) > 100.f) {
//		markDelete = true;
//	} else {
//		debug_trace.push_back(position);
//		velocity = velocity + acceleration;
//		position = position + velocity;
//		debug_trace.push_back(position);
//		toWorld.setTranslate(position);
//	}
//}
//
