#include "Creeper.h"
#include "Globals.h"

#include "Models/CreeperModel.h"

std::string Creeper::__frontlegEID = "";
std::string Creeper::__backlegEID = "";
std::string Creeper::__bodyEID = "";
std::string Creeper::__headEID = "";

int Creeper::cid = 0;
int Creeper::number = 0;

/* Factory Method
 * ----------------------------------------------- */
Creeper* Creeper::MakeCreeper(mat4 m2w) {
	//TODO: put in collision store
	Creeper::cid++;
	Creeper::number++;

	// m2w would should be center position of front leg in world coordinates
	Cube *frontLeg = CreateFrontLegModel(), 
		 *backLeg = CreateBackLegModel(),
		 *body = CreateBodyModel(),
		 *head = CreateHeadModel();

	// Creeper's draw call is modified to not traverse tree
	// Since it's one unit, it will store references to its
	// constituents and draw all at once
	// A bit not standard, this one
	Creeper *Sapling = new Creeper(m2w, frontLeg, backLeg, body, head);
	return Sapling;
}

/* Factory Helper Functions:: Auto-creates Entity
 * ----------------------------------------------- */
Cube* Creeper::CreateFrontLegModel() {
	//If internal EID is empty, use 
	if( __frontlegEID == "" ){
		__frontlegEID = "Creeper::FrontLeg";
		EntityNode *frontlegEN = CreateEntity(__frontlegEID, CreeperModel::FrontLeg, sizeof(CreeperModel::FrontLeg));
		frontlegEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(frontlegEN);
	}
	return new Cube(__frontlegEID);
}

Cube* Creeper::CreateBackLegModel() {
	if( __backlegEID == "" ){
		__backlegEID = "Creeper::BackLeg";
		EntityNode *backlegEN = CreateEntity(__backlegEID, CreeperModel::BackLeg, sizeof(CreeperModel::BackLeg));
		backlegEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(backlegEN);
	}
	return new Cube(__backlegEID);
}

Cube* Creeper::CreateBodyModel() {
	if( __bodyEID == "" ){
		__bodyEID = "Creeper::Body";
		EntityNode *bodyEN = CreateEntity(__bodyEID, CreeperModel::Body, sizeof(CreeperModel::Body));
		bodyEN->drawData.texture = CreateTexture(CreeperModel::CreeperSkin);
		Globals::EntityStore->insert(bodyEN);
	}
	return new Cube(__bodyEID);
}

Cube* Creeper::CreateHeadModel() {
	if( __headEID == "" ){
		__headEID = "Creeper::Head";
		Program *shade = Program::LoadShaders("Models/Shaders/CreeperFace.vs", "Models/Shaders/CreeperFace.fs");
		EntityNode *headEN = CreateEntity(__headEID, CreeperModel::Head, sizeof(CreeperModel::Head), shade);
		headEN->drawData.texture = CreateFaceTexture(CreeperModel::CreeperFace, CreeperModel::CreeperSkin);
		headEN->drawData.multipleTex = 2;
		headEN->drawData.shaders = shade;
		Globals::EntityStore->insert(headEN);
	}
	return new Cube(__headEID);
}

// Creates an Entity Node and fills in vbo vao
EntityNode* Creeper::CreateEntity(std::string eid, const GLvoid *verts, GLsizeiptr vertsize, Program *prog) {
	EntityNode *genEN = new EntityNode();
	genEN->name = eid;
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
		printf( "SOIL loading error: %i '%s'\n",i, SOIL_last_result() );
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
	M = m2w;
	fr_leg = fl;
	bk_leg = bl;
	body = bdy;
	head = hd;
	
	ft_legMT = mat4().makeIdentity().setTranslate(vec3(0.f, 0.f, 1.f ));
	bk_legMT = mat4().makeIdentity().setTranslate(vec3(0.f, 0.f, -0.6f));
	bodyMT = mat4().makeIdentity().setTranslate(vec3(0.f, 1.96f, 0.2f));
	headMT = mat4().makeIdentity().setTranslate(vec3(0.f, 2.5f, 0.f));
}

Creeper::~Creeper() {
	delete fr_leg;
	delete bk_leg;
	delete body;
	delete head;
	
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
	body->draw(C);
	head->draw(C * headMT);
}

        