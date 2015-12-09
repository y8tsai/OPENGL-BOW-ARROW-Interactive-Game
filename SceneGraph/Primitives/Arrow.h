#ifndef __ARROW_H__
#define __ARROW_H__

#include "SceneGraph/Base/MatrixTransform.h"
#include "SceneGraph/Primitives/Cube.h"
#include "Entity/EntityNode.h"

class Arrow : public MatrixTransform {
public:
	static std::string __ArrowEID;
	static Arrow* MakeArrow(mat4 m2w, vec3 init_v, quat rot = quat());
	static EntityNode* CreateEntity(std::string eid, const GLvoid *verts, GLsizeiptr vertsize);
	static const float lifetime;

    void draw( mat4 C );
	void update(float t, float dt);

	bool markDelete;
	
private:
	Arrow();
	Arrow(mat4 m2w, std::string EntityID, unsigned int cid);
	virtual ~Arrow();

	Cube *model;
};



#endif;