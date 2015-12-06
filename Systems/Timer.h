#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL.h>


class Timer {
public:
	static Uint32 startTicks;
	static Uint32 pausedTicks;
	static Uint32 interval;
	//void displayElapsed();

	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	void resetTicks();
	Uint32 getTicks();

	void updateInterval();


private:
	bool started;
	bool paused;
};



#endif