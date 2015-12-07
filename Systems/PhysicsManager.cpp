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
	if( Globals::EvtMgr.ActionState._moveforward ) {
		dx -= velocity * cosf(turn);
		dz -= velocity * sinf(turn);
	}
	if( Globals::EvtMgr.ActionState._movebackward ) {
		dx += velocity * cosf(turn);
		dz += velocity * sinf(turn);
	}
	//strafe left
	if( Globals::EvtMgr.ActionState._moveleft ) {
		turn -= 1.5707; // 90 rad
		dx -= velocity * cosf(turn);
		dz -= velocity * sinf(turn);
	}
	//strafe right
	if( Globals::EvtMgr.ActionState._moveright ) {
		turn -= 1.5707; // 90 rad
		dx += velocity * cosf(turn);
		dz += velocity * sinf(turn);
	}
	Globals::camera.eye = Globals::camera.eye + vec3(dx, 0.f, dz);
	Globals::camera.dir = Globals::camera.dir + vec3(dx, 0.f, dz);

	Body sim = Body(1.f, Globals::camera.eye, vec3(0.f,0.f,0.f));
	Simulation::RK4(sim, t, dt);
	vec3 newEyePstn = sim.position;
	float height = Globals::scene->terrain->terrainGetHeight(Globals::camera.eye.v[0], Globals::camera.eye.v[2]);

	if( newEyePstn.v[1] < height ) {
		newEyePstn.v[1] =  height; 
	}
	Globals::camera.eye.v[1] = newEyePstn.v[1] + 1.0;
}