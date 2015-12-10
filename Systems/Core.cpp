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
	const double dt = 0.01; // milliseconds
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
				
				
				// !! NOTE - So how do you use tdt ? 
				// dt are discrete chunks of time that you can always assume will
				// never change and always reliablt. Say now you have an animation that you've determined
				// will take 1.0 second to complete. The amount of dt you will need is
				// 100 since up there I've limited the dt to 0.01 every frame

				// You may ask how reliable is this dt?
				// How this accumulator works is that the delta time wont be the same across
				// most display refresh rates. Like some monitors are limited to 60Hz or 90hz
				// and what not. To complicate things, the amount of time it takes for a frame to render will be
				// different across graphics cards. So you'll end up with variable delta steps in between frames. 
				// So constant 100 fps, you're solid and the simulation runs exactly as intended.
				// Say you get half that, well the simulation needs work 2x as hard to catch up.
				// Thats why the simulation runs in a loop, to catch up.
				
				// Also since dt won't divide exactly into delta, sometimes you'll get
				// leftover time that the simulation needed. Over runtime, these increments add
				// up into what's called a spiral of death since movement that shouldve been calculated
				// or animations that shouldve taken place never did. So the accumulator is there to
				// to recycle these increments

				Globals::SceneGraph->update(t, dt);
				// Correct all dynamic objects positions
				// and animations on Geodes

				Globals::gLevelMgr.EventUpdate(t, dt);

				accumulator -= dt;
				          t += dt;
			}
		}
		
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