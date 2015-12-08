#include "PhysicsManager.h"
#include "Globals.h"
#include "Physics/Simulation.h"

//-------------------- CONSTRUCT/DESTRUCT---------------------
PhysicsManager::PhysicsManager() {

}

PhysicsManager::~PhysicsManager() {

}



//--------------------- PUBLIC FUNCTIONS ---------------------
void PhysicsManager::StartUp() {

}

void PhysicsManager::Shutdown() {

}

void PhysicsManager::Update(float t, float dt) {
	UpdatePlayer(t, dt);

	
}

//-------------------- PRIVATE FUNCTIONS --------------------
void PhysicsManager::UpdatePlayer(float t, float dt) {
	
	float velocity = 0.1f;
	vec3 heading = Globals::camera.eye - Globals::camera.dir;
	float turn = atan2f(heading[2], heading[0]);
	float dx = 0.f;
	float dz = 0.f;
	float tx = 0.f;
	float tz = 0.f;
	if( Globals::EvtMgr.ActionState._moveforward ) {
		dx -= velocity * cosf(turn);
		dz -= velocity * sinf(turn);
	}
	if( Globals::EvtMgr.ActionState._movebackward ) {
		dx += velocity * cosf(turn);
		dz += velocity * sinf(turn);
	}
	Globals::camera.eye = Globals::camera.eye + vec3(dx, 0.f, dz);
	Globals::camera.dir = Globals::camera.dir + vec3(dx, 0.f, dz);

	//strafe left
	if( Globals::EvtMgr.ActionState._moveleft ) {
		turn -= 1.5707f; // 90 rad
		tx -= velocity * cosf(turn);
		tz -= velocity * sinf(turn);
	}
	//strafe right
	if( Globals::EvtMgr.ActionState._moveright ) {
		turn -= 1.5707f; // 90 rad
		tx += velocity * cosf(turn);
		tz += velocity * sinf(turn);
	}
	Globals::camera.eye = Globals::camera.eye + vec3(tx, 0.f, tz);
	Globals::camera.dir = Globals::camera.dir + vec3(tx, 0.f, tz);

	float newHeight = 0.f;
	static float prevHeight = 0.f;
	static float currHeight = 0.f;
	if( Globals::SceneGraph != nullptr ) {
		newHeight = Globals::SceneGraph->terrain->GetInterpolatedHeight(Globals::camera.eye[0], Globals::camera.eye[2]);
		if(prevHeight != 0.f && prevHeight != currHeight) {
			float slope = (currHeight - prevHeight);
			float slope2 = (newHeight - currHeight);
			float correction = slope2 - 0.042 * (slope2 - slope);
			newHeight -= correction;
		}
		prevHeight = currHeight;
		currHeight = newHeight;
	}
	
	Globals::camera.eye.v[1] = newHeight + 3.f;
}