#include "Arrow.h"
#include "Globals.h"

#include "Models/ArrowModel.h"

std::string Arrow::__ArrowEID = "";
const float Arrow::lifetime = 500.f;

// Static Factory Method
Arrow* Arrow::MakeArrow(mat4 m2w, vec3 init_v) {
	if( __ArrowEID == "" ) {
		__ArrowEID = "Arrow";
		EntityNode *ArrowEN = CreateEntity(__ArrowEID, ArrowModel::Shaft, sizeof(ArrowModel::Shaft));
		Globals::EntityStore->insert(ArrowEN);
	}
	
	AABB *bbox = new AABB(m2w.getTranslate(), ArrowModel::BoundingBox[0], ArrowModel::BoundingBox[1], m2w.getRotation());
	AABB temp = *bbox;
	AABB::UpdateAABB(temp, *bbox);
	bbox->tag = "Arrow";
	unsigned int collision_id = Globals::ColStore->RegisterAABB(bbox);

	// Each geode object has it's own physics body unlike Entity used for drawing
	Fizzix::PBody *pb = new Fizzix::PBody(m2w.getTranslate(), init_v, 1.f);
	pb->CID = collision_id;
	unsigned int physics_id = Globals::gPhysicsMgr.RegisterPBody(pb);

	Arrow *projectile = new Arrow(m2w, __ArrowEID, physics_id, collision_id);

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

Arrow::Arrow(mat4 m2w, std::string EntityID, unsigned int pid, unsigned int cid): MatrixTransform(m2w) {
	model = new Cube(EntityID, pid, cid);
	timeUntilDel = 0.f;
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

		if(Globals::gPhysicsMgr.DebugDraw.__arrows) {
			AABB* info = Globals::ColStore->GetAABBInfo(model->CID);
			Fizzix::PBody *body = Globals::gPhysicsMgr.GetPBody(model->PID);

			if(!body->staticBody && info != nullptr) {
				HitList hits;
				Globals::ColStore->Query(model->CID, hits);
				if( hits.size() ) {
					std::cout << "draw hit box" << std::endl;
					info->DrawDebug(C * M, true);
				} else {
					std::cout << "draw box" << std::endl;
					info->DrawDebug(C * M);
				}

			}
		}
	}
}

void Arrow::update(float t, float dt) {
	//collision id -> AABB will also be fetched here for updating

	AABB *bbox =  Globals::ColStore->GetAABBInfo(model->CID);
	Fizzix::PBody *info = Globals::gPhysicsMgr.GetPBody(model->PID);
	if( !info->staticBody) {
		vec3 currPstn = info->position;
		float boundaryX = (float)Globals::SceneGraph->terrain->terrainGridWidth/2.f;
		float boundaryZ = (float)Globals::SceneGraph->terrain->terrainGridLength/2.f;
		float hitFloor = Globals::SceneGraph->terrain->terrainGetHeight((int)currPstn[0], (int)currPstn[2]);

		if(bbox != nullptr) {
			bbox->position = info->position;
			HitList hits;
			Globals::ColStore->Query(model->CID, hits);
			
			if(hits.size()) {
				info->staticBody = true;
				timeUntilDel = 480.f;
			}
		}

		if( currPstn[0] > boundaryX || currPstn[0] < -boundaryX || currPstn[2] < -boundaryZ || currPstn[2] > boundaryZ) {
			visible = false;
			Globals::ColStore->RemoveAABBInfo(model->CID);
			model->CID = 0;
			info->staticBody = true;
			cleanup = true;
		}

		if( currPstn[1] < hitFloor) {
			Globals::ColStore->RemoveAABBInfo(model->CID);
			model->CID = 0;
			info->position[1] = hitFloor;
			info->staticBody = true;
			info->velocity = vec3(); //loses all momentum
		}
		M.setTranslate( info->position );
	} else {
		++timeUntilDel;
		if ( timeUntilDel >= Arrow::lifetime) {
			cleanup = true; // tell top level MT to delete
		}
	}
	
}