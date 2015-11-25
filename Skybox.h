#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Drawable.h"
#include "Texture.h"


class Skybox : public Drawable
{
public:
	float size;

	Skybox(float);
	virtual ~Skybox(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

};

#endif