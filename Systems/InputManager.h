#ifndef __INPUTMGR_H__
#define __INPUTMGR_H__

#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <SDL.h>


/*	Keys that are not remapped are prefixed with <Class Name>::<Function>
 * 
 */

class InputManager {
public:
	InputManager();
	void Register(std::string cmd, std::function<void(SDL_Event&)>);
	void OnEvent(SDL_Event &sdl_evt);

	struct {
		bool _moveforward;
		bool _movebackward;
		bool _moveleft;
		bool _moveright;
		bool _chargeAttack;
		bool _run;
	} ActionState;

private:
	void Fire(std::string cmd, SDL_Event &updateData);

	std::unordered_map<std::string, std::function<void(SDL_Event&)>> keybinds;
};


#endif