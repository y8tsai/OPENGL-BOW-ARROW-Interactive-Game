#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>
#include <stdio.h>

class Window {
public:
	static GLsizei WIDTH;
	static GLsizei HEIGHT;

	Window();
	~Window();

	void initialize();
	void reshape(GLsizei w, GLsizei h);
	void display();
	void shutdown();

private:
	void glConfiguration();

	SDL_Window* winHandle;
	SDL_GLContext glContext;


};

#endif