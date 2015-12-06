#include "EntityNode.h"

EntityNode::EntityNode() {
	name = " ";
	drawData = DrawData();
	materialData = MaterialData();
	updateData = UpdateData();
}


EntityNode::EntityNode(std::string n, DrawData& dd, MaterialData& md, UpdateData& ud) {
	name = n;
	drawData = dd;
	materialData = md;
	updateData = ud;
}

EntityNode::~EntityNode() {
}