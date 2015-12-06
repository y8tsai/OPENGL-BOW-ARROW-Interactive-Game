#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <math.h>
#include "math3d.h"

// Class::Simulation
// Utility class for physics calculations
// F = m/a <=> a = F/m 
//

/* Notes on Acceleration:
	All objects have constant downward acceleration due to gravity
	Most if not all objects have a top velocity due to dampening effect
	from atmosphere e.g. air resistance, friction, etc.

	This means the integral of velocity (dv), where `b` is a constant
	for dampening && object is unit mass, would be the equation. 
		
		dv = (topVelocity - b * velocity) / 1.0f

	Behavior is a slow start until max velocity attained.

	If momentum is added to the equation.


	Mass is specified in kilograms



	
*/	


struct Body {
	Body( float body_mass, vec3 initial_position, vec3 initial_velocity ) {
		mass = body_mass;
		position = initial_position;
		velocity = initial_velocity;	
	}
	
	float mass;			// Mass in kilograms
	vec3 position;		// Position in world coordinates
	vec3 velocity;		// Meters per second, calculated from momentums
};


struct Derivative {
	vec3 dx;	// derivative of position, Velocity 
	vec3 dv;	// derivative of velocity, Acceleration
};


class Simulation {
public:
	static Derivative Evaluate(const Body &state, float t) {
		Derivative result;
		result.dx = state.velocity;
		result.dv = Acceleration(state, t);
		return result;
	}

	static Derivative Evaluate(Body state, float t, float dt, const Derivative &derivative) {
		state.position = state.position + derivative.dx * dt;
		state.velocity = state.velocity + derivative.dv * dt;
		
		Derivative result;
		result.dx = state.velocity;
		result.dv = Acceleration(state, t+dt);
		return result;
	}

	static void RK4(Body &state, float t, float dt) {
		Derivative a = Evaluate(state, t);
		Derivative b = Evaluate(state, t, dt*0.5f, a);
		Derivative c = Evaluate(state, t, dt*0.5f, b);
		Derivative d = Evaluate(state, t, dt, c);

		state.position = state.position + (a.dx + (b.dx + c.dx)*2.0f + d.dx) * (1.0f/6.0f) * dt;
		state.velocity = state.velocity + (a.dv + (b.dv + c.dv)*2.0f + d.dv) * (1.0f/6.0f) * dt;
	}

	static vec3 Acceleration(const Body &body, float t) {
		return vec3(0.f, -0.0002f, 0.f);
	}
};









#endif