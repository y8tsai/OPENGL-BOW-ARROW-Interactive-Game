#include "Core.h"
#include "Globals.h"

Core::Core() : running(false) {
	glewInit();
}

Core::~Core() {
}


void Core::startup() {
	SDL_Event evee;
		
	SDL_StartTextInput();
	running = true;
	
	// Trap mouse to window
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while( running ) {
		
		while(SDL_PollEvent(&evee)) {
			OnEvent(&evee);
			Globals::window.OnEvent(&evee);
		}
		Globals::window.display();
	}
};

void Core::shutdown() {
	SDL_StopTextInput();
}

void Core::OnEvent(SDL_Event* evt) {
	Event::OnEvent(evt);
}

void Core::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
	if( sym == SDLK_ESCAPE ) {
		running = false;
	} 
	
	float velocity = 0.1f; //move 0.3 units per *frame
	// *Physics simulation is currently locked to frame refreshes
	// so it will move as fast as your graphics card can update
	vec3 heading = Globals::camera.eye - Globals::camera.dir;
	float turn = atan2f(heading.v[2], heading.v[0]);
	float xc = velocity * cosf(turn);
	float zc = velocity * sinf(turn);
	if( sym == SDLK_w ) {
		Globals::camera.eye.v[0] -= xc;
		Globals::camera.eye.v[2] -= zc;
		Globals::camera.dir.v[0] -= xc;
		Globals::camera.dir.v[2] -= zc;
	}
	if( sym == SDLK_s ) {
		Globals::camera.eye.v[0] += xc;
		Globals::camera.eye.v[2] += zc;
		Globals::camera.dir.v[0] += xc;
		Globals::camera.dir.v[2] += zc;
	}

	//strafe left
	if( sym == SDLK_a ) {
		turn -= 1.5707; // 90 rad
		Globals::camera.eye.v[0] -= velocity * cosf(turn);
		Globals::camera.eye.v[2] -= velocity * sinf(turn);
		Globals::camera.dir.v[0] -= velocity * cosf(turn);
		Globals::camera.dir.v[2] -= velocity * sinf(turn);
	}

	//strafe right
	if( sym == SDLK_d ) {
		turn -= 1.5707; // 90 rad
		Globals::camera.eye.v[0] += velocity * cosf(turn);
		Globals::camera.eye.v[2] += velocity * sinf(turn);
		Globals::camera.dir.v[0] += velocity * cosf(turn);
		Globals::camera.dir.v[2] += velocity * sinf(turn);
	}
}

static float xorbit = 0.0f;
void Core::OnMouseMove(int mX, int mY, int relX, int relY, bool lt, bool rt, bool mid) {
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

void Core::OnLButtonDown(int mX, int mY) {
	Globals::fireDown = true;
}

void Core::OnLButtonUp(int mX, int mY) {
	Globals::fireDown = false;
}

void Core::OnExit() {
	running = false;
}
