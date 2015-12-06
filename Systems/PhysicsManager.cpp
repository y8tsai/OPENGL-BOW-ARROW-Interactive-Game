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


static Body sim = Body(1.f, Globals::camera.eye, vec3(0.f,0.f,0.f));

//-------------------- PRIVATE FUNCTIONS --------------------
void PhysicsManager::UpdatePlayer(float t, float dt) {
	
	float velocity = 0.1f;
	vec3 heading = Globals::camera.eye - Globals::camera.dir;
	float turn = atan2f(heading.v[2], heading.v[0]);
	float xc = velocity * cosf(turn);
	float zc = velocity * sinf(turn);
	if( Globals::EvtMgr.ActionState._moveforward ) {
		Globals::camera.eye.v[0] -= xc;
		Globals::camera.eye.v[2] -= zc;
		Globals::camera.dir.v[0] -= xc;
		Globals::camera.dir.v[2] -= zc;
	}
	if( Globals::EvtMgr.ActionState._movebackward ) {
		Globals::camera.eye.v[0] += xc;
		Globals::camera.eye.v[2] += zc;
		Globals::camera.dir.v[0] += xc;
		Globals::camera.dir.v[2] += zc;
	}

	//strafe left
	if( Globals::EvtMgr.ActionState._moveleft ) {
		turn -= 1.5707; // 90 rad
		Globals::camera.eye.v[0] -= velocity * cosf(turn);
		Globals::camera.eye.v[2] -= velocity * sinf(turn);
		Globals::camera.dir.v[0] -= velocity * cosf(turn);
		Globals::camera.dir.v[2] -= velocity * sinf(turn);
	}

	//strafe right
	if( Globals::EvtMgr.ActionState._moveright ) {
		turn -= 1.5707; // 90 rad
		Globals::camera.eye.v[0] += velocity * cosf(turn);
		Globals::camera.eye.v[2] += velocity * sinf(turn);
		Globals::camera.dir.v[0] += velocity * cosf(turn);
		Globals::camera.dir.v[2] += velocity * sinf(turn);
	}

	Simulation::RK4(sim, t, dt);
	vec3 newEyePstn = sim.position;
	float height = Globals::scene->terrain->terrainGetHeight(newEyePstn.v[0], newEyePstn.v[2]);
	if( newEyePstn.v[1] < height ) {
		newEyePstn.v[1] = height;
	}
	float dy = newEyePstn.v[1] - Globals::camera.eye.v[1];
	Globals::camera.dir.v[1] += dy;
	Globals::camera.eye.v[1] = newEyePstn.v[1];

	std::cout << "Height: " << height << std::endl;
	std::cout << "\t\t\t Eye Height: " << Globals::camera.eye.v[1] << std::endl;
}