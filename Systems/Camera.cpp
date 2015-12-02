#include "Camera.h"

Camera::Camera() {
	reset();
}

Camera::~Camera() { }

void Camera::lookAt(const vec3& e, const vec3& d, const vec3& u) {
	eye = e;
	dir = d;
	up = u;
	update();
}

void Camera::update() {
	vec3 z, x, y;
	z = eye - dir;
	x = up.cross(z.normalize());
	y = z.cross(x.normalize());
	c = mat4({
		{x.v[0], x.v[1], x.v[2], 0.0f },
		{y.v[0], y.v[1], y.v[2], 0.0f },
		{z.v[0], z.v[1], z.v[2], 0.0f },
		{eye.v[0], eye.v[1], eye.v[2], 1.0f }
	});

	ci = c.rigidInverse(); 
	// Both c and ci are transposed for ease of use
}

void Camera::reset() {
	eye = vec3(50.0f, 40.0f, 20.0f);
	dir = vec3(0.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	update();
}
