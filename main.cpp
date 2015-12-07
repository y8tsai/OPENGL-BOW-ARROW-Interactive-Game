#include <GL/glew.h>
#include "Globals.h"
#include "Core.h"

/* Entry point to game
 *
 * Ordering here is important:
 * Physics Manager needs simulation data populated within Level Manager
 * Level Manager needs Window's opengl context to create  
 */

int main(int argc, char* argv[]) {
	Core core = Core();
	Globals::window.StartUp();
	Globals::clock.start();
	Globals::gLevelMgr.StartUp();
	Globals::gPhysicsMgr.StartUp();
	core.StartUp();

	core.Shutdown();
	Globals::gPhysicsMgr.Shutdown();
	Globals::gLevelMgr.Shutdown();
	Globals::clock.stop();
	Globals::window.Shutdown();
	return 0;
}