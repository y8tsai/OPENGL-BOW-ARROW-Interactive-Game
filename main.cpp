#include <GL/glew.h>
#include "Globals.h"
#include "Core.h"

// Press ESC to quit, this event is setup in Core::OnKeyDown

int main(int argc, char* argv[]) {
	Core core = Core();
	
	Globals::window.StartUp();
	Globals::gPhysicsMgr.StartUp();
	core.StartUp();

	core.Shutdown();
	Globals::gPhysicsMgr.Shutdown();
	Globals::window.Shutdown();
	return 0;
}