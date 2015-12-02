#include "Scene.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*Constants*/
// stuff for lighting
GLfloat lAmbient[] = { 0.3,0.3,0.3,1.0 };
GLfloat lDiffuse[] = { 1.0,1.0,1.0,1.0 };
GLfloat lSpecular[] = { 1.0,1.0,1.0,1.0 };

GLfloat lPosition[] = { 0.0,100.0,0.0,1.0 };

// materials
GLfloat mSpecular[] = { 1.0,1.0,1.0,1.0 };
// the smaller the larger the specular area is
GLfloat mShininess[] = { 128.0 };

//colors
GLfloat cBlack[] = { 0.0,0.0,0.0,1.0 };
GLfloat cOrange[] = { 1.0,0.5,0.5,1.0 };
GLfloat cWhite[] = { 1.0,1.0,1.0,1.0 };
GLfloat cGrey[] = { 0.1,0.1,0.1,1.0 };
GLfloat cLightGrey[] = { 0.9,0.9,0.9,1.0 };

Scene::Scene() {
	sceneMT = new MatrixTransform();
	
	forest = new Forest();
	terrain = new Terrain();
	player = new Player();
	enemy = new Enemy();
	fog = new FogMT();
	light = new LightMT();

	// init terrain structures
	if (terrain->terrainLoadFromImage("3dtech.tga", 1) != TERRAIN_OK)
		std::cerr << ("TERRAIN_OK is FALSE") << std::endl;;
	terrain->terrainScale(0, 40);


	sceneMT->addChild(terrain);
	//sceneMT->addChild(forest);
	sceneMT->addChild(player);
	//sceneMT->addChild(enemy);
	sceneMT->addChild(fog);
	sceneMT->addChild(light);
}

Scene::~Scene() {

}

void Scene::update() {
	//Fill in update logic for the entire scene
}

void Scene::draw(mat4 C) {
	sceneMT->draw(C);

	int terrainDL = terrain->terrainCreateDL(0, 0, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cGrey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cWhite);
	glCallList(terrainDL);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	//glutSwapBuffers();  //this causes access violation
}


void Scene::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}