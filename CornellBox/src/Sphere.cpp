#include "../include/Sphere.h"
#include <iostream>
/* 	
	Class Sphere  
	
	private members:
	- glm::vec3 position;
	- float radius;
	- float transparency;
	- float refractiveIndex;
*/

/* Default Constructor */
Sphere::Sphere()
: Object(glm::vec3(0.0,0.0,0.0))
{
	radius = 0.0;
	transparent = false;
	refractiveIndex = 0.0;
}

/* The real del constructor */
Sphere::Sphere(glm::vec3 _position, float _radius, bool _transparent, float _refractiveIndex)
: Object(_position)
{
	radius = _radius;
	transparent = _transparent;
	refractiveIndex = _refractiveIndex;
}

/* Destructor */
Sphere::~Sphere()
{
	//TODO: Write code 
}

/*
	This function should calculate the intersectionpoints between a ray 
	and the surface of the Sphere.
*/
glm::vec3 Sphere::calculateIntersection(Ray* _ray)
{
	/*
		Using the equations:
			S: r^2 = x^2 + y^2 + z^2		
			R = t*(x,y,z)
			where 
			t = direction.xyz

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
	//initialize the variables
	glm::vec3 startingPoint = _ray->getStartingPoint();
	glm::vec3 direction = _ray->getDirection();
	std::cout << "==== studying sphere (" << position.x << ", " << position.y << ", " << position.z << "), r = " << radius << " ==== "; //\n";
	//std::cout << "starting point of ray: " << startingPoint.x << ", " << startingPoint.y << ", " << startingPoint.z << std::endl;
	//std::cout << "Direction of ray: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
	glm::vec3 centerPoint = position;
	//std::cout << "CenterPoint of sphere: " << centerPoint.x << ", " << centerPoint.y << ", " << centerPoint.z;
	//std::cout << ", radius of sphere: " << radius << std::endl;

	float a = 0.0, b = 0.0, c = 0.0;
	float delta = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;

	//calculates a, b and c
	a = (direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z);
	b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
			(direction.y)*(startingPoint.y - centerPoint.y) +
			(direction.z)*(startingPoint.z - centerPoint.z) );
	c = (startingPoint.x - centerPoint.x)*(startingPoint.x - centerPoint.x) +
		(startingPoint.y - centerPoint.y)*(startingPoint.y - centerPoint.y) +
		(startingPoint.z - centerPoint.z)*(startingPoint.z - centerPoint.z)
		- radius*radius;

	// std::cout << "a = " << a << "\nb = " << b << "\nc = "<< c << std::endl;
	// calculates delta
	delta = b*b - 4*a*c;
	
	// std::cout << "delta = " << delta << std::endl;
	glm::vec3 finalIntersection = glm::vec3(0.0, 0.0, 0.0);
	if(delta<0)	//no intersection
	{	
		std::cout << " - NO INTERSECTIONS - " << std::endl;
		intersectedNormal = glm::vec3(0.0,0.0,0.0);
		return finalIntersection; //no intersection
	}
	else if(delta == 0)	//single intersection
	{
		std::cout << " - ONE INTERSECTION - " << std::endl;
		t = -b/(2*a);
		finalIntersection = t * direction;
		//std::cout << "t = " << t << std::endl;
		//std::cout << "Returning glm::vec3(" << t*direction.x << ", " << t*direction.y << ", " << t*direction.z << ")"<< std::endl;
		intersectedNormal = (finalIntersection - centerPoint)/radius;
		return finalIntersection; //returns the point where it intersects
	}
	else //if(delta>0)	//two intersections
	{
		std::cout << " - TWO INTERSECTIONS - " << std::endl;
		t1 = (-b - sqrt(delta))/(2*a);
		t2 = (-b + sqrt(delta))/(2*a);

		//std::cout << "t1 = " << t1 << std::endl;
		//std::cout << "t2 = " << t2 << std::endl;
		if(_ray->isInsideObject())			//if true
		{
			
			finalIntersection.x = startingPoint.x + std::max(t1,t2) * direction.x;
			finalIntersection.y = startingPoint.y + std::max(t1,t2) * direction.y;
			finalIntersection.z = startingPoint.z + std::max(t1,t2) * direction.z;
			//std::cout << "Returning glm::vec3(" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ")"<< std::endl;
			intersectedNormal = (finalIntersection - centerPoint)/radius;
			return finalIntersection;
		}	
		else
		{
			glm::vec3 finalIntersection;
			finalIntersection.x = startingPoint.x + std::min(t1,t2) * direction.x;
			finalIntersection.y = startingPoint.y + std::min(t1,t2) * direction.y;
			finalIntersection.z = startingPoint.z + std::min(t1,t2) * direction.z;
			//std::cout << "Returning glm::vec3(" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ")"<< std::endl;
			//return startingPoint + std::min(t1,t2) * direction;
			intersectedNormal = (finalIntersection - centerPoint)/radius;
			return finalIntersection;
		}			
	}
}

void Sphere::calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint)				// TEMPORARY
{
	std::cout << "\nCalculating child ray for intersection point " << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << std::endl << std::endl;
	// calculate direction for reflected or transmitted ray - WHITTED - (TEMPORARY)
	std::cout << "====== Reflection/refraction =====" << std::endl;
	glm::vec3 reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
	std::cout << "reflection = (" << reflectedRayDirection.x << ", " << reflectedRayDirection.y << ", " << reflectedRayDirection.z << ")" << std::endl;

	glm::vec3 refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, refractiveIndex);
	std::cout << "refraction = (" << refractedRayDirection.x << ", " << refractedRayDirection.y << ", " << refractedRayDirection.z << ")" << std::endl;

	_ray->childNodes = new Ray(intersectionPoint, reflectedRayDirection, _ray->getImportance(), glm::vec3(0.0, 0.0, 0.0), false);
}

float Sphere::getRefractiveIndex()
{
	return refractiveIndex;
}

glm::vec3 Sphere::getIntersectedNormal()
{
	return intersectedNormal;
}

void Sphere::setIntersectedNormal(glm::vec3 _intersectedNormal)
{
	intersectedNormal = _intersectedNormal;
}
