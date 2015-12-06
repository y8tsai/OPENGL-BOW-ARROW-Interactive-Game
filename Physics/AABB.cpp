#include "Physics\AABB.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>

vec3 AABB::hitColor = vec3(1.f, 0.f, 0.f);
vec3 AABB::stdColor = vec3(1.f, 1.f, 1.f);

AABB::AABB() {
	center = vec3(0.f, 0.f, 0.f);
	radius = vec3(0.f, 0.f, 0.f);
	hit = false;
}

AABB::AABB(vec3 c, vec3 r) {
	center = c;
	radius = r;
	hit = false;
}

AABB::AABB(vec3 c, float rx, float ry, float rz) {
	center = c;
	radius = vec3(rx, ry, rz);
	hit = false;
}

AABB::AABB(const AABB& b) {
	if( this != &b ) {
		center = b.center;
		radius = b.radius;
	}
}

// Check if AABBs intersect and set hit as true for both in such case
// Otherwise, set hit false
void AABB::Intersect(AABB &a, AABB &b) {
	for(int i = 0; i < 3; ++i) {
		if( abs(a.center.v[i] - b.center.v[i]) > (a.radius.v[i] + b.radius.v[i]) ) {
			a.hit = false;
			b.hit = false;
			return;
		}
	}
	a.hit = true;
	b.hit = true;
}


void AABB::DrawDebug() {
	if( hit ){
		glColor3fv(AABB::hitColor.ptr());
	}else{
		glColor3fv(AABB::stdColor.ptr());
	}

	glPointSize(3.0f);
	glBegin(GL_POINTS);
		glVertex3f(center.v[0], center.v[1], center.v[2]);
	glEnd();

	glPushMatrix();
	glMultMatrixf(mat4().makeIdentity().setTranslate(center).makeTranspose().ptr());


	

	glBegin(GL_LINES);
	glVertex3f(-radius.v[0], radius.v[1], -radius.v[2]);
	glVertex3f(-radius.v[0], -radius.v[1], -radius.v[2]);
		glVertex3f(-radius.v[0], radius.v[1], -radius.v[2]);
		glVertex3f(-radius.v[0], radius.v[1], radius.v[2]);

		glVertex3f(-radius.v[0], -radius.v[1], -radius.v[2]);
		glVertex3f(-radius.v[0], -radius.v[1], radius.v[2]);

	glVertex3f(radius.v[0], -radius.v[1], -radius.v[2]);
	glVertex3f(radius.v[0], radius.v[1], -radius.v[2]);
		
		glVertex3f(radius.v[0], -radius.v[1], -radius.v[2]);
		glVertex3f(radius.v[0], -radius.v[1], radius.v[2]);

		glVertex3f(radius.v[0], radius.v[1], -radius.v[2]);
		glVertex3f(radius.v[0], radius.v[1], radius.v[2]);

	glVertex3f(-radius.v[0], radius.v[1], radius.v[2]);
	glVertex3f(-radius.v[0], -radius.v[1], radius.v[2]);
		//sideways back-bottom LR
		glVertex3f(-radius.v[0], -radius.v[1], radius.v[2]);
		glVertex3f(radius.v[0], -radius.v[1], radius.v[2]);
		// front-top LR
		glVertex3f(-radius.v[0], radius.v[1], -radius.v[2]);
		glVertex3f(radius.v[0], radius.v[1], -radius.v[2]);
		// front-bottom LR
		glVertex3f(-radius.v[0], -radius.v[1], -radius.v[2]);
		glVertex3f(radius.v[0], -radius.v[1], -radius.v[2]);
		// back-top LR
		glVertex3f(-radius.v[0], radius.v[1], radius.v[2]);
		glVertex3f(radius.v[0], radius.v[1], radius.v[2]);

	glVertex3f(radius.v[0], -radius.v[1], radius.v[2]);
	glVertex3f(radius.v[0], radius.v[1], radius.v[2]);
	glEnd();
	glPopMatrix();
}