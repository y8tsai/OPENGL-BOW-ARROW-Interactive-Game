#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Window.h"
#include "Core.h"
#include "Timer.h"
#include "Camera.h"

#include "Skybox.h"

class Globals {
public:
	static Timer hiresTime;
	static Camera camera;
	static Window window;
	static Core core;

	/* Commit 1949f48 */
	//Custom objects
	static DrawData drawData;
	static UpdateData updateData;
	static Skybox skybox;
	static Texture front;
	static Texture back;
	static Texture up;
	static Texture down;
	static Texture left;
	static Texture right;

	static char* Front;
	static char* Back;
	static char* Up;
	static char* Down;
	static char* Left;
	static char* Right;
	/* End 1949f48 */
};


#endif