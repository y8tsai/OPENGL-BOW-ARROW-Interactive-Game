#include "LevelManager.h"
#include "Globals.h"

#include "Entity/EntityNode.h"
#include "SceneGraph/Primitives/Tree.h"
#include "SceneGraph/Primitives/Creeper.h"
#include "SceneGraph/Primitives/Arrow.h"

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
}

void LevelManager::StartUp() {
	refSG = new Scene();
	refES = new EntityBST();

	Globals::SceneGraph = refSG;
	Globals::EntityStore = refES;

	LoadTestLevel();
}

void LevelManager::Shutdown() {
	delete refSG;
	delete refES;
}

static float interval_ms = 0.f;
void LevelManager::EventUpdate(float t, float dt) {
	// Want to load a creeper every 5 -> 10 seconds
	if( interval_ms < 0.f ) {
		interval_ms = (float)((std::rand() % 6) + 5);
		std::cout << "Load creeper. Next one in " << interval_ms << " seconds" << std::endl;
		refSG->addChild(LoadCreeperRandom());
	} else {
		interval_ms = interval_ms - dt;
	}
}

void LevelManager::LoadTestLevel() {
	// Creating player info
	PBody *player_pbody = new PBody(Globals::camera.eye, vec3(), 1.0f, false);	
	Globals::gPhysicsMgr.RegisterPBody(player_pbody);

	AABB *player_bbox = new AABB( Globals::camera.eye, vec3(0.0, 1.5, 0.0), vec3(0.5f, 1.5f, 0.5f), mat3());
	Globals::ColStore->RegisterAABB( player_bbox );

	/*	Getting the Creepers Ready for Battle
	 ----------------------------------------------------------- */
/*	float theight = refSG->terrain->terrainGetHeight(0, -10);
	Creeper *creepsMT = Creeper::MakeCreeper(
		mat4().makeIdentity().setTranslate(vec3(0.f, theight+0.4f, -10.f))
	);
	refSG->addChild(creepsMT)*/;


	//float theight = refSG->terrain->terrainGetHeight(0, 10);
	//Creeper *BBTest = Creeper::MakeCreeper(
	//	mat4().makeIdentity().setTranslate(vec3(0.f, theight+0.4f, 10.f))
	//);
	//refSG->addChild(BBTest);

	/*	Making All the Trees
	 ----------------------------------------------------------- */
	//refSG->addChild(LoadTrees(1));
}

MatrixTransform* LevelManager::LoadCreeperRandom() {
	
	// TODO:: Generate Random Spot for Creeper to load
	// int x = /* random float here within bounds of terrain */

	// Bounds for creeper location is:
	// Camera.eye[0] + 20 < x_maxpos <  + terrain.width/2
	// Camera.eye[0] - 20 < x_minpos <  - terrain.width/2
	//
	// x_finalpos is then whichever's absolute pstn is greater
	//
	// Ditto for z using Camera.eye[2] && (terrain.height/2)

	// int z = /* random float here within bounds of terrain */
	// int height = /* use terrain get height for this */

	/* TODO:: make a creeperMT

	Creeper *creepsMT = Creeper::MakeCreeper(
		// random position, but make sure the height is on terrain 
		// use mat4.translate(vec3).
	);
	
	*/
		
	// return creepsMT; // uncommment this when done
	return nullptr;
}


MatrixTransform* LevelManager::LoadTrees(int amount) {
	MatrixTransform *forestMT = new MatrixTransform();

	LTree TreeGenerator = LTree(0, LSysParam());
	treeGrammars = new LSysParam[3];
	std::string fernTree = "Tree::Fern Grammar";
	std::string niceTree = "Tree::Nice Grammar";
	std::string bushTree = "Tree::Bush Grammar";
	std::string stalkyTree = "Tree::StalkyTree";
		
	treeGrammars[0].iterations = 5;
	treeGrammars[0].length = 0.12f;
	treeGrammars[0].rules['X'] = "F[+X]F[-X]+X";
	treeGrammars[0].rules['F'] = "FF";
	treeGrammars[0].startRule = 'X';

	LSysParam bushTreeProp;
	treeGrammars[1].iterations = 3;
	treeGrammars[1].length = 0.5f;
	treeGrammars[1].radius = 0.009f;
	treeGrammars[1].rules['F'] = "FF-[-F+F+F]+[+F-F-F]";
	treeGrammars[1].startRule = 'F';

	treeGrammars[2].iterations = 4;
	treeGrammars[2].length = 0.3f;
	treeGrammars[2].radius = 0.08f;
	treeGrammars[2].rules['F'] = "F[+F]F[-F]F";;
	treeGrammars[2].startRule = 'F';

	// Default LSysParam is a fern grammar
	EntityNode *fernTreeNode = TreeGenerator.generate();
	fernTreeNode->name = fernTree;
	refES->insert(fernTreeNode);
	
	TreeGenerator.setProperties(treeGrammars[0]);
	EntityNode *niceTreeNode = TreeGenerator.generate();
	niceTreeNode->name = niceTree;
	refES->insert(niceTreeNode);

	TreeGenerator.setProperties(treeGrammars[1]);
	EntityNode *bushTreeNode = TreeGenerator.generate();
	bushTreeNode->name = bushTree;
	refES->insert(bushTreeNode);

	TreeGenerator.setProperties(treeGrammars[2]);
	EntityNode *stalkyTreeNode = TreeGenerator.generate();
	stalkyTreeNode->name = stalkyTree;
	refES->insert(stalkyTreeNode);

	int type = 0;
	MatrixTransform **treeMT = new MatrixTransform*[amount];
	Tree **tree = new Tree*[amount];
	for(int i = 0; i < amount; ++i) {
		treeMT[i] = new MatrixTransform();

		if( i % 4 == 0 ){ tree[i] = new Tree(fernTree, 0, 0);
		}else if(i % 4 == 1){ tree[i] = new Tree(niceTree, 0, 0);
		}else if(i % 4 == 2){ tree[i] = new Tree(bushTree, 0, 0);
		}else{ 
			tree[i] = new Tree(stalkyTree, 0, 0); 
		}
		
		int rx = 0, height = 0, rz = 0;
		if( refSG->terrain != nullptr ) {
			rx = (rand() % refSG->terrain->terrainGridWidth) - refSG->terrain->terrainGridWidth/2;
			rz = (rand() % refSG->terrain->terrainGridLength) - refSG->terrain->terrainGridLength/2;
			height = refSG->terrain->terrainGetHeight(rx,rz);
		}
		treeMT[i]->setMatrix( mat4().translate( vec3(rx,(float)(height) - 0.3f, rz)) );
		treeMT[i]->setMatrix( mat4().translate( vec3(rx,(float)(height) - 0.3f, rz)) );

		treeMT[i]->addChild(tree[i]);
		forestMT->addChild(treeMT[i]);
	}

	return forestMT;
}