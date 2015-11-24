#include "Core.h"
#include "Globals.h"

Core::Core() : running(false) {

}

Core::~Core() {
}


void Core::startup() {
	SDL_Event evee;
		
	SDL_StartTextInput();
	running = true;
		
	while( running ) {
		while(SDL_PollEvent(&evee)) {
			OnEvent(&evee);
			Globals::window.OnEvent(&evee);
		}
		Globals::window.display();
	}
};

void Core::shutdown() {
	SDL_StopTextInput();
}

void Core::OnEvent(SDL_Event* evt) {
	Event::OnEvent(evt);
}

void Core::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
	if( sym == SDLK_ESCAPE ) {
		running = false;
	}
}
