#include "../include/Ray.h"
#include <iostream>

#include "../include/Object.h"

/* 	Class Ray  
	
	private members:
	- glm::dvec3 color;							// vec4 for alpha?
	- glm::dvec3 direction;
	- bool insideObject;
	- bool finalNode;
	- double importance;
	- glm::dvec3 startingPoint;

	public variables:
	- Ray* childNodes;
	- glm::dvec3 intersectionPoint
*/

/* 
	Empty constructor
*/
Ray::Ray()
{
	startingPoint = glm::dvec3(0.0, 0.0, 0.0);
	direction = glm::dvec3(0.0, 0.0, 0.0);
	importance = 0;
	color = glm::dvec3(0.0, 0.0, 0.0);
	finalNode = false;
	childNodes = nullptr;
	insideObject = false;
}

/*
	Constructor
*/
Ray::Ray(glm::dvec3 _startingPoint, glm::dvec3 _direction, double _importance, glm::dvec3 _color, bool _insideObject)
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
glm::dvec3 Ray::calculateColor()
{
	/* 	
	Combines color contributions from childNodes and
	a local lighting model (Phong's) to a single RGB vector 
	*/
	
	// TODO: Write Code
	// Track ray through its children and blend final color.
	return glm::dvec3(0.0, 0.0, 0.0);
}


glm::dvec3 Ray::calculateLocalLightingContribution(Object* _object, Ray* _shadowRay)
{
	/*
		First - diffuse, transparent or intransparent
	*/
	// Initializing variables for the surface
	bool transparent = _object->isTransparent();
	bool diffuse = _object->isDiffuse();
	
	glm::dvec3 normal_surface = _object->getIntersectedNormal();
	glm::dvec3 color_surface = _object->getColor();
	
	glm::dvec3 rayToLightSource = - _shadowRay->getDirection();
	//std::cout << "shadowRay direction = " << rayToLightSource.x << ", " << rayToLightSource.y << ", " << rayToLightSource.z << std::endl;
	//std::cout << "magnitude = " << glm::length(rayToLightSource) << std::endl;
	glm::dvec3 color_ray = glm::dvec3(1.0,1.0,1.0); 		//temporary

	// if(diffuse)					// If diffuse surface
	// {
		// Using phong Id * kd * (L ° N)
		double dotproduct = glm::dot(normal_surface, rayToLightSource);
		glm::dvec3 returningthing = glm::dvec3(0.0, 0.0, 0.0);
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
		return glm::dvec3(0.0,0.0,0.0);

	// }
	// else if(transparent)		// If the surface is transparent
	// {	
	// 	return glm::dvec3(0.0,0.0,0.0);

	// }
	// else if(!transparent)		// If the surface is intransparent
	// {
	// 	return glm::dvec3(0.0,0.0,0.0);
	// }
	// else
	// {
	// 	std::cout << "This message should not be displayed, and is only here for debugging" << std::endl;
	// 	return glm::dvec3(0.0,0.0,0.0);
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
glm::dvec3 Ray::getColor()
{
	return color;
}

glm::dvec3 Ray::getDirection()
{
	return direction;
}

double Ray::getImportance()
{
	return importance;
}

glm::dvec3 Ray::getStartingPoint()
{
	return startingPoint;
}

/*
	Set functions
*/
void Ray::setIsInsideObject(bool _insideObject)
{
	//std::cout << "setting isInsideObject to " << _insideObject << std::endl;
	insideObject = _insideObject;
}

/*
	Bool functions
*/
bool Ray::isInsideObject()
{
	return insideObject;
}



bool Ray::russianRoulette(glm::dvec3 colorForTheReflectedRay, double survivalOds)
{
	//colorForTheReflectedRay - kanske skicka med en Ray* till den reflected rayen och kalla på funktionen getColor, eller color
	/*
		
	*/
	// double p = MAX(colorForTheReflectedRay[0], MAX(colorForTheReflectedRay[1],colorForTheReflectedRay[2]));
	// // får inte ekvationen att gå ihop
	return false;
}

/*
	Reflect and refract
*/
glm::dvec3 Ray::reflectRay(glm::dvec3 _direction, glm::dvec3 _intersectedNormal)
{
	/*
	   I  N  R
	   ^  ^  ^
		\ | /
		 \|/

		perfect reflection
		R = I - 2(dot(N,I)N)
	*/

	glm::dvec3 normal_surface = _intersectedNormal;
	glm::dvec3 ray_from_lightsourve = _direction;
	
	double dotN_I = glm::dot(normal_surface, ray_from_lightsourve);
	//std::cout << "Normal: " << normal_surface.x << ", " << normal_surface.y << ", " << normal_surface.z << std::endl;
	//std::cout << "Ray from lightsource: " << ray_from_lightsourve.x << ", " << ray_from_lightsourve.y << ", " << ray_from_lightsourve.z << std::endl;
	//std::cout << "dotN_I " << dotN_I << std::endl;
	
	// FUlkod, då fel uppstår vid * operatorn for glm
	glm::dvec3 temp;
	temp.x = 2.0 * dotN_I * normal_surface.x;
	temp.y = 2.0 * dotN_I * normal_surface.y;
	temp.z = 2.0 * dotN_I * normal_surface.z;
	
	glm::dvec3 _R = ray_from_lightsourve - temp;
	//std::cout << "Reflected ray = " << _R.x << ", " << _R.y << ", " << _R.z << std::endl;
	
	return _R;
}

glm::dvec3 Ray::refractRay()
{
	return glm::dvec3(0.0, 0.0, 0.0);
}
