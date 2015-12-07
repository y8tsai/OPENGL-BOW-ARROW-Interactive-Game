#include "LTree.h"
#include <stack>
#include <vector>

LTree::LTree(unsigned int randseed, LSysParam properties) {
	prop = properties;
	reset(randseed);
}
void LTree::setProperties(LSysParam properties) {
	prop = properties;
	reset(0);
}

void LTree::reset(unsigned int randseed) {
	seed = randseed;
	position = vec3(0.0f, 0.0f, 0.0f);
	yaw = 0.0f;
}

EntityNode* LTree::generate() {
	std::string rule = prop.rules[prop.startRule];
	//parametricCylinder(1.0, 1.f, 4, 1);
	rule = evalRule(rule, prop.iterations - 1);
	EntityNode *modelData = new EntityNode();
	modelData->vertices = new std::vector<Verts*>();
	
	modelData->drawData.shaders = Program::LoadShaders("Models/Shaders/tree.vs", "Models/Shaders/tree.fs");

	modelData->drawData.texture = new Texture();
	GLuint woodtex;
	glGenTextures(1, &woodtex);
	glBindTexture(GL_TEXTURE_2D, woodtex);
	int w, h;
	unsigned char *img = SOIL_load_image("Resources/Textures/treebark.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	modelData->drawData.texture->setID(woodtex);

	std::vector<CylinderMesh*>* raw = draw(rule);
	for( int i = 0; i < raw->size(); ++i ) {
		Verts *mesh = (*raw)[i]->ExportGLTriangleStrip();
		modelData->vertices->push_back(mesh);
	}

	return modelData;
}

std::string LTree::evalRule(std::string &rule, int iteration) {
	if (iteration > 0) {
		for (std::size_t i = 0; i < rule.length(); ++i) {
			if (prop.rules.count(rule[i])) {
				char key = rule[i];
				rule.replace(i, 1, prop.rules[key]);
				int len = prop.rules[key].length() - 1;
				i += len;
			}
		}
		rule = evalRule(rule, iteration - 1);
	} 
	return rule;
}

std::vector<CylinderMesh*>* LTree::draw(std::string tape) {
	std::stack<vec3> transSave;
	std::stack<float> rotSave;
	std::vector<CylinderMesh*> *TreeMesh = new std::vector<CylinderMesh*>();
	int level = 0;

	for (std::size_t i = 0; i < tape.length(); ++i) {
		if (tape[i] == Grammar::DRAW) {
			TreeMesh->push_back(drawForward());
		} else if (tape[i] == Grammar::TURNLEFT) {
			yawLeft(prop.yawMax);
		} else if (tape[i] == Grammar::TURNRIGHT) {
			yawRight(-prop.yawMax);
		} else if (tape[i] == Grammar::SAVE) {
			transSave.push(position);
			rotSave.push(yaw);
			++level;
		} else if (tape[i] == Grammar::RESTORE) {
			position = transSave.top();
			yaw = rotSave.top();
			transSave.pop();
			rotSave.pop();
			--level;
		}
	}
	return TreeMesh;
}

CylinderMesh* LTree::drawForward() {
	CylinderMesh *b = new CylinderMesh();
	b->Translate(position);
	b->Rotate(yaw, vec3(0.0f, 0.0f, 1.0f));
	b->CreateCylinder(prop.length, prop.radius, 1, prop.segments);
	
	quat qyaw = quat::rotate(DEG2RAD(yaw), vec3(0.f, 0.f, 1.f));
	qyaw = qyaw * vec3(0.f, prop.length, 0.f) * qyaw.conjugate();
	position = position + quat::tovec3(qyaw);

	return b;
}

void LTree::yawLeft(GLfloat turnRadian) {
	yaw += turnRadian;
}

void LTree::yawRight(GLfloat turnRadian) {
	yawLeft(turnRadian);
}