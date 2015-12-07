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
	MatrixTransform *tree1MT = new MatrixTransform();
	MatrixTransform *tree2MT = new MatrixTransform();
	MatrixTransform *tree3MT = new MatrixTransform();
	MatrixTransform *tree4MT = new MatrixTransform();

	int height = refSG->terrain->terrainGetHeight(0,0);
	tree0MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(0.f, (float)(height) - 0.3f, 0.f)));
	height = refSG->terrain->terrainGetHeight(6,-6);
	tree1MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(6.f, (float)(height) - 0.3f, -6.f)));
	height = refSG->terrain->terrainGetHeight(-6,0);
	tree2MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(-6.f, (float)(height) - 0.3f, 0.f)));
	height = refSG->terrain->terrainGetHeight(6,0);
	tree3MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(6.f, (float)(height) - 0.3f, 0.f)));
	height = refSG->terrain->terrainGetHeight(0,-6);
	tree4MT->setMatrix(mat4().makeIdentity().setTranslate(vec3(0.f, (float)(height) - 0.3f, -6.f)));

	forestMT->addChild(tree0MT);
	forestMT->addChild(tree1MT);
	forestMT->addChild(tree2MT);
	forestMT->addChild(tree3MT);
	forestMT->addChild(tree4MT);
	
	// Creating our first tree
	std::string treeSample = "Tree::sample";
	
	EntityNode *tree0_EN = new EntityNode();
	tree0_EN->name = treeSample;
	tree0_EN->parts = TreeGenerator.generate();
	refES->insert(tree0_EN);

	Tree *tree0 = new Tree(treeSample);
	Tree *tree1 = new Tree(treeSample);
	Tree *tree2 = new Tree(treeSample);
	Tree *tree3 = new Tree(treeSample);
	Tree *tree4 = new Tree(treeSample);

	tree0MT->addChild(tree0);
	tree1MT->addChild(tree1);
	tree2MT->addChild(tree2);
	tree3MT->addChild(tree3);
	tree4MT->addChild(tree4);

}

