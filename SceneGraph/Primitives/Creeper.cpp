#include "Creeper.h"
#include "Globals.h"

#include "Models/CreeperModel.h"

std::string Creeper::__frontlegEID = "";
std::string Creeper::__backlegEID = "";
std::string Creeper::__bodyEID = "";
std::string Creeper::__headEID = "";

int Creeper::number = 0;

/* Factory Method
 * ----------------------------------------------- */
Creeper* Creeper::MakeCreeper(mat4 m2w) {
	Creeper::number++;

	vec3 btrans = m2w.getTranslate();
	btrans[1] += 6.f;
	AABB* bbox = new AABB(btrans, {0.f, 5.5f, 0.f }, {1.f, 3.0f, 1.f} ,m2w.getRotation());
	bbox->tag = "Creeper";
	unsigned int cid = Globals::ColStore->RegisterAABB(bbox);

	// m2w would should be center position of front leg in world coordinates
	Cube *frontLeg = CreateFrontLegModel(m2w, cid), 
		 *backLeg = CreateBackLegModel(m2w, cid),
		 *body = CreateBodyModel(m2w, cid),
		 *head = CreateHeadModel(m2w, cid);

	// Creeper's draw call is modified to not traverse tree
	// Since it's one unit, it will store references to its
	// constituents and draw all at once
	// A bit not standard, this one
	Creeper *Sapling = new Creeper(m2w, frontLeg, backLeg, body, head);

	


	// creating a physics body
	Fizzix::PBody *pb = new Fizzix::PBody(m2w.getTranslate(), vec3(0.f,0.f,0.5f), 1.f);
	int PID = Globals::gPhysicsMgr.RegisterPBody(pb);

	return Sapling;
}

/* Factory Helper Functions:: Auto-creates Entity
 * ----------------------------------------------- */
Cube* Creeper::CreateFrontLegModel(mat4 m2w, unsigned int cid) {
	//If internal EID is empty, use 
	if( __frontlegEID == "" ){
		__frontlegEID = "Creeper::FrontLeg";
		EntityNode *frontlegEN = CreateEntity(__frontlegEID, CreeperModel::FrontLeg, sizeof(CreeperModel::FrontLeg));
		frontlegEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(frontlegEN);
	}

	return new Cube(__frontlegEID, 0, cid);
}

Cube* Creeper::CreateBackLegModel(mat4 m2w, unsigned int cid) {
	if( __backlegEID == "" ){
		__backlegEID = "Creeper::BackLeg";
		EntityNode *backlegEN = CreateEntity(__backlegEID, CreeperModel::BackLeg, sizeof(CreeperModel::BackLeg));
		backlegEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(backlegEN);
	}

	return new Cube(__backlegEID, 0, cid);
}

Cube* Creeper::CreateBodyModel(mat4 m2w, unsigned int cid) {
	if( __bodyEID == "" ){
		__bodyEID = "Creeper::Body";
		EntityNode *bodyEN = CreateEntity(__bodyEID, CreeperModel::Body, sizeof(CreeperModel::Body));
		bodyEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(bodyEN);
	}

	return new Cube(__bodyEID, 0, cid);
}

Cube* Creeper::CreateHeadModel(mat4 m2w, unsigned int cid) {
	if( __headEID == "" ){
		__headEID = "Creeper::Head";
		Program *shade = Program::LoadShaders("Models/Shaders/CreeperFace.vs", "Models/Shaders/CreeperFace.fs");
		EntityNode *headEN = CreateEntity(__headEID, CreeperModel::Head, sizeof(CreeperModel::Head), shade);
		headEN->drawData.texture = CreateFaceTexture(CreeperModel::CreeperFace, CreeperModel::CreeperSkin);
		headEN->drawData.multipleTex = 2;
		headEN->drawData.shaders = shade;
		Globals::EntityStore->insert(headEN);
	}

	return new Cube(__headEID, 0, cid);
}

// Creates an Entity Node and fills in vbo vao
EntityNode* Creeper::CreateEntity(std::string eid, const GLvoid *verts, GLsizeiptr vertsize, Program *prog) {
	EntityNode *genEN = new EntityNode();
	genEN->name = eid;
	genEN->drawData.type = GL_TRIANGLES;
	genEN->drawData.indexStart = 0;
	genEN->drawData.indexCount = 2*3*6;

	glGenVertexArrays(1, &genEN->drawData.vao);
	glBindVertexArray(genEN->drawData.vao);

	glGenBuffers(1, &genEN->drawData.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, genEN->drawData.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsize, verts, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (const GLvoid*)0 );

	glEnableVertexAttribArray(8); 
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE,  6*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(9); 
	glVertexAttribPointer(9, 1, GL_FLOAT, GL_FALSE,  6*sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

	glBindVertexArray(0);

	return genEN;
}

Texture* Creeper::CreateTexture(std::string filename) {
	GLuint texid;
	glGenTextures(1, &texid);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texid);
	int w, h;
	unsigned char *img = SOIL_load_image(filename.c_str(), &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
	
	return new Texture(texid, w, h);
}

Texture* Creeper::CreateFaceTexture(std::string faceFilename, std::string skinFilename) {
	GLuint texid[2];
	glGenTextures(2, &texid[0]);
	Texture *tex = new Texture[2];

	for( int i = 0; i < 2; ++i ){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texid[i]);
		
		int w, h;
		const char *filename = (i == 0 ? skinFilename.c_str() : faceFilename.c_str()); 
		unsigned char *img = SOIL_load_image(filename, &w, &h, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glActiveTexture(0);
		tex[i].setID(texid[i]);
	}
	return tex;
}

// Creeper Object (MT) Implementation
Creeper::Creeper(mat4 m2w, Cube* fl, Cube* bl, Cube *bdy, Cube* hd) : MatrixTransform(m2w) {
	fr_leg = fl;
	bk_leg = bl;
	body = bdy;
	head = hd;

	//for updating the creeper
	headLookAt = vec3(0.0, 0.0, 1.0); //only used by head
	bodyLookAt = vec3(0.0, 0.0, 1.0); //shared by body and legs
	headRotation = mat4().makeIdentity();
	bodyRotation = mat4().makeIdentity();

	ft_legMT = mat4().makeIdentity().setTranslate(vec3(0.f, 0.f, 1.f ));
	bk_legMT = mat4().makeIdentity().setTranslate(vec3(0.f, 0.f, -0.6f));
	bodyMT = mat4().makeIdentity().setTranslate(vec3(0.f, 1.96f, 0.2f));
	headMT = mat4().makeIdentity().setTranslate(vec3(0.f, 2.5f, 0.f));
	EXPLODE = false;
	timeUntilDel = 0.f;
}

Creeper::~Creeper() {
	
	if(fr_leg != nullptr) delete fr_leg;
	if(bk_leg != nullptr) delete bk_leg;
	if(body != nullptr) delete body;
	if(head != nullptr) delete head;
	
	fr_leg = nullptr;
	bk_leg = nullptr;
	body = nullptr;
	head = nullptr;

	Creeper::number--;
}

void Creeper::draw( mat4 C ) {
    C = C * M;

	fr_leg->draw(C * ft_legMT);
	bk_leg->draw(C * bk_legMT);
	C = C * bodyMT;
	if(Globals::gPhysicsMgr.DebugDraw.__enemies) {
		AABB* bb = Globals::ColStore->GetAABBInfo(body->CID);	

		if( bb != nullptr ){
			HitList hits;
			Globals::ColStore->Query(body->CID, hits);
			if(hits.size()) {
				bb->DrawDebug(C, true);
			} else {
				bb->DrawDebug(C);
			}
		}
	}
	body->draw(C);
	head->draw(C * headMT);
}

static float lifetime = 0.15f; // 0.2 second after collision, EXPLODE
void Creeper::update(float t, float dt) {
	
	if( !EXPLODE ) {
		// Animation in only this block
		vec3 camPos = Globals::camera.eye;
		vec3 crpPos = bodyMT.getTranslate() + headMT.getTranslate() + vec3(0, 0, -10);
		vec3 disToCamXZ = camPos - crpPos;
		disToCamXZ[1] = 0; // we dont want y comp for rotation around y
		disToCamXZ.normalize();
		float dotProd = disToCamXZ.dot(headLookAt);
		if (dotProd > 1.0f)
			dotProd = 0.999f;
		else if (dotProd < -1.0f)
			dotProd = -0.999f;
		float angleY = acos(dotProd) * 180 / PI;
		if (disToCamXZ[0] < 0)
			angleY = angleY * -1;
	
		mat4 rotY = mat4().makeRotateY(angleY);
		HitList hits;
		Globals::ColStore->Query(body->CID, hits);
		if(hits.size()) {
			EXPLODE = true;
			Globals::ColStore->RemoveAABBInfo(body->CID);
			body->CID = 0;
		}

		if (angleY < -0.5 || angleY > 0.5) {
			//std::cout << "dotProd is: " << dotProd << std::endl;
			//std::cout << "distToCamXZ: " << distToCamXZ[0] << ", " << distToCamXZ[1] << ", " << distToCamXZ[2] << std::endl;
			//std::cout << "HeadLookAt: " << headLookAt[0] << ", " << headLookAt[1] << ", " << headLookAt[2] << std::endl;
			//std::cout << "AngleY: " << angleY << std::endl << std::endl;
			headRotation = rotY;										//update rotation matrix
			bodyRotation = rotY;										//update rotation matrix
			headLookAt = headRotation * headLookAt;					//update lookAt vectors
			bodyLookAt = bodyRotation * bodyLookAt;
			headMT = headMT * headRotation;								//apply transformations to each body part
			bodyMT = bodyMT * bodyRotation;
			ft_legMT = ft_legMT * bodyRotation;
			bk_legMT = bk_legMT * bodyRotation;
		}
	} else {
		if( timeUntilDel >= lifetime ) {
			Globals::SceneGraph->addChild(new Particles(1000, M.getTranslate() )); 
			
			cleanup = true;	
		} else {
			timeUntilDel += dt;
		}
	}

}
        