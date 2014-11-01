#include "../include/Object.h"
#include <iostream>

/*
	Constructor
*/
Object::Object(glm::dvec3 _position, glm::dvec3 _color, bool _diffuse, bool _transparent)
{
	position = _position;
	color = _color;
	diffuse = _diffuse;
	transparent = _transparent;
}

/*
	Bool functions
*/
bool Object::isDiffuse()
{
	return diffuse;
}

bool Object::isTransparent()
{
	return transparent;
}