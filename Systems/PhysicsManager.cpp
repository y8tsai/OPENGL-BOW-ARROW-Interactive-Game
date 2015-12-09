#include "PhysicsManager.h"
#include "Globals.h"
#include "Physics/Simulation.h"
#include "SceneGraph/Primitives/Arrow.h"
#include <string> // temp for printing

unsigned int PhysicsManager::pid_gen = 0;
unsigned int PhysicsManager::player_pid = 1;

//-------------------- CONSTRUCT/DESTRUCT---------------------
PhysicsManager::PhysicsManager() {
	pobjects = std::unordered_map<unsigned int, PBody *>();
	pobjects.clear();
	DebugDraw.__player = false;
	DebugDraw.__arrows = false;
	DebugDraw.__enemies = false;
	DebugDraw.__trees = false;
}

PhysicsManager::~PhysicsManager() {
	
}


//--------------------- PUBLIC FUNCTIONS ---------------------
void PhysicsManager::StartUp() {
	//Different granularity for turning on object bounding boxes
	Globals::EvtMgr.Register("PhysicsManager::DebugPlayer", [&](SDL_Event &){
		DebugDraw.__player = !DebugDraw.__player;
		std::cout << "PLAYER DEBUG MODE: " << (DebugDraw.__player ? "ON" : "OFF") << std::endl;
	});

	Globals::EvtMgr.Register("PhysicsManager::DebugArrows", [&](SDL_Event &){
		DebugDraw.__arrows = !DebugDraw.__arrows;
		std::cout << "ARROWS DEBUG MODE: " << (DebugDraw.__arrows ? "ON" : "OFF") << std::endl;
	});

	Globals::EvtMgr.Register("PhysicsManager::DebugEnemies", [&](SDL_Event &){
		DebugDraw.__enemies = !DebugDraw.__enemies;
		std::cout << "ENEMIES DEBUG MODE: " << (DebugDraw.__enemies ? "ON" : "OFF") << std::endl;
	});

	Globals::EvtMgr.Register("PhysicsManager::DebugTrees", [&](SDL_Event &){
		DebugDraw.__trees = !DebugDraw.__trees;
		std::cout << "TREES DEBUG MODE: " << (DebugDraw.__trees ? "ON" : "OFF") << std::endl;
	});
	
	Globals::EvtMgr.Register("PhysicsManager::DebugAll", [&](SDL_Event &){
		DebugDraw.__player = true;
		DebugDraw.__enemies = true;
		DebugDraw.__arrows = true;
		DebugDraw.__trees = true;

		std::cout << "ALL DEBUG MODE: ON" << std::endl;
	});
}

void PhysicsManager::Shutdown() {
	
}

// returns a GUUID, this is a physics objects unique identifier
// Don't lose it.
unsigned int PhysicsManager::RegisterPBody(PBody *pbody) {
	pobjects.insert(std::pair<unsigned int, PBody*>(++pid_gen, pbody));
	return pid_gen;
}

void PhysicsManager::DeregisterPBody(unsigned int key) {
	// should batch erase, this is fine for now
	if( key != 0 && pobjects.count(key)) {
		pobjects.erase(key);
	}
}

PBody* PhysicsManager::GetPBody(unsigned int key) {
	if( key != 0 && pobjects.count(key)) {
		return pobjects[key];
	}
	return nullptr;
}

void PhysicsManager::Update(float t, float dt) {
	UpdatePlayer(t, dt);
	// how should we update items in storage? we're updating pbodies
	// Guess we start with a for loop and make it better. Fill in those splits
	auto end = pobjects.end();
	for(auto it = pobjects.begin(); it != end; ++it) {
		if( !it->second->staticBody ) {
			it->second->UpdateSimulation(t, dt);
		}
	}
}

//-------------------- PRIVATE FUNCTIONS --------------------

// !kludge for charge
static float charge = 0.0;
static const float MAXCHARGE = 1.f / 0.01f; //this should be 1 second
static const float THRESHOLD = 0.6;
static const float maxv_magnitude = 25.f;

void PhysicsManager::UpdatePlayer(float t, float dt) {
	vec3 heading = Globals::camera.eye - Globals::camera.dir;
	float velocity = 0.1f;

	if( Globals::EvtMgr.ActionState._chargeAttack ) {	
		if( charge < MAXCHARGE ){
			++charge;
		}	
	}

	if( !Globals::EvtMgr.ActionState._chargeAttack && charge > 0.0 ){
		float percentage = CLAMP(charge / MAXCHARGE, 0.f, MAXCHARGE);
		if( percentage > THRESHOLD) {
			vec3 direcon = -heading;
			direcon.normalize();
			percentage *= maxv_magnitude;
			direcon = direcon * percentage;
			Arrow *fired = Arrow::MakeArrow(mat4().translate(Globals::camera.dir), direcon);
			Globals::SceneGraph->addChild(fired);
		}
		charge = 0.0;
	}


	// shift to run
	if(Globals::EvtMgr.ActionState._run) {
		velocity = 0.18f;
	}

	
	float turn = atan2f(heading[2], heading[0]);
	float dx = 0.f;
	float dz = 0.f;
	float tx = 0.f;
	float tz = 0.f;
	//move forward
	if( Globals::EvtMgr.ActionState._moveforward ) {
		dx -= velocity * cosf(turn);
		dz -= velocity * sinf(turn);
	}
	//move back
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
	//Invisible walls
	bool atBoundary = false;
	if( Globals::SceneGraph != nullptr ) {
		float boundaryX = (float)Globals::SceneGraph->terrain->terrainGridWidth/2.f;
		float boundaryZ = (float)Globals::SceneGraph->terrain->terrainGridLength/2.f;

		if( Globals::camera.eye[0] + tx > boundaryX ) {
			Globals::camera.eye[0] = boundaryX;
			atBoundary = true;
		} else if ( Globals::camera.eye[0] + tx < -boundaryX ){
			Globals::camera.eye[0] = boundaryX;
			atBoundary = true;
		}
		if( Globals::camera.eye[2] + tz > boundaryZ ) {
			Globals::camera.eye[2] = boundaryZ;
			atBoundary = true;
		} else if ( Globals::camera.eye[2] + tz < -boundaryZ ){
			Globals::camera.eye[2] = boundaryZ;
			atBoundary = true;
		}
	}
	if( !atBoundary ) {
		Globals::camera.eye = Globals::camera.eye + vec3(tx, 0.f, tz);
		Globals::camera.dir = Globals::camera.dir + vec3(tx, 0.f, tz);
	}

	float newHeight = 0.f;
	static float prevHeight = 0.f;
	static float currHeight = 0.f;
	if( Globals::SceneGraph != nullptr ) {
		newHeight = Globals::SceneGraph->terrain->GetInterpolatedHeight(Globals::camera.eye[0], Globals::camera.eye[2]);
		if(prevHeight != 0.f && prevHeight != currHeight) {
			float slope = (currHeight - prevHeight);
			float slope2 = (newHeight - currHeight);
			float correction = slope2 - 0.042f * (slope2 - slope);
			newHeight -= correction;
		}
		prevHeight = currHeight;
		currHeight = newHeight;
	}
	
	Globals::camera.eye[1] = newHeight + Globals::camera.height;
	pobjects[player_pid]->position = Globals::camera.eye;
}