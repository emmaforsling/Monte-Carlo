#include "../include/Ray.h"
#include <iostream>

/* 	Class Ray  
	
	private members:
	- glm::vec3 color;							// vec4 for alpha?
	- glm::vec3 direction;
	- bool insideObject;
	- bool finalNode;
	- float importance;
	- glm::vec3 startingPoint;

	public variables:
	- Ray* childNodes;
	- glm::vec3 intersectionPoint
*/

/* 
	Empty constructor
*/
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

/*
	Constructor
*/
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

/*
	Destructor
*/
Ray::~Ray()
{
 	delete childNodes;
}

/*
	Calculation functions
*/
glm::vec3 Ray::calculateColor()
{
	/* 	
	Combines color contributions from childNodes and
	a local lighting model (Phong's) to a single RGB vector 
	*/
	
	// TODO: Write Code
	// Track ray through its children and blend final color.
	return glm::vec3(0.0, 0.0, 0.0);
}


void Ray::calculateLocalLightingContribution()
{
	/* 
		Computes Le(x,theta) for the point where a ray
		intersects a surface
	*/

	//TODO: Write Code
}

/*
	Get functions
*/
glm::vec3 Ray::getColor()
{
	return color;
}

glm::vec3 Ray::getDirection()
{
	return direction;
}

float Ray::getImportance()
{
	return importance;
}

glm::vec3 Ray::getStartingPoint()
{
	return startingPoint;
}

/*
	Bool functions
*/
bool Ray::isInsideObject()
{
	return insideObject;
}

