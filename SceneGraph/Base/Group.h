#ifndef __GROUP_H__
#define __GROUP_H__

#include "Node.h"
#include "math3d.h"
#include <vector>

class Group : public Node {
public:
	virtual ~Group() {
		prune();
	};

	std::vector<Node*> children;
	void addChild(Node*);
	void removeChild(Node*);
	virtual void draw(mat4 C);
	virtual void prune();
};


#endif