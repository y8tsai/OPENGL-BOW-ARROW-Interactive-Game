#include "Simulation.h"
#include "Globals.h"

namespace Fizzix {

	PBody::PBody() {
		// bbox = AABB();		implicit
		// position = vec3();
		// velocity = vec3();
		mass = 0.f;
		staticBody = false;
		elasticity = 0.f;
	}

	PBody::PBody(vec3 initial_pstn, vec3 initial_velocity, float body_mass, bool isStatic, float spring_const) { 
		position = initial_pstn;
		velocity = initial_velocity;
		mass = body_mass;
		staticBody = isStatic;
		elasticity = spring_const;
	}

	PBody::~PBody() {
		//~~~~
	}

	void PBody::SetAABB(vec3 center, vec3 radius, quat orientation) {
		bbox = AABB(center, radius);
	}

	void PBody::UpdateSimulation(float t, float dt) {
		if( !staticBody ) {
			Simulation::RK4( *this, t, dt);
		}
	}

};