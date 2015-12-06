#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Timer.h"
#include "InputManager.h"
#include "Camera.h"
#include "Window.h"
#include "PhysicsManager.h"

// To move to it's own space
#include "LSystem/LTree.h"
#include "SceneGraph/Scene.h"
#include "Arrow.h"


class Globals {
public:
	static Timer clock;
	static InputManager EvtMgr;
	static Camera camera;
	static Window window;
	static PhysicsManager gPhysicsMgr;

	static LTree ltree;
	static Scene* scene;
	static std::vector<Arrow*> fired;
	static bool fireDown;
};


#endif