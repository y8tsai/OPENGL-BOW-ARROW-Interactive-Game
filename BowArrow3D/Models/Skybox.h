#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Drawable.h"


// I've modified the skybox to do environmental mapping (shaders)
// Instead of glBegin/glEnd, using VBOs and VAOS
// The sides of the skybox are all stored in here

// Behavior of the skybox will be to follow the player around
// so the player will always be at the center of the skybox.

// This creates an illusion that the skybox is infinitely far away
// called parallax effect.
class Skybox : public Drawable 
{
public:
	Skybox(float size);
	virtual ~Skybox(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);


private:
	float size;
	DrawData model;

};


#endif