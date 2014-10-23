#include "../include/Object.h"
#include <iostream>

Object::Object()
{
	
}

Object::Object(glm::vec3 _position, glm::vec3 _color, bool _diffuse, bool _transparent)
{
	position = _position;
	color = _color;
	diffuse = _diffuse;
	transparent = _transparent;
}

Object::~Object()
{
	//Hello
}


// glm::vec3 Object::getColor()
// {
// 	return color;
// }

bool Object::isDiffuse()
{
	return diffuse;
}

bool Object::isTransparent()
{
	return transparent;
}