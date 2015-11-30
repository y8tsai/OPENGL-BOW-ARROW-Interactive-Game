#include "LTree.h"
#include <stack>

LTree::LTree(unsigned int randseed, LSysParam properties) {
	prop = properties;
	memo = NULL;
	reset(randseed);
	if( prop.rules.size() ){
		memo = new RuleMap[prop.rules.size()];
	}
}

void LTree::reset(unsigned int randseed) {
	seed = randseed;
	position = vec3();
	heading = vec3(0.0f, prop.length, 0.0f);
	numDraws = 0;
	currentLv = 0; //supports 254 levels
	if( memo != NULL ){
		delete[] memo;
	}
}

DrawData* LTree::generate() {
	std::string rule = prop.rules[prop.startRule];

	rule = evalRule(rule, prop.iterations - 1);
	for (int i = 0; i < rule.length(); ++i) {
		if (rule[i] == Grammar::DRAW) ++numDraws;
	}

	return draw(rule);
}

std::string LTree::evalRule(std::string &rule, int iteration) {
	if (iteration > 0) {
		for (int i = 0; i < rule.length(); ++i) {
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

DrawData* LTree::draw(std::string tape) {
	DrawData *dd = new DrawData();

	GLint numOfVerts = numDraws * prop.segments * 2 * 3;
	GLfloat *vertices = new GLfloat[numOfVerts];
	std::stack<vec3> states;
	int vertIdx = 0;
	for (int i = 0; i < tape.length(); ++i) {
		if (tape[i] == Grammar::DRAW) {
			drawForward(vertices, vertIdx);
		} else if (tape[i] == Grammar::TURNLEFT) {
			yawLeft(prop.yawMin);
		} else if (tape[i] == Grammar::TURNRIGHT) {
			yawRight(-prop.yawMin);
		} else if (tape[i] == Grammar::SAVE) {
			states.push(position);
			states.push(heading);
		} else if (tape[i] == Grammar::RESTORE) {
			heading = states.top();
			states.pop();
			position = states.top();
			states.pop();
		}
	}

	dd->type = GL_POINTS;
	glGenBuffers(1, &dd->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, dd->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVerts, vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &dd->vao);
	glBindVertexArray(dd->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, dd->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	dd->indexStart = 0;
	dd->indexCount = numOfVerts/3;

	return dd;
}

void LTree::drawForward(GLfloat *vertices, int &vert_idx) {
	/*int idx = vert_idx * prop.segments * 2 * 3;
	position.print("pos: ");
	float turn = DEG2RAD(0);
	vertices[idx] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 1] = position.v[1];
	vertices[idx + 2] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 3] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 4] = position.v[1];
	vertices[idx + 5] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 6] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 7] = position.v[1];
	vertices[idx + 8] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 9] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 10] = position.v[1];
	vertices[idx + 11] = prop.radius * (position.v[0] + sinf(turn));
	position = position + heading;
	position.print("pos: ");
	turn = DEG2RAD(0);
	vertices[idx + 12] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 13] = position.v[1];
	vertices[idx + 14] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 15] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 16] = position.v[1];
	vertices[idx + 17] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 18] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 19] = position.v[1];
	vertices[idx + 20] = prop.radius * (position.v[0] + sinf(turn));
	turn += DEG2RAD(90);
	vertices[idx + 21] = prop.radius * (position.v[0] + cosf(turn));
	vertices[idx + 22] = position.v[1];
	vertices[idx + 23] = prop.radius * (position.v[0] + sinf(turn));

	++vert_idx;*/


	int idx = vert_idx * 2 * 3;
	vertices[idx] = position.v[0];
	vertices[idx + 1] = position.v[1];
	vertices[idx + 2] = position.v[2];
	position = position + heading;
	vertices[idx + 3] = position.v[0];
	vertices[idx + 4] = position.v[1];
	vertices[idx + 5] = position.v[2];
	++vert_idx;
}

void LTree::yawLeft(GLfloat turnRadian) {
	vec3 axis = heading.cross(vec3(-heading.v[1], heading.v[0], 0.0f)).normalize();
	quat rot = quat::rotate(turnRadian, axis);
	heading = quat::tovec3(rot * quat(heading) * rot.conjugate());
}

void LTree::yawRight(GLfloat turnRadian) {
	yawLeft(turnRadian);
}