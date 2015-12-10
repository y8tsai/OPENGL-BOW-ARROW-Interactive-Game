/*
 *  Particle.cpp
 *  
 *  Created by Karl Grogan on 26/04/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particle.h"
#include <stdlib.h>
#include <GL/glut.h>

Particle::Particle() {
	srand(time(NULL));
}

Particle::~Particle() {
	//delete dynamically allocated objects
}

// Constructor for a particle.
void Particle::CreateParticle()
{
	lifetime= (float)rand();
	decay=1;
	r = 0.7;
	g = 0.7;
	b = 1.0;
	xpos= 256.0;
	ypos= 128.0;
	zpos= 5.0;
	xspeed = 2-(int)rand() % 5 ;
	yspeed = 2-(int)rand() % 5  ;
	zspeed = 2- (int)rand() % 5  ;
	active = true;
}

// Constructor for a particle.
void Particle::CreateParticle(vec3 sourcePos)
{
	lifetime = (float)rand();
	decay = 1;
	r = 1.0;
	g = 0.0;
	b = 0.0;
	//get location of the source 
	xpos = sourcePos.v[0];
	ypos = sourcePos.v[1];
	zpos = sourcePos.v[2];

	//randomize speed
	xspeed = float( 50 - rand() % 100 ) / 1000;  
	yspeed = float( 50 - rand() % 100 ) / 1000;
	zspeed = float( 50 - rand() % 100 ) / 1000;

	std::cout << xspeed << " " << yspeed << " " << zspeed << std::endl;

	//alive
	active = true;
}

// Constructor for a particle with initial velocity and distance from center (for explosion).
void Particle::CreateParticle(vec3 sourcePos, float iniVel, float distFromCenter)
{
	
	lifetime = 500; //live 500 frames
	decay = 1;
	r = 0.7;
	g = 0.7;
	b = 1.0;
	//get location of the source 
	xpos = sourcePos.v[0];
	ypos = sourcePos.v[1];
	zpos = sourcePos.v[2];

	xposC = sourcePos.v[0];
	yposC = sourcePos.v[1];
	zposC = sourcePos.v[2];

	int signX, signY, signZ;
	if (rand() % 2 == 0) //determines the direction of the particle
			signX = 1;
	else
			signX = -1;

	if (rand() % 2 == 0) //determines the direction of the particle
		signY = 1;
	else
		signY = -1;

	if (rand() % 2 == 0) //determines the direction of the particle
		signZ = 1;
	else
		signZ = -1;

	//randomize speed
	xspeed = iniVel * distFromCenter * signX;  //still need to weigh this based on the distance from center
	yspeed = iniVel * distFromCenter * signY;
	zspeed = iniVel * distFromCenter * signZ;

	if (yspeed == 0)
		yspeed = 0.20; //give initial y speed so it drops

	//alive
	active = true;
}


/* 
 Evolves the particle parameters over time.
 This method changes the vertical and horizontal poition of the particle, its, speed and decay time.
*/
void Particle::EvolveParticle()
{
	lifetime-=decay;
	if ( abs(xpos) > (xposC + 10) && abs(zpos) > (zposC + 10) )
		active = false;
	xpos += xspeed;
	ypos -= yspeed;
	zpos += zspeed;
	yspeed+= abs(yspeed) / 100 ;  //so it always falls
}

/*
 This method draws the particle on screen.
 Sets the clorour mode.
 Sets the drawing primitive.
 Sets the coordinates of each point on the triangle strip
*/
void Particle::DrawObjects()
{

	glPushMatrix();
	glEnable(GL_COLOR);
	glDisable(GL_CULL_FACE);
	if((lifetime>0.0) && (active == true) )
	{
		glColor3f(r,g,b);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0,1.0); glVertex3f(xpos+0.5, ypos+0.5,zpos);     // top    right
		glTexCoord2f(0.0,1.0); glVertex3f(xpos-0.5, ypos+0.5,zpos);     // top    left
		glTexCoord2f(0.0,1.0); glVertex3f(xpos+0.5, ypos-0.5,zpos);     // bottom right
		glTexCoord2f(0.0,1.0); glVertex3f(xpos-0.5, ypos-0.5,zpos);     // bottom left
		glEnd();
	} 
	glEnable(GL_CULL_FACE);
	glDisable(GL_COLOR);
	glPopMatrix();
}

// Getter and setter methods


float Particle::GetXPos()
{
	return xpos;
}

void Particle::SetXPos(float xPos)
{
	xpos = xPos;
}


void Particle::SetYPos(float yPos)
{
	xpos = yPos;
}

float Particle::GetYPos()
{
	return ypos;
}

void Particle::SetG(float myG)
{
	g = myG;
}

float Particle::GetG()
{
	return g;
}


void Particle::draw(DrawData&) {
	DrawObjects(); //draw the particle
}

void Particle::update(UpdateData&) {
	EvolveParticle(); //update the particle
}

