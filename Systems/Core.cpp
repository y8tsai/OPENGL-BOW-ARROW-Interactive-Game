#include "Core.h"
#include "Globals.h"

#include <iostream>
#include <vector>

Core::Core() : running(false) {
	glewInit();
}

Core::~Core() {
}

void Core::StartUp() {
	
	running = true;
	SetupKeybinds();
	SDL_StartTextInput();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	float t = 0.f;
	const float dt = 10.0f; // milliseconds
	float deltaTime = 0.f;
	float accumulator = 0.f;

	while( running ){
		Globals::clock.updateInterval();
		deltaTime = Timer::interval;

		// Step 1: Respond to actions and change game state
		SDL_Event eve;
		while( SDL_PollEvent(&eve) ){
			Globals::EvtMgr.OnEvent(eve);
		}

		if( deltaTime > 0.0f ){
			accumulator += deltaTime;

			while( accumulator >= dt ){
				// Step 2: Update Physics based on current game state
				Globals::gPhysicsMgr.Update(t, dt);
				accumulator -= dt;
				t += dt;
			}
		}

		// Step 3: Display game state
		Globals::window.display();
	}
};

void Core::Shutdown() {
	SDL_StopTextInput();
}

void Core::Stop() {
	running = false;
}

void Core::SetupKeybinds() {
	Globals::EvtMgr.Register("Core::StopRun", [&](SDL_Event evt){ 
		this->Stop();
	});
	Globals::EvtMgr.Register("Core::Pause", [&](SDL_Event evt){ 
		SDL_SetRelativeMouseMode(SDL_FALSE);
		system("PAUSE");
		SDL_SetRelativeMouseMode(SDL_TRUE);
	});
}


//static float xorbit = 0.0f;
//void Core::OnMouseMove(int mX, int mY, int relX, int relY, bool lt, bool rt, bool mid) {
//	//double maxAngle = 1; //180 deg up/down lock
//	
//	////////////////// Orbit about y-axis, rotating camera left/right //////////////////
//	quat yrot = quat::rotate( -relX * DEG2RAD(0.3f), vec3(0.0f, 1.0f, 0.0f) );
//	quat ytarget;
//
//	//This is direction in model space
//	vec3 viewvec = Globals::camera.eye - Globals::camera.dir;
//	viewvec.negate();
//
//	ytarget.x = viewvec.v[0];
//	ytarget.y = viewvec.v[1];
//	ytarget.z = viewvec.v[2];
//	ytarget.w = 0.0f;
//
//	// Rotate by quaternion
//	ytarget = yrot * ytarget * yrot.conjugate();
//
//	Globals::camera.dir.v[0] = ytarget.x + Globals::camera.eye.v[0];
//	Globals::camera.dir.v[1] = ytarget.y + Globals::camera.eye.v[1];
//	Globals::camera.dir.v[2] = ytarget.z + Globals::camera.eye.v[2];
//
//	////////////////// Orbit about x-axis, rotating camera up/down //////////////////
//
//	float mouseYSensitivity = DEG2RAD(3.0f); //rotating 0.3 degrees at any time
//
//	vec3 viewcalc = Globals::camera.eye - Globals::camera.dir;
//	viewcalc.negate();
//	
//	xorbit += relY * DEG2RAD(mouseYSensitivity);
//
//	vec3 axis = (Globals::camera.eye - Globals::camera.dir).cross(Globals::camera.up);
//	axis.normalize();
//
//	quat xrot = quat::rotate( relY * DEG2RAD(mouseYSensitivity), axis );
//	quat xtarget;
//	xtarget.x = viewcalc.v[0];
//	xtarget.y = viewcalc.v[1];
//	xtarget.z = viewcalc.v[2];
//	xtarget.w = 0.0f;
//
//	xtarget = xrot * xtarget * xrot.conjugate();
//
//	Globals::camera.dir.v[0] = xtarget.x + Globals::camera.eye.v[0];
//	Globals::camera.dir.v[1] = xtarget.y + Globals::camera.eye.v[1];
//	Globals::camera.dir.v[2] = xtarget.z + Globals::camera.eye.v[2];
//}
//
//void Core::OnLButtonDown(int mX, int mY) {
//	Globals::fireDown = true;
//}
//
//void Core::OnLButtonUp(int mX, int mY) {
//	Globals::fireDown = false;
//	Arrow *bullet = new Arrow();
//	Globals::fired.push_back(bullet);
//}