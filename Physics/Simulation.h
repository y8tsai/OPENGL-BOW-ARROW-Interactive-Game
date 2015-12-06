#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <math.h>
#include "math3d.h"

struct PhysState {
	vec3 position;
	vec3 velocity;
};

struct Derivative {
	vec3 dx;
	vec3 dv;
};







#endif