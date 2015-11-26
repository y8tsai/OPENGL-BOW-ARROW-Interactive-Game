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
	void OnMouseMove(int mX, int mY, int relX, int relY, bool lt, bool rt, bool mid);
	void OnExit();

private:
	bool running;
};

#endif