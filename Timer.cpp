#include "Timer.h"
#include "Globals.h"


Uint32 Timer::startTicks = 0;
Uint32 Timer::pausedTicks = 0;
SDL_Color Timer::fpsDisplayColor = {255, 255, 255};

void Timer::displayElapsed() {

//	GLuint texture;
//
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	
//	hud = TTF_RenderUTF8_Blended(arialTypeset, "Time per Frame: " + Timer::getTicks(), Timer::fpsDisplayColor);
//	Timer::startTicks = SDL_GetTicks();
//
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, hud->w, hud->h, 0, GL_RGB, GL_UNSIGNED_BYTE, hud->pixels);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glBegin(GL_QUADS);
//		glTexCoord2d(0, 0); glVertex3d(-0.5, -0.5, 0.0 );
//		glTexCoord2d(0, 1); glVertex3d(-0.5, 0.5, 0.0);
//		glTexCoord2d(1, 1); glVertex3d(0.5, 0.5, 0.0);
//		glTexCoord2d(1, 0); glVertex3d(0.5, -0.5, 0.0);
//	glEnd();
//
//	glDeleteTextures(1, &texture);
//	SDL_FreeSurface(hud);
}

Timer::Timer() : started(false), paused(false) {
	TTF_Init();
	arialTypeset = TTF_OpenFont(".\\arial.ttf", 24);
}

void Timer::start() {
	started = true;
	paused = false;
	Timer::startTicks = SDL_GetTicks();
	Timer::pausedTicks = 0;
}

void Timer::stop() {
	started = false;
	paused = false;
	Timer::startTicks = 0;
	Timer::pausedTicks = 0;
}

void Timer::pause() {
	if(started && !paused) {
		paused = true;
		Timer::pausedTicks = SDL_GetTicks() - Timer::startTicks;
		Timer::startTicks = 0;
	}
}

void Timer::unpause() {
	if(started && paused) {
		paused = false;
		Timer::startTicks = SDL_GetTicks() - Timer::pausedTicks;
		Timer::pausedTicks = 0;
	}
}

void Timer::resetTicks() {
	Timer::startTicks = 0;
	Timer::pausedTicks = 0;
}

Uint32 Timer::getTicks() {
	Uint32 time = 0;

	if( started ) {
		if( paused ) { 
			time = Timer::pausedTicks; 
		} else {
			time = SDL_GetTicks() - Timer::startTicks;
		}
	} 

	return time;
}