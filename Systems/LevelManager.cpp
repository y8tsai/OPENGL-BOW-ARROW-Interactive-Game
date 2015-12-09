#include "LevelManager.h"
#include "Globals.h"

#include "Models/LSystem/LTree.h"
#include "SceneGraph/Primitives/Tree.h"
#include "SceneGraph/Creeper.h"

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


void LevelManager::LoadTestLevel() {
	// Creating player info
	PBody *player_pbody = new PBody(Globals::camera.eye, vec3(), 1.0f, false);
	player_pbody->SetAABB(vec3(0.0, 1.5, 0.0), vec3(0.5f, 1.5f, 0.5f)); 
	Globals::gPhysicsMgr.RegisterPBody(player_pbody);

	/*	Getting the Creepers Ready for Battle
	 ----------------------------------------------------------- */
	float theight = refSG->terrain->terrainGetHeight(0, -10);
	Creeper *creepsMT = Creeper::MakeCreeper(
		mat4().makeIdentity().setTranslate(vec3(0.f, theight+0.4f, -10.f))
	);

	refSG->addChild(creepsMT);
	
	Arrow *arrowMT = Arrow::MakeArrow(
		mat4().makeIdentity().setTranslate(vec3(0.f, theight+0.70f, -10.f)),
		vec3(1.2, 2.0, 0.0)
	);

	refSG->addChild(arrowMT);

	//Globals::EntityStore->insert(arrowEN);
	//Arrow *tempA = new Arrow("quick temp arrow");
	//MatrixTransform *ArrowMT = new MatrixTransform(mat4().makeIdentity().setTranslate(vec3(0.f, theight+30.f, -10.f)));
	//refSG->addChild(ArrowMT);
	//ArrowMT->addChild(tempA);

	//Fizzix::PBody *arrowpb = new PBody(vec3(0.f, theight+30.f, -10.f), vec3(0,0,0), 1.0f);
	//tempA->CID = Globals::gPhysicsMgr.RegisterPBody(arrowpb);


	/*	Making All the Trees
	 ----------------------------------------------------------- */
	//int NumberOfTrees = 300;
	//LTree TreeGenerator = LTree(0, LSysParam());
	//MatrixTransform *forestMT = new MatrixTransform();
	//refSG->addChild(forestMT);

	//std::string fernTree = "Tree::Fern Grammar";
	//EntityNode *treeSampleNode = TreeGenerator.generate();
	//treeSampleNode->name = fernTree;
	//refES->insert(treeSampleNode);

	//std::string niceTree = "Tree::Nice Grammar";
	//LSysParam niceTreeProp;
	//niceTreeProp.iterations = 5;
	//niceTreeProp.length = 0.12f;
	//niceTreeProp.rules['X'] = "F[+X]F[-X]+X";
	//niceTreeProp.rules['F'] = "FF";
	//niceTreeProp.startRule = 'X';

	//TreeGenerator.setProperties(niceTreeProp);
	//EntityNode *niceTreeNode = TreeGenerator.generate();
	//niceTreeNode->name = niceTree;
	//refES->insert(niceTreeNode);

	//std::string bushTree = "Tree::Bush Grammar";
	//LSysParam bushTreeProp;
	//bushTreeProp.iterations = 3;
	//bushTreeProp.length = 0.5f;
	//bushTreeProp.radius = 0.009f;
	//bushTreeProp.rules['F'] = "FF-[-F+F+F]+[+F-F-F]";
	//bushTreeProp.startRule = 'F';

	//TreeGenerator.setProperties(bushTreeProp);
	//EntityNode *bushTreeNode = TreeGenerator.generate();
	//bushTreeNode->name = bushTree;
	//refES->insert(bushTreeNode);


	/*std::string mysteryTree = "Tree::Mystery Grammar";
	LSysParam mysteryTreeProp;
	mysteryTreeProp.iterations = 4;
	mysteryTreeProp.length = 0.3f;
	mysteryTreeProp.radius = 0.08f;
	mysteryTreeProp.rules['F'] = "F[+F]F[-F]F";;
	mysteryTreeProp.startRule = 'F';*/

	/*TreeGenerator.setProperties(mysteryTreeProp);
	EntityNode *mysteryTreeNode = TreeGenerator.generate();
	mysteryTreeNode->name = mysteryTree;
	refES->insert(mysteryTreeNode);
	*/

	//MatrixTransform **treeMT = new MatrixTransform*[NumberOfTrees];
	//Tree **tree = new Tree*[NumberOfTrees];
	//for(int i = 0; i < NumberOfTrees; ++i) {
	//	treeMT[i] = new MatrixTransform();
	//	
	//	tree[i] = new Tree(fernTree);
	//	//if( i % 5 == 0) {
	//		//tree[i] = new Tree(mysteryTree);
	//	/*} else if( i % 4 == 0 ){
	//		tree[i] = new Tree(niceTree);
	//	} else if( i % 3 ) {
	//		
	//	} else {
	//		tree[i] = new Tree(bushTree);
	//	}*/
	//	int rx = (rand() % refSG->terrain->terrainGridWidth) - refSG->terrain->terrainGridWidth/2;
	//	int rz = (rand() % refSG->terrain->terrainGridLength) - refSG->terrain->terrainGridLength/2;
	//	int height = refSG->terrain->terrainGetHeight(rx,rz);
	//	treeMT[i]->setMatrix( mat4().makeIdentity().setTranslate( vec3(rx,(float)(height) - 0.3f, rz)) );
	//	treeMT[i]->addChild(tree[i]);
	//	forestMT->addChild(treeMT[i]);
	//}

}
