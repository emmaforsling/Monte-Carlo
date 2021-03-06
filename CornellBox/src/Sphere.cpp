#include "../include/Sphere.h"
#include <iostream>
/* 	
	Class Sphere  
	
	private members:
	- glm::dvec3 position;
	- double radius;
	- double transparency;
	- double refractiveIndex;
*/

/* 
	Emtpy constructor
*/
Sphere::Sphere()
: Object(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0 ,0.0), false, false)
{
	radius = 0.0;
	refractiveIndex = 0.0;
}

/*
	Constructor
*/
Sphere::Sphere(glm::dvec3 _position, double _radius, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse)
: Object(_position, _color, _diffuse, _transparent)
{
	radius = _radius;
	refractiveIndex = _refractiveIndex;
}

/*
	Calculation functions
*/
glm::dvec3 Sphere::calculateIntersection(Ray* _ray)
{
	/*

	This function should calculate the intersectionpoints between a ray 
	and the surface of the Sphere.

		Using the equations:
			S: r^2 = x^2 + y^2 + z^2		
			R = t*(x,y,z)
			where 
			t = direction

			The equation is then rewritten into this:

			a = (direction.x)^2 + (direction.y)^2 + (direction.z)^2;
			b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
					(direction.y)*(startingPoint.y - centerPoint.y) +
					(direction.z)*(startingPoint.z - centerPoint.z));
			c = (startingPoint.x - centerPoint.x)^2 +
				(startingPoint.y - centerPoint.y)^2 +
				(startingPoint.z - centerPoint.z)^2;

			then
			delta = b^2 + 4*a*c;

			if(delta<0) no intersection
			if(delta==0) one intersection
			if(delta>0) two intersection

	*/

	// Initializing the variables
	double a = 0.0, b = 0.0, c = 0.0;
	double delta = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
	glm::dvec3 finalIntersection = glm::dvec3(0.0, 0.0, 0.0);

	// Get the startingPoint for the ray
	glm::dvec3 startingPoint = _ray->getStartingPoint();

	// Get the direction for the ray
	glm::dvec3 direction = _ray->getDirection();
	
	// Set the centerPoint for the sphere to the position given as an argument to the constructor
	glm::dvec3 centerPoint = position;
	
	// Calculate a, b and c
	a = (direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z);
	b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
			(direction.y)*(startingPoint.y - centerPoint.y) +
			(direction.z)*(startingPoint.z - centerPoint.z) );
	c = (startingPoint.x - centerPoint.x)*(startingPoint.x - centerPoint.x) +
		(startingPoint.y - centerPoint.y)*(startingPoint.y - centerPoint.y) +
		(startingPoint.z - centerPoint.z)*(startingPoint.z - centerPoint.z)
		- radius*radius;

	// Calculate delta
	delta = b*b - 4*a*c;
		
	if(delta<0)										// No intersection
	{	
		intersectedNormal = glm::dvec3(0.0,0.0,0.0);
		return finalIntersection;
	}
	else if(delta == 0)								// Single intersection
	{
		t = -b/(2*a);
		finalIntersection = t * direction;
		intersectedNormal = (finalIntersection - centerPoint)/radius;
		return finalIntersection; //returns the point where it intersects
	}
	else //if(delta>0)								// Two intersections
	{
		
		t1 = (-b - sqrt(delta))/(2*a);
		t2 = (-b + sqrt(delta))/(2*a);

		double min_t = std::min(t1,t2);
		double max_t = std::max(t1,t2);

		if(_ray->isInsideObject())
		{
			//std::cout << "Ray inside object!" << std::endl;
			finalIntersection.x = startingPoint.x + max_t * direction.x;
			finalIntersection.y = startingPoint.y + max_t * direction.y;
			finalIntersection.z = startingPoint.z + max_t * direction.z;
			intersectedNormal = (finalIntersection - centerPoint)/radius;
			return finalIntersection;
		}	
		else
		{
			
			if(min_t != 0.0)
			{
				finalIntersection.x = startingPoint.x + min_t * direction.x;
				finalIntersection.y = startingPoint.y + min_t * direction.y;
				finalIntersection.z = startingPoint.z + min_t * direction.z;
			}
			else
			{
				finalIntersection.x = startingPoint.x + max_t * direction.x;
				finalIntersection.y = startingPoint.y + max_t * direction.y;
				finalIntersection.z = startingPoint.z + max_t * direction.z;
			}
			intersectedNormal = (finalIntersection - centerPoint)/radius;
			return finalIntersection;
		}			
	}
}

void Sphere::calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint)				// TEMPORARY
{
	// // std::cout << "\nCalculating child ray for intersection point " << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << std::endl << std::endl;
	// calculate direction for reflected or transmitted ray - WHITTED - (TEMPORARY)
	// // std::cout << "====== Reflection/refraction =====" << std::endl;
	// glm::dvec3 reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
	// // std::cout << "reflection = (" << reflectedRayDirection.x << ", " << reflectedRayDirection.y << ", " << reflectedRayDirection.z << ")" << std::endl;

	// glm::dvec3 refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, refractiveIndex);
	// // std::cout << "refraction = (" << refractedRayDirection.x << ", " << refractedRayDirection.y << ", " << refractedRayDirection.z << ")" << std::endl;

	glm::dvec3 newRayDirection;
	glm::dvec3 reflectedRayDirection;
	glm::dvec3 refractedRayDirection;
	bool refractedRayIsInside;
	if(transparent)
	{
		if(_ray->isInsideObject())
		{
			//reflectedRayDirection = glm::reflect(_ray->getDirection(), -intersectedNormal);
			refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, 1.0/refractiveIndex);
			refractedRayIsInside = false;
		}
		else
		{
			//reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
			refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, refractiveIndex);
			refractedRayIsInside = true;
		}
		
		//_ray->isInsideObject() ? refractedRayIsInside = false : refractedRayIsInside = true;

		//_ray->childNodes = new Ray(intersectionPoint, reflectedRayDirection, _ray->getImportance(), color, false);
		_ray->childNodes = new Ray(intersectionPoint, refractedRayDirection, _ray->getImportance(), color, refractedRayIsInside);
	}
	else
	{
		reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
		_ray->childNodes = new Ray(intersectionPoint, reflectedRayDirection, _ray->getImportance(), color, false);
	}
}

/*
	Get functions
*/
glm::dvec3 Sphere::getColor()
{
	return color;
}

glm::dvec3 Sphere::getIntersectedNormal()
{
	return intersectedNormal;
}

int Sphere::getIntersectedSide()
{
	intersectedSide = 666;
	return intersectedSide;
}

double Sphere::getRefractiveIndex()
{
	return refractiveIndex;
}

/*
	Set functions
*/
void Sphere::setIntersectedNormal(glm::dvec3 _intersectedNormal)
{
	intersectedNormal = _intersectedNormal;
}


