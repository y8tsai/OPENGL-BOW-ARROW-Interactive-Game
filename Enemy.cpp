#include "Enemy.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Enemy::Enemy() {
	enemiesMT = new MatrixTransform();
	enemy = new Sphere();

	//loop to add multiple enemy MatrixTransformations, only 1 enemy instance but many enemyMT instances
	for (int i = 0; i < 10; i++){
		enemyMT = new MatrixTransform();
		
		mat4 translate;
		translate.translate(vec3(i / 5 + i % 5, 0, i / 5 + i % 5));
		
		enemyMT->setMatrix(translate);
		enemyMT->addChild(enemy);
		enemiesMT->addChild(enemyMT);
	}
}

Enemy::~Enemy() {

}

void Enemy::update() {

}

void Enemy::draw(mat4 C) {
	enemiesMT->draw(C);
}

void Enemy::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}