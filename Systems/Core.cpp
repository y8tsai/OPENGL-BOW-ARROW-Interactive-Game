#include "Core.h"
#include "Globals.h"

#include <iostream>
#include <vector>

Core::Core() : running(false) {
	glewInit();
}

Core::~Core() {
}

void Core::StartUp() {
	
	running = true;
	SetupKeybinds();
	SDL_StartTextInput();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	float t = 0.f;
	const float dt = 10.0f; // milliseconds
	float deltaTime = 0.f;
	float accumulator = 0.f;

	while( running ){
		Globals::clock.updateInterval();
		deltaTime = (float)Timer::interval;

		// Step 1: Respond to actions and change game state
		SDL_Event eve;
		while( SDL_PollEvent(&eve) ){
			Globals::EvtMgr.OnEvent(eve);
		}

		if( deltaTime > 0.0f ){
			accumulator += deltaTime;

			while( accumulator >= dt ){
				// Step 2: Update Physics based on current game state
				Globals::gPhysicsMgr.Update(t, dt);
				accumulator -= dt;
				t += dt;
			}
		}

		// Step 3: Display game state
		Globals::window.display();
	}
};

void Core::Shutdown() {
	SDL_StopTextInput();
}

void Core::Stop() {
	running = false;
}

void Core::SetupKeybinds() {
	Globals::EvtMgr.Register("Core::StopRun", [&](SDL_Event evt){ 
		this->Stop();
	});
	Globals::EvtMgr.Register("Core::Pause", [&](SDL_Event evt){ 
		SDL_SetRelativeMouseMode(SDL_FALSE);
		system("PAUSE");
		SDL_SetRelativeMouseMode(SDL_TRUE);
	});
}