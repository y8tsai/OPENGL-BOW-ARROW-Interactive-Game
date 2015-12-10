#ifndef __AABB_H__
#define __AABB_H__

#include <vector>
#include <iostream>

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

 // !explicit prevents compiler from turning this class into another type
// Can be doubly used for ray casting
class HitInfo {
public:
	explicit HitInfo(float tdist = 0.f, const vec3& hpstn = vec3(), const vec3& norm = vec3()){};
	float t; // hit distance
	vec3 p; // hit position
	vec3 n; // normal
	bool intersect;
	unsigned int query_id;
	unsigned int ref_id;
};

// these are collision id keys of interactable game objects
typedef std::pair<unsigned int, HitInfo> HitPair;
typedef std::vector<HitInfo> HitList;

class AABB {
public:
	AABB();
	AABB(vec3 p, vec3 c, vec3 r, mat3 rot);
	AABB(const AABB& b); //copy constructor
	
	void DrawDebug(mat4 C = mat4().makeIdentity(), bool collided = false); // Draws bounding volume
	bool hit;
	std::string tag;

	static HitInfo BroadIntersect(unsigned int k, AABB &a, unsigned int l, AABB &b);

	static void UpdateAABB(AABB rotated, AABB &res);

	static vec3 hitColor;
	static vec3 stdColor;

	mat3 rotation;
	vec3 position;
	vec3 center;
	vec3 radius; // half-width extents (rx, ry, rz)
};


#endif