#ifndef __ARROW_H__
#define __ARROW_H__

#include "SceneGraph/Primitives/Cube.h"
#include "math3d.h"

class Arrow : public Cube {
public:
	Arrow();
	~Arrow();

    virtual void update();
	bool markDelete;

private:
	float mass;
	vec4 tracecolor;

};



#endif;