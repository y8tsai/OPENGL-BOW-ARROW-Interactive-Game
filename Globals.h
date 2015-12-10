#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Systems/Window.h"
#include "Systems/InputManager.h"
#include "Systems/PhysicsManager.h"
#include "Systems/LevelManager.h"

#include "Systems/Timer.h"
#include "Systems/Camera.h"
#include "SceneGraph/Scene.h"
#include "Entity/EntityBST.h"
#include "Physics/BVH/NaiveCollision.h"


#define CLAMP(n, lower, upper) std::fmax(lower, std::fmin(n, upper))

class Globals {
public:
	static Window window;
	static InputManager EvtMgr;
	static PhysicsManager gPhysicsMgr;
	static LevelManager gLevelMgr;
	
	static Timer clock;
	static Camera camera;
	static Scene* SceneGraph;
	static EntityBST* EntityStore;
	static NaiveCollision *ColStore;
};


#endif