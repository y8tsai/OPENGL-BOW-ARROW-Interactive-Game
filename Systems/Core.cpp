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
	
	// dt set to 100 fps max so physics
	// sim doesn't explode
	double t = 0.0;
	const double dt = 0.0100; // milliseconds
	double deltaTime = 0.0;
	double accumulator = 0.0;

	while( running ){
		Globals::clock.updateInterval();
		deltaTime = (float)Timer::interval;	//# of ms as integer not floating point
		double delta = deltaTime / 1000.0;

		// Step 1: Respond to actions and change game state
		SDL_Event eve;
		while( SDL_PollEvent(&eve) ){
			Globals::EvtMgr.OnEvent(eve);
		}

		if( delta > dt ){
			// Variable time stepping so # of physics updates happen
			// proportionally to (max frame rate - last reported display rate)
			accumulator += delta;
			while( accumulator >= dt ){
				// Step 2: Update Physics based on current game state
				Globals::gPhysicsMgr.Update(t, dt);

				// Do collision checking
				// # # # #
				
				// Correct all dynamic objects positions
				// and animations on Geodes
				Globals::SceneGraph->update(t, dt);

				accumulator -= dt;
				          t += dt;
			}
		}

		std::cout << "RUNING TIME: " << t << std::endl;
		
		// Step ???: Display game state
		Globals::window.display();
	
		//Go again!
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