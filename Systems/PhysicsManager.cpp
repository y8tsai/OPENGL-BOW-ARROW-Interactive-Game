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

	Body sim = Body(1.f, Globals::camera.eye, vec3(0.f,0.f,0.f));
	Simulation::RK4(sim, t, dt);
	vec3 newEyePstn = sim.position;

	float height = 0.f;
	if( Globals::SceneGraph != nullptr ) {
		height = (float)Globals::SceneGraph->terrain->terrainGetHeight(Globals::camera.eye.v[0], Globals::camera.eye.v[2]);
	
	}
	if( newEyePstn.v[1] < height ) {
		// smoothing out movement, look ahead of where player is going
		// TODO: need terrainGetHeight with floats as arguments
		float zheight = height;
		vec3 next = vec3();
		if( Globals::EvtMgr.ActionState._moveforward || Globals::EvtMgr.ActionState._movebackward ) {
			next = Globals::camera.eye + vec3(dx, 0.f, dz);
			zheight = (float)Globals::SceneGraph->terrain->terrainGetHeight(next[0], next[2]);
		}
		if( Globals::EvtMgr.ActionState._moveright || Globals::EvtMgr.ActionState._moveleft ) {
			next = Globals::camera.eye + vec3(tx, 0.f, tz);
			zheight = (float)Globals::SceneGraph->terrain->terrainGetHeight(next[0], next[2]);
		}

		newEyePstn.v[1] = height - 0.2f*(zheight - height); 
		Globals::camera.eye.v[1] = newEyePstn.v[1] + 3.0f;
	}
	//Globals::camera.eye.print("physMGr::eye");
}