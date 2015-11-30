#include "Forest.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Forest::Forest() {
	forestMT = new MatrixTransform();
	tree = new Cube();


	/*The loop creates many instances of treeMT, adds single tree as child, then forestMT adds treeMT as child*/
	for (int i = 0; i < 10; i++){
		treeMT = new MatrixTransform();
		mat4 tempMat;
		tempMat.translate( vec3(i / 5 + i % 5, 0, i / 5 + i % 5) ); //displacement for trees in X, Z only
		treeMT->setMatrix(tempMat); //set the translation as the matrix of this MatrixTransform

		treeMT->addChild(tree);
		forestMT->addChild(treeMT);
	}

}

Forest::~Forest() {
	//handle deletion
	delete tree; //delete the tree first

	for (int i = 0; i < forestMT->children.size(); i++)
	{
		delete forestMT->children.at(i);
	}

	delete forestMT; //delete root last
}

void Forest::update(){
	//Fill in update logic
}

void Forest::draw(mat4 C) {
	forestMT->draw(C);
}

void Forest::drawBoundingSphere(vec3 C) {
	//logic to draw bounding sphere
}