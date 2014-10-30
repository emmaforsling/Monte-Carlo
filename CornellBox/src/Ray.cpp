#include "../include/Ray.h"
#include <iostream>

#include "../include/Object.h"

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
	direction = _direction/glm::length(_direction);
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


glm::vec3 Ray::calculateLocalLightingContribution(Object* _object, Ray* _shadowRay)
{
	/*
		First - diffuse, transparent or intransparent
	*/
	// Initializing variables for the surface
	bool transparent = _object->isTransparent();
	bool diffuse = _object->isDiffuse();
	
	glm::vec3 normal_surface = _object->getIntersectedNormal();
	glm::vec3 color_surface = _object->getColor();
	
	glm::vec3 rayToLightSource = - _shadowRay->getDirection();
	//std::cout << "shadowRay direction = " << rayToLightSource.x << ", " << rayToLightSource.y << ", " << rayToLightSource.z << std::endl;
	//std::cout << "magnitude = " << glm::length(rayToLightSource) << std::endl;
	glm::vec3 color_ray = glm::vec3(1.0,1.0,1.0); 		//temporary

	// if(diffuse)					// If diffuse surface
	// {
		// Using phong Id * kd * (L ° N)
		float dotproduct = glm::dot(normal_surface, rayToLightSource);
		glm::vec3 returningthing = glm::vec3(0.0, 0.0, 0.0);
		//std::cout << "dot = " << dotproduct << std::endl;
		if(dotproduct <= 0)
		{
			return returningthing;
		}	
		if(dotproduct > 0 && dotproduct <= 1)
		{
			returningthing = color_ray * color_surface * dotproduct;
			return returningthing;
		}
		return glm::vec3(0.0,0.0,0.0);

	// }
	// else if(transparent)		// If the surface is transparent
	// {	
	// 	return glm::vec3(0.0,0.0,0.0);

	// }
	// else if(!transparent)		// If the surface is intransparent
	// {
	// 	return glm::vec3(0.0,0.0,0.0);
	// }
	// else
	// {
	// 	std::cout << "This message should not be displayed, and is only here for debugging" << std::endl;
	// 	return glm::vec3(0.0,0.0,0.0);
	// }
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

void Ray::setIsInsideObject(bool _insideObject)
{
	//std::cout << "setting isInsideObject to " << _insideObject << std::endl;
	insideObject = _insideObject;
}

