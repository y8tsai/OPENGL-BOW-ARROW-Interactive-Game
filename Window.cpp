#include "Globals.h"
#include "Window.h"
#include "math3d.h"

GLint Window::WIDTH = 512;
GLint Window::HEIGHT = 512;

Window::Window() : winHandle(NULL), glContext(NULL) {}

Window::~Window() {}

void Window::initialize() {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
	}
	// Setting up opengl 2.1 context
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 1);

	// Setting up color depth, instead of [0, 1] with 8 bits it's [0, 255], for SDL Color
	// OpenGL's system is still [0, 1]
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	// SDL_WINDOW_RESIZABLE :: allows window to be resizable
	// SDL_WINDOW_OPENGL :: let opengl render window
	// SDL_WINDOW_SHOWN :: Makes the window visible
	Uint32 windowFlags = (SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	winHandle = SDL_CreateWindow( "OpenGLTestBench", 500, 500, Window::WIDTH, Window::HEIGHT,  windowFlags);

	if( !winHandle || !(glContext = SDL_GL_CreateContext(winHandle)) ) {
		printf( "SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
	}
	/* if( SDL_GL_SetSwapInterval(1) < 0 ) {
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	} */
	glConfiguration(); // Set OpenGL specific options
	reshape(Window::WIDTH, Window::HEIGHT);
	Globals::hiresTime.start();
}

void Window::glConfiguration() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// Mask filter for textures to allow for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::reshape(GLsizei w, GLsizei h) {
	Window::WIDTH = w;
	Window::HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLdouble(w)/h, 0.1, 500.0);
}


void drawCoordinateAxes() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();
}

void Window::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	Globals::camera.update();
	glLoadMatrixf(Globals::camera.ci.ptr());

	/*glLoadIdentity();
	gluLookAt(-2.0, 2.0, 5.0, 
			  0.0, 0.0, 0.0, 
			  0.0, 1.0, 0.0);*/


	/* Commit 1949f48 */
	Globals::skybox.draw(Globals::drawData);
	/* End 1949f48 */

	/* Scene generation*/
	mat4 identity;
	identity.makeIdentity();
	Globals::scene.draw(identity); 
	/*End scene generation */


	drawCoordinateAxes();

	// This will swap the buffers
	SDL_GL_SwapWindow( winHandle );

	//Globals::hiresTime.displayElapsed(); don't need this yet
}

void Window::shutdown() {
	SDL_DestroyWindow(winHandle);
	SDL_Quit();
}

void Window::OnEvent(SDL_Event* evt) {
	Event::OnEvent(evt);
}

void Window::OnResize(int w, int h) {
	reshape(w, h);
}