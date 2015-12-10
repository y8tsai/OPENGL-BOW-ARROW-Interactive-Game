#ifndef __NAIVEC_H__
#define __NAIVEC_H__

#include <iostream>
#include <unordered_map>
#include <queue>


#include "math3d.h"
#include "Physics/BVH/AABB.h"

// Simple Class for Testing Bounding Boxes
class NaiveCollision {
public:
	NaiveCollision();
	~NaiveCollision();

	unsigned int RegisterAABB(AABB *bbox); // returns CID

	AABB* GetAABBInfo(unsigned int cid);

	void RemoveAABBInfo(unsigned int cid);

	unsigned int ReplaceAABB(unsigned int cid, AABB* re);

	void Query(unsigned int cid, HitList &out);

	void Update(float t, float dt);

	static unsigned int cid_keygen;
	static unsigned int player_cid;

private:
	HitList collisions;
	std::unordered_map<unsigned int, AABB*> CID_Store;
	std::queue<unsigned int> free_CID;

};


#endif