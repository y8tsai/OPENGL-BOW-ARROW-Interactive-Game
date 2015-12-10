#include "Physics/BVH/NaiveCollision.h"

unsigned int NaiveCollision::cid_keygen = 0;

NaiveCollision::NaiveCollision() {
}

NaiveCollision::~NaiveCollision() {
}

unsigned int NaiveCollision::RegisterAABB(AABB *bbox) {
	CID_Store.insert(std::pair<unsigned int, AABB*>(++cid_keygen, bbox));
	return cid_keygen;
}

AABB* NaiveCollision::GetAABBInfo(unsigned int cid) {
	if( cid != 0 && CID_Store.count(cid)) {
		return CID_Store[cid];
	}
	return nullptr;
}

unsigned int NaiveCollision::ReplaceAABB(unsigned int cid, AABB* re) {
	if( cid != 0 && CID_Store.count(cid) ) {
		
		AABB* todel = CID_Store[cid];
		if( todel != nullptr )
			delete todel;
		CID_Store.erase(cid);
		CID_Store.insert(std::pair<unsigned int, AABB*>(cid, re));

		return cid;
	}
	return 0;
}

void NaiveCollision::RemoveAABBInfo(unsigned int cid) {
	if( cid != 0 && CID_Store.count(cid) ) {
		AABB* todel = CID_Store[cid];
		if( todel != nullptr )
			delete todel;
		CID_Store.erase(cid);
	}
}


void NaiveCollision::Query(unsigned int cid, HitList &out) {
	HitList::iterator it = collisions.begin();
	while( it != collisions.end() ) {
		if( (*it).intersect && (*it).query_id == cid ) {
			out.push_back(*it);
		}
		++it;
	}
}


void NaiveCollision::Update(float t, float dt) {
	collisions.clear();
	std::unordered_map<unsigned int, AABB*>::iterator it = CID_Store.begin();
	while( it != CID_Store.end() ) {
		std::unordered_map<unsigned int, AABB*>::iterator ref = CID_Store.begin();
		while( ref != CID_Store.end() ) {

			if( it->first != ref->first ) {
				HitInfo ht = AABB::BroadIntersect(it->first, *it->second, ref->first, *ref->second);
				if( ht.intersect ) {
					collisions.push_back(ht);
				}
			}
			ref++;
		}
		it++;
	}
}

void NaiveCollision::Cleanup() {

}