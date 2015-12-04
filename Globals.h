#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Window.h"
#include "Core.h"
#include "Camera.h"
#include "LSystem/LTree.h"
#include "SceneGraph/Scene.h"

#include "Arrow.h"


class Globals {
public:
	static Camera camera;
	static Window window;
	static Core core;
	static LTree ltree;

	static Scene scene;

	static std::vector<Arrow*> fired;
	static bool fireDown;
};


#endif