#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "Globals.h"



bool gRenderQuad = true;
bool running = true;

void handleEvents();

TTF_Font* Font;
GLuint Texture = 0;
SDL_Color Color = {255, 255, 255};


int main(int argc, char* argv[]) {
	
	Globals::window.initialize();

	SDL_StartTextInput();
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	while( running ) {
		handleEvents();
		Globals::window.display();
	}

	SDL_StopTextInput();

	Globals::window.shutdown();
	return 0;
}


void reshapeWindow(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLdouble(w)/h, 1.0, 500.0);
}


void handleEvents() {
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 ) {
		if( e.type == SDL_QUIT ) {
			running = false;
		} else if( e.type == SDL_TEXTINPUT ) {
			int x = 0, y = 0;
			SDL_GetMouseState(&x, &y);
			if( e.text.text[0] == 'q')
				running = false;
		}
	}
}