#include "InputManager.h"

InputManager::InputManager() {
	ActionState._moveforward = false;
	ActionState._movebackward = false;
	ActionState._moveleft = false;
	ActionState._moveright = false;
	ActionState._chargeAttack = false;
	ActionState._run = false;
}

void InputManager::Register(std::string cmd, std::function<void(SDL_Event&)> func) {
	keybinds.insert(std::pair<std::string, std::function<void(SDL_Event&)>>(cmd, func));
}

// If nothing bound to command, no runtime errors
// Duplicate bindings not allowed, recent will replace former
void InputManager::Fire(std::string cmd, SDL_Event &updateData) {
	if( keybinds.count(cmd) ){
		keybinds[cmd](updateData);
	}
}

// To be called with SDL Event Polling Loop
// Strings specified to Fire(...) are available mappings
// It's up to the system that's binding to the string to define what it does
void InputManager::OnEvent(SDL_Event& evt) {
	SDL_Keycode sym;
	switch(evt.type){
		case SDL_QUIT: 
			Fire("Core::StopRun", evt);	
			break;
		case SDL_KEYDOWN: 		
			sym = evt.key.keysym.sym;
			if( sym == SDLK_ESCAPE ){
				Fire("Core::StopRun", evt);
			}else if( sym == SDLK_p ){
				Fire("Core::Pause", evt);
			}

			//--------------- CHARACTER MOVEMENT ----------------
			if( sym == SDLK_w ) ActionState._moveforward = true;
			if( sym == SDLK_s ) ActionState._movebackward = true;
			if( sym == SDLK_a ) ActionState._moveleft = true;
			if( sym == SDLK_d ) ActionState._moveright = true;
			if( sym == SDLK_LSHIFT) ActionState._run = true;
			break;
		case SDL_KEYUP:
			sym = evt.key.keysym.sym;
			if( sym == SDLK_w ) ActionState._moveforward = false;
			if( sym == SDLK_s ) ActionState._movebackward = false;
			if( sym == SDLK_a ) ActionState._moveleft = false;
			if( sym == SDLK_d ) ActionState._moveright = false;
			if( sym == SDLK_LSHIFT) ActionState._run = false;

			// Turn on drawing of bounding boxes
			if( sym == SDLK_F5 ) {
				Fire("PhysicsManager::DebugAll", evt);
			} else if( sym == SDLK_F1 ) {
				Fire("PhysicsManager::DebugPlayer", evt);
			} else if( sym == SDLK_F2 ) {
				Fire("PhysicsManager::DebugArrows", evt);
			} else if( sym == SDLK_F3 ) {
				Fire("PhysicsManager::DebugEnemies", evt);
			} else if( sym == SDLK_F4 ) {
				Fire("PhysicsManager::DebugTrees", evt);
			}

			break;
		case SDL_MOUSEMOTION:
			Fire("Camera::Orbit", evt);
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch(evt.button.button) {
				case SDL_BUTTON_LEFT:
					ActionState._chargeAttack = true;
					Fire("ChargeAttack", evt);
					break;
				case SDL_BUTTON_RIGHT:	
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch(evt.button.button) {
				case SDL_BUTTON_LEFT: 
					ActionState._chargeAttack = false;
					Fire("FireAttack", evt);
				break;
				case SDL_BUTTON_RIGHT:
				break;
			}
		break;
		case SDL_WINDOWEVENT:
			if( evt.window.event == SDL_WINDOWEVENT_RESIZED ){
				Fire("Window::Resize", evt);
			}
			break;
	} // end switch
}