#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <math.h>
#include "math3d.h"

#include "BVH/AABB.h"

#define GRAVITY -3.f

// Class::Simulation
// Utility class for physics calculations

/* Notes on Acceleration:	F = m/a <=> a = F/m 
	All objects have constant downward acceleration due to gravity
	Most if not all objects have a top velocity due to dampening effect
	from atmosphere e.g. air resistance, friction, etc.

	This means the integral of velocity (dv), where `b` is a constant
	for dampening && object is unit mass, would be the equation. 
		
		dv = (topVelocity - b * velocity) / 1.0f

	Observed trajectory behavior is a slow start until max velocity attained.
	Mass is specified in kilograms

*/	

namespace Fizzix {


	/* PBody ( Physics Body ) Used in simulation of physics motion
	 ----------------------------------------------------------------------------------  */
	class PBody {
	public:
		PBody(
			vec3  initial_pstn, 
			vec3  initial_velocity,
			float body_mass, 
			bool  isStatic = false,
			float spring_const = 0.f
		);
		PBody();
		~PBody();
		
		void SetAABB(vec3 center, vec3 radius, quat orientation = quat());
		void UpdateSimulation(float t, float dt);

		// axis-aligned bounding box used in BVH to do Z-curve spread
		// and median cut.
		
		AABB bbox;	     // Center position held by AABB is in model space
		vec3 position;  // World coordinates
		vec3 velocity;  // Meters per second ?
		float mass;		 // Mass in kilograms ?
		bool staticBody;  // This body does not move i.e. obstacle
		float elasticity; // Elastic collision constant
	};

	struct Derivative {
		vec3 dx;	// derivative of position, Velocity 
		vec3 dv;	// derivative of velocity, Acceleration
	};


	class Simulation {
	public:
		static Derivative Evaluate(const PBody &state, float t) {
			Derivative result;
			result.dx = state.velocity;
			result.dv = Acceleration(state, t);
			return result;
		}

		static Derivative Evaluate(PBody state, float t, float dt, const Derivative &derivative) {
			state.position = state.position + derivative.dx * dt;
			state.velocity = state.velocity + derivative.dv * dt;
		
			Derivative result;
			result.dx = state.velocity;
			result.dv = Acceleration(state, t+dt);
			return result;
		}

		static void RK4(PBody &state, float t, float dt) {
			Derivative a = Evaluate(state, t);
			Derivative b = Evaluate(state, t, dt*0.5f, a);
			Derivative c = Evaluate(state, t, dt*0.5f, b);
			Derivative d = Evaluate(state, t, dt, c);
			state.position = state.position + (a.dx + (b.dx + c.dx)*2.0f + d.dx) * (1.0f/6.0f) * dt;
			state.velocity = state.velocity + (a.dv + (b.dv + c.dv)*2.0f + d.dv) * (1.0f/6.0f) * dt;
		}

		static vec3 Acceleration(const PBody &body, float t) {
			return vec3(-1.f, GRAVITY, -1.f); // right now, everything is modeled as unit mass
		}
	};

};

#endif