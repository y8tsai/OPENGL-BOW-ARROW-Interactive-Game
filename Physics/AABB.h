#ifndef __AABB_H__
#define __AABB_H__

#include "math3d.h"

// Axis Aligned Bounding Box
// =========================
/*	Used during broad sweep of physics collision tests
 *	The broad sweep entails checking whether pairs of physics bodies
 *  have the potential to collide
 *
 */


 /*		+-------+	Half width extents can be thought of as
		|   ^	|   the radius of an object. In the figure,
	    |	* > |   * is the center 
		|       |   ^ is the radius in Y direction
		+-------+   > is the radius in X direction
 */

class AABB {
public:
	AABB();
	AABB(vec3 c, vec3 r);
	AABB(vec3 c, float rx, float ry, float rz);
	AABB(const AABB& b); //copy constructor
	
	void DrawDebug(); // Draws bounding volume
	bool hit;


	static void Intersect(AABB &a, AABB &b);

	static vec3 hitColor;
	static vec3 stdColor;
	vec3 center;
	vec3 radius; // half-width extents (rx, ry, rz)
};


#endif
