#include "Scene.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Scene::Scene() {
	sceneMT = new MatrixTransform();
	
	forest = new Forest();
	terrain = new Terrain();
	player = new Player();
	enemy = new Enemy();
	fog = new FogMT();
	light = new LightMT();

	// init terrain structures
	if (terrain->terrainLoadFromImage("Resources/TGA/3dtech.tga", 1) != TERRAIN_OK)
		std::cerr << ("TERRAIN_OK is FALSE") << std::endl;;
	terrain->terrainScale(0, 40);

	sceneMT->addChild(terrain);
	sceneMT->addChild(forest);
	//sceneMT->addChild(player);
	//sceneMT->addChild(enemy);
	//sceneMT->addChild(fog);
	//sceneMT->addChild(light);
}

Scene::~Scene() {

}

void Scene::update() {
	//Fill in update logic for the entire scene
}

void Scene::draw(mat4 C) {
	//Draw the scene graph
	sceneMT->draw(C);


}


void Scene::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}