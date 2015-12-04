#include "LTree.h"
#include <stack>
#include <vector>

LTree::LTree(unsigned int randseed, LSysParam properties) {
	prop = properties;
	reset(randseed);
}

void LTree::reset(unsigned int randseed) {
	seed = randseed;
	position = vec3(0.0f, 0.0f, 0.0f);
	yaw = 0.0f;
}

std::vector<CylinderMesh*>* LTree::generate() {
	std::string rule = prop.rules[prop.startRule];

	rule = evalRule(rule, prop.iterations - 1);

	return draw(rule);
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

	int vertIdx = 0;
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
		} else if (tape[i] == Grammar::RESTORE) {
			position = transSave.top();
			yaw = rotSave.top();
			transSave.pop();
			rotSave.pop();
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
	//quat qyaw = quat::rotate(yaw, vec3(0.f, 0.f, 1.f));
	//qyaw = qyaw * vec3(0.f, prop.length, 0.f) * qyaw.conjugate();
	//position = position + quat::tovec3(qyaw);
}

void LTree::yawRight(GLfloat turnRadian) {
	yawLeft(turnRadian);
}


//DrawData* LTree::parametricCylinder(GLfloat height, GLfloat radius, GLint slices, GLint stacks) {
//	stacks++;
//	int count = stacks * slices * (3 + 2); // vertex components + uv texcoord + normal components + color
//	GLfloat *vertices = new float[count];
//
//	// +2 indices for degenerate triangles inbetween each stack
//	// for every stack +2 indices to close mesh
//	int indexCount = (count/5) + slices * (stacks - 2) + (4 * stacks - 6);
//	
//	GLuint *indices = new GLuint[indexCount];
//	int curridx = -1;
//
//	for (int v = 0; v < stacks; ++v) {
//		float y = (float) v / stacks * height;
//		if( v >= 2 ) curridx++;
//		for (int u = 0; u < slices; ++u) {
//			curridx += 2;
//			double rotation = PI * 2 * (float)u / slices;
//			float x = radius * cos(rotation);
//			float z = radius * sin(rotation);
//			int idx = (v * slices + u);
//			indices[curridx] = idx;
//			if( stacks > 1 && v > 0 && v != stacks - 1) {
//				indices[ v*slices*2  + u*2 + v*4 + 1] = idx;
//			}
//
//			idx *= 5;
//			vec4 vertex =  m2w * vec4(x, y, z, 1.0f);
//
//			// vertex xyz
//			vertices[idx] = vertex.v[0];
//			vertices[idx + 1] = vertex.v[1]; 
//			vertices[idx + 2] = vertex.v[2];
//			// texcoords
//			vertices[idx + 3] = (float)u / (slices-1); //u latitude
//			vertices[idx + 4] = (float)v / (stacks -1); //v longitude
//		}
//		// if v is odd, then copy top 2 of that stack, to close walls
//		// if v is even, then go back
//		if( v > 0) { 
//			curridx += 2;
//			indices[curridx] = indices[ curridx - slices * 2];
//			indices[++curridx] = indices[ curridx - slices * 2];
//		} else if( v < 2) {
//			curridx -= (slices * 2 + 1);	
//		}
//	}
//
//	// Fill in degenerate triangles
//	for( curridx = 2*slices+4; curridx < indexCount; curridx += 2*slices+4 ) {
//		indices[curridx - 1] = indices[curridx];
//		indices[curridx - 2] = indices[curridx-3];
//	}
//
//	//std::cout<< indexCount;
//	GLuint ibo;
//	//Make vertex array buffer object
//	DrawData *cyl = new DrawData();
//	cyl->type = GL_TRIANGLE_STRIP;
//	cyl->indexStart = 0;
//	cyl->indexCount = indexCount;
//	
//	cyl->shaders = Program::LoadShaders("Models/Shaders/tree.vs", "Models/Shaders/tree.fs");
//
//	//Make vertex attribute object
//	glGenVertexArrays(1, &cyl->vao);
//	glBindVertexArray(cyl->vao);
//	// Bind ibo to VAO
//	glGenBuffers(1, &ibo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexCount, indices, GL_STATIC_DRAW);
//	
//	// Bind VBO to VAO saying
//	glGenBuffers(1, &cyl->vbo);	//Make vertex index buffer object
//	glBindBuffer(GL_ARRAY_BUFFER, cyl->vbo); // this is the vertex array, use  it
//	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0); //store vertex array in position 0
//		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // this is how it's formatted
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
//	// 1st arg: index of generic vertex attribute
//	// 2nd arg: # of components per vertex
//	// 3rd: data type
//	// 4th: auto-normalize?
//	// 5th: offset inbetween each vertex <# of components + offset>
//	// 6th: pointer to first component of starting vertex
//
//	// uv Texture Coordinate Attribute
//
//	GLint attrib = glGetAttribLocation(cyl->shaders->getHandle(), "turd");
//	glEnableVertexAttribArray(attrib);
//	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glBindVertexArray(0);
//
//	delete[] vertices;
//	delete[] indices;
//	
//	cyl->texture = new Texture();
//	GLuint woodtex;
//	glGenTextures(1, &woodtex);
//	glBindTexture(GL_TEXTURE_2D, woodtex);
//	int w, h;
//	unsigned char *img = SOIL_load_image("Resources\\Textures\\treeTrunk.bmp", &w, &h, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	cyl->texture->setID(woodtex);
//
//	return cyl;
//}