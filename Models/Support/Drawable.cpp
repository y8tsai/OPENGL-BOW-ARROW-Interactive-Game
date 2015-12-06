#include "Drawable.h"
#include "Window.h"

Drawable::Drawable()
{
    this->toWorld.makeIdentity();
	this->center = vec3(0, 0, 0);
	this->maxValues = new float[0];
	this->minValues = new float[0];
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() with DrawData is not implemented" << std::endl;
}

void Drawable::draw(MaterialData&) 
{
	std::cout << "Warning: draw() with MaterialData is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}

vec3 Drawable::getCenter()
{
	return center;
}

float* Drawable::getMaxValues() {
	return maxValues;
}
float* Drawable::getMinValues() {
	return minValues;
}