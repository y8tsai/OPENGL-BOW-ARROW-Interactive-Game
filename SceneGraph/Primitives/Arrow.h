#ifndef __ARROW_H__
#define __ARROW_H__

#include "Drawable.h"
#include "math3d.h"

class Arrow : public Drawable {
public:
	Arrow();
	~Arrow();

	virtual void draw(DrawData&);
    virtual void update(UpdateData&);
	
	bool markDelete;

private:
	vec3 velocity;
	vec3 acceleration;
	vec3 position;
	vec3 initialp;
	
	
	vec4 tracecolor;
	std::vector<vec3> debug_trace;
};



#endif;