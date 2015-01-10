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
	importance = 0.0;
	color = glm::dvec3(0.0, 0.0, 0.0);
	finalNode = false;
	//childNodes = nullptr;
	reflectedRay = nullptr;
	refractedRay = nullptr;
	insideObject = false;
	//std::cout << "\n\n HELLLO MEEE THIS IS WORLD\n" << std::endl;
}

/*
	Constructor
*/
Ray::Ray(glm::dvec3 _startingPoint, glm::dvec3 _direction, double _importance, glm::dvec3 _color, bool _insideObject)
{
	//std::cout << "startingPoint = (" << _startingPoint.x << ", " << _startingPoint.y << ", " << _startingPoint.z << ")" << std::endl;
	startingPoint = _startingPoint;
	direction = _direction/glm::length(_direction);
	importance = _importance;
	color = _color;
	insideObject = _insideObject;
	finalNode = false;
	//childNodes = nullptr;
	reflectedRay = nullptr;
	refractedRay = nullptr;
}

/*
	Destructor
*/
Ray::~Ray()
{
 	//delete childNodes;
 	//delete reflectedRay;
	//delete refractedRay;
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
	return glm::dvec3(1.0, 0.0, 0.0);
}


glm::dvec3 Ray::calculateLocalLightingContribution(Object* _object, glm::dvec3 _directionToLight, double _radiance, int _iteration)
{	
	glm::dvec3 normal_surface = glm::normalize(_object->getIntersectedNormal());
	glm::dvec3 color_surface = _object->getColor();
	
	//std::cout << "color at surface: = " << color_surface.x << ", " << color_surface.y << ", " << color_surface.z << ")" << std::endl;
	//std::cout << "normal at surface: = " << normal_surface.x << ", " << normal_surface.y << ", " << normal_surface.z << ")" << std::endl;
	
	//std::cout << "shadowRay direction = " << rayToLightSource.x << ", " << rayToLightSource.y << ", " << rayToLightSource.z << std::endl;
	//std::cout << "magnitude = " << glm::length(rayToLightSource) << std::endl;
	glm::dvec3 color_ray = glm::dvec3(1.0,1.0,1.0); 		//temporary

	// Using Lambertian surfaces: Id * kd * (L ° N)
	double cosineOfAngle = glm::dot(normal_surface, glm::normalize(_directionToLight));
	glm::dvec3 lightingContribution = glm::dvec3(0.0, 0.0, 0.0);
	//std::cout << "dot = " << cosineOfAngle << std::endl;

	if(cosineOfAngle <= 0)
	{
		// lightingContribution = color_ray * color_surface * _radiance;
		// return lightingContribution;
		return /*lightingContribution*/ glm::dvec3(0.0, 0.0, 0.0);
	}	
	if(cosineOfAngle > 0 && cosineOfAngle <= 1)
	{
		lightingContribution = color_ray * color_surface * cosineOfAngle * _radiance;
		if(_iteration == 2)
		{
			// std::cout << "är det här vi får noll?" << std::endl;	
			// std::cout << "lightingContribution = (" << lightingContribution.x << ", " << lightingContribution.y << ", " << lightingContribution.z << std::endl;
			// std::cout << "radiance = " << _radiance << std::endl;
			// std::cout << "color_surface = (" << color_surface.x << ", " << color_surface.y << ", " << color_surface.z << ")" << std::endl;
			// std::cout << "normal at surface: = " << normal_surface.x << ", " << normal_surface.y << ", " << normal_surface.z << ")" << std::endl;		
		}
		
		return lightingContribution;
	}
	return glm::dvec3(0.0,1.0,1.0);

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
	
	// TODO
	return false;
}
