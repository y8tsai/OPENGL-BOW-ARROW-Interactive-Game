#include "Skybox.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Globals.h"

Skybox::Skybox(float s): Drawable()
{
	size = s;
}

Skybox::~Skybox(void)
{

}

void Skybox::draw(DrawData&)
{
	float halfSize = size / 2.0;

	//Never see the outside of the box
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	/*
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	*/

	glPushMatrix();


	mat4 m2w = mat4({
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	});
	m2w.makeTranspose();
	glMultMatrixf(m2w.ptr());

	//Color the skybox white to use original texture color
	glColor3f(1.0, 1.0, 1.0);

	Globals::front.bind();
	
	//disable Lighting for the texture to show
	glDisable(GL_LIGHTING);

	glBegin(GL_QUADS);
	// Draw front face:
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2d(0 ,0); glVertex3f(halfSize, halfSize, halfSize); //top left
	glTexCoord2d(0, 1); glVertex3f(halfSize, -halfSize, halfSize); //bottom left
	glTexCoord2d(1, 1); glVertex3f(-halfSize, -halfSize, halfSize); //bottom right
	glTexCoord2d(1, 0); glVertex3f(-halfSize, halfSize, halfSize);  //top right
	glEnd();
	Globals::front.unbind();


	Globals::left.bind();

	glBegin(GL_QUADS);
	// Draw left side:
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2d(0, 0);  glVertex3f(-halfSize, halfSize, halfSize); //top left
	glTexCoord2d(0, 1);  glVertex3f(-halfSize, -halfSize, halfSize); //bottom left
	glTexCoord2d(1, 1);  glVertex3f(-halfSize, -halfSize, -halfSize); //bottom right
	glTexCoord2d(1, 0);  glVertex3f(-halfSize, halfSize, -halfSize); //top right
	glEnd();
	Globals::left.unbind();


	Globals::right.bind();

	glBegin(GL_QUADS);
	// Draw right side:
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2d(0, 0);  glVertex3f(halfSize, halfSize, -halfSize);  //top left
	glTexCoord2d(0, 1);  glVertex3f(halfSize, -halfSize, -halfSize); //bottom left
	glTexCoord2d(1, 1);  glVertex3f(halfSize, -halfSize, halfSize); //bottom right
	glTexCoord2d(1, 0);  glVertex3f(halfSize, halfSize, halfSize); //top right
	glEnd();
	Globals::right.unbind();

	Globals::back.bind();

	glBegin(GL_QUADS);
	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2d(0, 0);  glVertex3f(-halfSize, halfSize, -halfSize);  //top left
	glTexCoord2d(0, 1);  glVertex3f(-halfSize, -halfSize, -halfSize); //bottom left
	glTexCoord2d(1, 1);  glVertex3f(halfSize, -halfSize, -halfSize);  //bottom right
	glTexCoord2d(1, 0);  glVertex3f(halfSize, halfSize, -halfSize);   //top right
	glEnd();
	Globals::back.unbind();


	Globals::up.bind();

	glBegin(GL_QUADS);
	// Draw top side:
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0, 0);  glVertex3f(-halfSize, halfSize, -halfSize);//top left
	glTexCoord2d(0, 1);  glVertex3f(halfSize, halfSize, -halfSize); //bottom left
	glTexCoord2d(1, 1);  glVertex3f(halfSize, halfSize, halfSize);  //bottom right
	glTexCoord2d(1, 0);  glVertex3f(-halfSize, halfSize, halfSize); //top right
	glEnd();
	Globals::up.unbind();


	Globals::down.bind();

	glBegin(GL_QUADS);
	// Draw bottom side:
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0, 0);  glVertex3f(-halfSize, -halfSize, halfSize);  //top left
	glTexCoord2d(0, 1);  glVertex3f(halfSize, -halfSize, halfSize); //bottom left
	glTexCoord2d(1, 1);  glVertex3f(halfSize, -halfSize, -halfSize);  //bottom right
	glTexCoord2d(1, 0);  glVertex3f(-halfSize, -halfSize, -halfSize);   //top right
	glEnd();
	Globals::down.unbind();

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();
	//glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING); //re-enable the lighting
}

void Skybox::update(UpdateData&)
{
	//add update code...
}