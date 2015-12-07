#include "EntityNode.h"

EntityNode::EntityNode() {
	name = "";
	drawData = DrawData();
	materialData = MaterialData();
	updateData = UpdateData();
	vertices = nullptr;
}


EntityNode::EntityNode(std::string n, DrawData& dd, MaterialData& md, UpdateData& ud) {
	name = n;
	drawData = dd;
	materialData = md;
	updateData = ud;
}

EntityNode::~EntityNode() {
	if( vertices != nullptr ){
		delete vertices;
	}
}