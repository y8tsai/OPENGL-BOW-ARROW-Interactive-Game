#include "Simulation.h"
#include "Globals.h"

namespace Fizzix {

	PBody::PBody() {
		// position = vec3();
		// velocity = vec3();
		CID = 0;
		staticBody = false;
	}

	PBody::PBody(vec3 initial_pstn, vec3 initial_velocity, unsigned int cid, bool isStatic) { 
		position = initial_pstn;
		velocity = initial_velocity;
		CID = cid;
		staticBody = isStatic;
	}

	PBody::~PBody() {
		//~~~~
	}

	void PBody::UpdateSimulation(float t, float dt) {
		if( !staticBody ) {
			Simulation::RK4( *this, t, dt);
			AABB *cobj = Globals::ColStore->GetAABBInfo(CID);
			if( cobj != nullptr ) {
				cobj->position = position;
			}
		}
	}

};