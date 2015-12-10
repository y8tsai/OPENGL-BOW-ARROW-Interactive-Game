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
	Globals::gPhysicsMgr.StartUp();
	Globals::gLevelMgr.StartUp();
	core.StartUp();

	core.Shutdown();
	Globals::gLevelMgr.Shutdown();
	Globals::gPhysicsMgr.Shutdown();
	Globals::clock.stop();
	Globals::window.Shutdown();
	return 0;
}