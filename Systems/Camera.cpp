#include "Camera.h"
#include "Globals.h"


Camera::Camera() {
	reset();
	Globals::EvtMgr.Register("Camera::Orbit", [&](SDL_Event& evt) {
		this->Orbit(evt.motion.x, evt.motion.y, evt.motion.xrel, evt.motion.yrel);
	});
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
	eye = vec3(0.0f, 20.0f, -128.0f);
	dir = vec3(0.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	update();
}

static float xorbit = 0.0f;
void Camera::Orbit(int mX, int mY, int relX, int relY) {
	//double maxAngle = 1; //180 deg up/down lock
	
	////////////////// Orbit about y-axis, rotating camera left/right //////////////////
	quat yrot = quat::rotate( -relX * DEG2RAD(0.3f), vec3(0.0f, 1.0f, 0.0f) );
	quat ytarget;

	//This is direction in model space
	vec3 viewvec = Globals::camera.eye - Globals::camera.dir;
	viewvec.negate();

	ytarget.x = viewvec.v[0];
	ytarget.y = viewvec.v[1];
	ytarget.z = viewvec.v[2];
	ytarget.w = 0.0f;

	// Rotate by quaternion
	ytarget = yrot * ytarget * yrot.conjugate();

	Globals::camera.dir.v[0] = ytarget.x + Globals::camera.eye.v[0];
	Globals::camera.dir.v[1] = ytarget.y + Globals::camera.eye.v[1];
	Globals::camera.dir.v[2] = ytarget.z + Globals::camera.eye.v[2];

	////////////////// Orbit about x-axis, rotating camera up/down //////////////////

	float mouseYSensitivity = DEG2RAD(3.0f); //rotating 0.3 degrees at any time

	vec3 viewcalc = Globals::camera.eye - Globals::camera.dir;
	viewcalc.negate();
	
	xorbit += relY * DEG2RAD(mouseYSensitivity);

	vec3 axis = (Globals::camera.eye - Globals::camera.dir).cross(Globals::camera.up);
	axis.normalize();

	quat xrot = quat::rotate( relY * DEG2RAD(mouseYSensitivity), axis );
	quat xtarget;
	xtarget.x = viewcalc.v[0];
	xtarget.y = viewcalc.v[1];
	xtarget.z = viewcalc.v[2];
	xtarget.w = 0.0f;

	xtarget = xrot * xtarget * xrot.conjugate();

	Globals::camera.dir.v[0] = xtarget.x + Globals::camera.eye.v[0];
	Globals::camera.dir.v[1] = xtarget.y + Globals::camera.eye.v[1];
	Globals::camera.dir.v[2] = xtarget.z + Globals::camera.eye.v[2];
}
