#include "../include/Object.h"
#include <iostream>

Object::Object()
{
	
}

Object::Object(glm::vec3 _position, glm::vec3 _color)
{
	position = _position;
	color = _color;
}

Object::~Object()
{
	
}

glm::vec3 Object::getColor()
{
	return color;
}
