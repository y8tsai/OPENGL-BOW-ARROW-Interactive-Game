#include "LevelManager.h"
#include "Globals.h"

#include "Models/LSystem/LTree.h"
#include "SceneGraph/Primitives/Tree.h"

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
	LTree TreeGenerator = LTree(0, LSysParam());


	MatrixTransform *forestMT = new MatrixTransform();
	refSG->addChild(forestMT);

	MatrixTransform *tree0MT = new MatrixTransform();
	int height = refSG->terrain->terrainGetHeight(0,0);
	tree0MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(0.f, (float)(height) - 0.3f, 0.f)));
	forestMT->addChild(tree0MT);
	
	// Creating our first tree
	std::string tree0_ID = "Tree::sample0";
	
	EntityNode *tree0_EN = new EntityNode();
	tree0_EN->name = tree0_ID;
	tree0_EN->parts = TreeGenerator.generate();
	refES->insert(tree0_EN);

	Tree *sampleTree = new Tree(tree0_ID);
	tree0MT->addChild(sampleTree);

}

