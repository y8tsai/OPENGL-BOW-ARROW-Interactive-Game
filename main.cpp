#include <GL/glew.h>
#include "Globals.h"
#include "Core.h"

int main(int argc, char* argv[]) {
	Core core = Core();
	Globals::window.StartUp();
	Globals::clock.start();
	Globals::gPhysicsMgr.StartUp();
	core.StartUp();

	core.Shutdown();
	Globals::gPhysicsMgr.Shutdown();
	Globals::clock.stop();
	Globals::window.Shutdown();
	return 0;
}