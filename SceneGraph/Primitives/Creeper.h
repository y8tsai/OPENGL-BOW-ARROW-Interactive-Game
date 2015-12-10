#ifndef __CREEP_H__
#define __CREEP_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Primitives/Cube.h"
#include "Entity/EntityNode.h"

/* 
This is a factory class that creates creepers
  
    Creeper objects are made up of 4 cube geodes,
    (1) Front Leg, (2)Back Leg, (3)Body, (4)Head  

	The root MT starts at the floor center point of model (0, 0, 0)
	but it's drawing routine is non-standard
	since it doesnt store any children,
	but can think of it's scene graph like so,
		
	Sapling->addChild(frontLegMT);		
		frontLegMT->addChild(frontLeg);			   SaplingMT( bottom centroid )
															|     |     |
	Sapling->addChild(backLegMT);				      backleg MT  |    frontleg MT        
		backLegMT->addChild(backLeg);                /            |               \
										Cube::backleg           body MT            Cube::frontleg
	Sapling->addChild(bodyMT);								   /     |
		bodyMT->addChild(body);                      Cube::body      |        
																	head MT  	
		bodyMT->addChild(headMT);								 	/  
			headMT->addChild(head);						  Cube::head		 
*/

class Creeper: public MatrixTransform {
public:
	static Creeper* MakeCreeper(mat4 m2w);
	
	// Only need to set values for Entity IDs if model for
	// each of the parts are created externally
	// OR you want different appearances and characteristics	
	static std::string __frontlegEID;
	static std::string __backlegEID;
	static std::string __bodyEID;
	static std::string __headEID;

	// Reference count keeping track of amount of creepers
	static int number; 
	

	Creeper(mat4 m2w, Cube* fl, Cube* bl, Cube *bdy, Cube* hd);
	~Creeper();
	
	void draw( mat4 C );
	void update(float t, float dt);

private:
	static Cube* CreateFrontLegModel(mat4 m2w);
	static Cube* CreateBackLegModel(mat4 m2w);
	static Cube* CreateBodyModel(mat4 m2w);
	static Cube* CreateHeadModel(mat4 m2w);
	static EntityNode* CreateEntity(std::string eid, const GLvoid *verts, GLsizeiptr vertsize, Program *prog = nullptr);
	static Texture* CreateTexture(std::string filename);
	static Texture* CreateFaceTexture(std::string faceFilename, std::string skinFilename);

	vec3 headLookAt;
	vec3 bodyLookAt;
	mat4 headRotation;
	mat4 bodyRotation;

	mat4 ft_legMT;
	mat4 bk_legMT;
	mat4 bodyMT;
	mat4 headMT;

	Cube *fr_leg;
	Cube *bk_leg;
	Cube *body;
	Cube *head;
};

#endif