#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "Globals.h"


// Press ESC to quit, this event is setup in Core::OnKeyDown

int main(int argc, char* argv[]) {
	
	Globals::window.initialize();
	Globals::core.startup();

	Globals::core.shutdown();
	Globals::window.shutdown();

	return 0;
}