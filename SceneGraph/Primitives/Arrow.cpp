#include "Arrow.h"
#include "Globals.h"
#include <math.h>
#include <GL/glut.h>


Arrow::Arrow() {
	tracecolor = vec4(1.0f, 0.0f, 0.f, 1.0f);
}


Arrow::~Arrow() {
	
}

 void Arrow::update() {
 
 }

//void Arrow::draw(DrawData& dd) {
//	
//	glLineWidth(1.0f);
//	glBegin(GL_LINES);
//	for(std::size_t i=0; i < debug_trace.size();++i) {
//		glColor3fv(tracecolor.ptr());
//		vec3 trace = debug_trace[i];
//		glVertex3fv( trace.ptr() );
//	}
//}
//
//void Arrow::update(UpdateData& ud) {
//	// mark delete if out of playing field
//	if(abs(position.v[0]) > 100.f || abs(position.v[1]) > 100.f || abs(position.v[2]) > 100.f) {
//		markDelete = true;
//	} else {
//		debug_trace.push_back(position);
//		velocity = velocity + acceleration;
//		position = position + velocity;
//		debug_trace.push_back(position);
//		toWorld.setTranslate(position);
//	}
//}
//
