#include "Scene.h"
#include <GL/glut.h>

Scene::Scene() {
	sceneMT = new MatrixTransform();
	terrain = new Terrain();

	// init terrain structures
	if (terrain->terrainLoadFromImage("Resources/TGA/3dtech.tga", 1) != TERRAIN_OK)
		std::cerr << ("TERRAIN_OK is FALSE") << std::endl;;
	terrain->terrainScale(0, 40);

	sceneMT->addChild(terrain);
}

Scene::~Scene() {
}

void Scene::addChild(Node *n) {
	if( n != nullptr) {
		sceneMT->addChild(n);
	}
}

void Scene::draw(mat4 C) {
	//Draw the scene graph
	sceneMT->draw(C);
}

void Scene::update(float t, float dt) {
	sceneMT->update(t, dt);
}