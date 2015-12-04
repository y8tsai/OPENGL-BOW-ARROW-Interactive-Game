#include "Arrow.h"
#include "Globals.h"
#include <math.h>
#include <GL/glut.h>

#define GRAVITY -0.0001f


Arrow::Arrow() {
	toWorld.makeIdentity();
	acceleration = vec3(0.f, GRAVITY, 0.f);
	velocity = Globals::camera.dir - Globals::camera.eye;
	velocity.normalize();

	tracecolor = vec4(1.0f, 0.0f, 0.f, 1.0f);
	position = Globals::camera.eye;
	initialp = position;
}


Arrow::~Arrow() {
	
}


void Arrow::draw(DrawData& dd) {
	
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	for(int i=0; i < debug_trace.size();++i) {
		glColor3fv(tracecolor.ptr());
		vec3 trace = debug_trace[i];
		glVertex3fv( trace.ptr() );
	}
}

void Arrow::update(UpdateData& ud) {
	// mark delete if out of playing field
	if(abs(position.v[0]) > 100.f || abs(position.v[1]) > 100.f || abs(position.v[2]) > 100.f) {
		markDelete = true;
	} else {
		debug_trace.push_back(position);
		velocity = velocity + acceleration;
		position = position + velocity;
		debug_trace.push_back(position);
		toWorld.setTranslate(position);
	}
}

