#ifndef __CORE_H__
#define __CORE_H__

#include "Event.h"

class Core : public Event {
public:
	Core();
	~Core();

	void startup();
	void shutdown();
	void OnEvent(SDL_Event* evt);
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
	bool running;
};

#endif