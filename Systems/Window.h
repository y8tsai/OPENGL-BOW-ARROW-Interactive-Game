#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <GL/GLU.h>
#include <stdio.h>

#include "Models/Skybox.h"
#include "LSystem/ProcMesh.h"
#include "Particles.h"
#include "Entity/Properties/Light.h"

class Window {
public:
	static GLsizei WIDTH;
	static GLsizei HEIGHT;

	Window();
	~Window();

	void StartUp();
	void Shutdown();
	void reshape(GLsizei w, GLsizei h);
	void display();

private:
	void glConfiguration();
	void DisplayHUD();

	SDL_Window* winHandle;
	SDL_GLContext glContext;
	Skybox* skybox;

	//Tree* sampleTree;
	//std::vector<CylinderMesh*>* treeData;
	//Particles* particles;
	//Light light; //addded to test light
};

#endif