#include "Physics/BVH/AABB.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>

vec3 AABB::hitColor = vec3(1.f, 0.f, 0.f);
vec3 AABB::stdColor = vec3(1.f, 1.f, 1.f);

AABB::AABB() {
	center = vec3(0.f, 0.f, 0.f);
	radius = vec3(0.f, 0.f, 0.f);
	hit = false;
	tag = "";
}

AABB::AABB(vec3 p, vec3 c, vec3 r, mat3 rot) {
	rotation = rot;
	position = p;
	center = c;
	radius = r;
	hit = false;
	tag = "";
}

AABB::AABB(const AABB& b) {
	if( this != &b ) {
		rotation = b.rotation;
		position = b.position;
		center = b.center;
		radius = b.radius;
		hit = false;
		tag = b.tag;
	}
}

// Check if AABBs intersect and set hit as true for both in such case
// Otherwise, set hit false
HitInfo AABB::BroadIntersect(unsigned int k, AABB &a, unsigned int l, AABB &b) {
	HitInfo result;
	if( a.tag == "Player" && b.tag == "Arrow" || a.tag == "Arrow" && b.tag == "Player" || 
		a.tag == "Creeper" && b.tag == "Creeper"
	) {
		result.intersect = false;
		return result;
	}
	result.intersect = true;
	
	for(int i = 0; i < 3; ++i) {
		if( abs(a.position[i] - b.position[i]) > (a.radius[i] + b.radius[i]) ) {
			result.intersect = false;
			return result;
		}
	}
	result.query_id = k;
	result.ref_id = l;
	result.p = b.position; // last known position of ref
	return result;
}

void AABB::UpdateAABB(AABB rotated, AABB &res) {
	for (int i = 0; i < 3; i++) {
		res.center[i] = rotated.position[i];
		res.radius[i] = 0.0f;
		for (int j = 0; j < 3; j++) {
			res.center[i] += rotated.rotation.m[i][j] * rotated.center[j];
			res.radius[i] += abs(rotated.rotation.m[i][j]) * rotated.radius[j];
		}
	}
}

void AABB::DrawDebug(mat4 C, bool collided) {

	if( radius.length() != 0 ){
		glPushMatrix();
		glMultMatrixf(mat4().translate(C.getTranslate()).makeTranspose().ptr());

		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glBegin(GL_LINES);
		if( collided ) 
			glColor3fv(AABB::hitColor.ptr());
		else 
			glColor3fv(AABB::stdColor.ptr());
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
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
	}
}