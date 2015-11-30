#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_ttf.h>

class Timer {
public:
	static Uint32 startTicks;
	static Uint32 pausedTicks;
	static SDL_Color fpsDisplayColor;
	void displayElapsed();

	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	void resetTicks();
	Uint32 getTicks();

private:
	bool started;
	bool paused;
	TTF_Font *arialTypeset;
	SDL_Surface *hud;
};



#endif