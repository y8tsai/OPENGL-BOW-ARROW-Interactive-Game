#include "Player.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Player::Player() {
	playerMT = new MatrixTransform();
	playerbodyMT = new MatrixTransform();
	bowMT = new MatrixTransform();
	arrowMT = new MatrixTransform();
	player = new Sphere();
	bow = new Cube();
	arrow = new Cube();

	//Arrow transform adds arrow geode as child
	arrowMT->addChild(arrow);

	//Bow transform adds arrowMT and bow geode as children
	bowMT->addChild(arrowMT);
	bowMT->addChild(bow);

	//PlayerbodyMT adds player geode as child
	playerbodyMT->addChild(player);

	//PlayerMT adds playerbodyMT and bowMT as children.
	playerMT->addChild(playerbodyMT);
	playerMT->addChild(bowMT);
	
}

Player::~Player() {
	//delete all dynamically allocated pointers
	delete player;
	delete bow;
	delete arrow;
	delete arrowMT;
	delete bowMT;
	delete playerbodyMT;
	delete playerMT;
}

void Player::update() {
	//add update logic
}

void Player::draw(mat4 C) {
	playerMT->draw(C);
}

void Player::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}