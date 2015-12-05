#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <GL/GLU.h>
#include <stdio.h>
#include "Event.h"

#include "Skybox.h"
#include "Models\Tree.h"
#include "LSystem\ProcMesh.h"
#include "Particles.h"

class Window : public Event {
public:
	static GLsizei WIDTH;
	static GLsizei HEIGHT;

	Window();
	~Window();

	void initialize();
	void reshape(GLsizei w, GLsizei h);
	void display();
	void OnEvent(SDL_Event* evt);

	void shutdown();

private:
	void glConfiguration();
	void OnResize(int w, int h);
	void DisplayHUD();


	SDL_Window* winHandle;
	SDL_GLContext glContext;
	Skybox* skybox;
	Tree* sampleTree;
	std::vector<CylinderMesh*>* treeData;
	Particles* particles;
};

#endif