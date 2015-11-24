#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "Window.h"
#include "Core.h"
#include "Timer.h"

class Globals {
public:
	static Timer hiresTime;
	static Window window;
	static Core core;
};


#endif