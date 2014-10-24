#include "../include/Ray.h"
#include <iostream>

/* 	Class Ray  
	
	private members:
	- glm::vec3 startingPoint;
	- glm::vec3 direction;
	- float importance;
	- glm::vec3 color;							// vec4 for alpha?
	- bool finalNode;
	- Ray* childNodes;
	- bool insideObject;
*/

/* Default Constructor */
Ray::Ray()
{
	startingPoint = glm::vec3(0.0, 0.0, 0.0);
	direction = glm::vec3(0.0, 0.0, 0.0);
	importance = 0;
	color = glm::vec3(0.0, 0.0, 0.0);
	finalNode = false;
	childNodes = nullptr;
	insideObject = false;
}

Ray::Ray(glm::vec3 _startingPoint, glm::vec3 _direction, float _importance, glm::vec3 _color, bool _insideObject)
{
	startingPoint = _startingPoint;
	direction = _direction;
	importance = _importance;
	color = _color;
	insideObject = _insideObject;
	finalNode = false;
	childNodes = nullptr;
}

/* Destructor */
Ray::~Ray()
{
 	//std::cout << "hej!" << std::endl;
 	delete childNodes;
}

/* 	
	Combines color contributions from childNodes and
	a local lighting model (Phong's) to a single RGB vector 
*/
glm::vec3 Ray::calculateColor()
{
	// TODO: Write Code
	// Track ray through its children and blend final color.
	return glm::vec3(0.0, 0.0, 0.0);
}

/*
	Returns the startingPoint
*/
glm::vec3 Ray::getStartingPoint()
{
	return startingPoint;
}

/*
	Returns the direction
*/
glm::vec3 Ray::getDirection()
{
	return direction;
}

/*
	Returns true/false 
*/
bool Ray::isInsideObject()
{
	return insideObject;
}

float Ray::getImportance()
{
	return importance;
}

glm::vec3 Ray::getColor(){
	return color;
}


/* 	Computes Le(x,theta) for the point where a ray
	intersects a surface
*/
void Ray::calculateLocalLightingContribution()
{
	//TODO: Write Code
}
