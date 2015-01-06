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
	intersectedNormal = glm::dvec3(0.0,0.0,0.0);
}

/*
	Constructor
*/
Sphere::Sphere(glm::dvec3 _position, double _radius, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse)
: Object(_position, _color, _diffuse, _transparent)
{
	color = _color;
	radius = _radius;
	refractiveIndex = _refractiveIndex;
}
/*
	Calculation functions
*/
glm::dvec3 Sphere::calculateIntersection(Ray* _ray, bool _isShadowRay)
{
	//glm::dvec3 direction2 = _ray->getDirection();
	//std::cout << "\tSphere::calculateIntersection(), incoming direction of ray = (" << direction2.x << ", " << direction2.y << ", " << direction2.z << std::endl;
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
	glm::dvec3 direction = glm::normalize(_ray->getDirection());
	// std::cout << "direction " << direction.x << ", " << direction.y << ", " << direction.z << std::endl; 
	//if(glm::length(direction) == 0)
		//std::cout << "EMMMMMMMMMAAAAAA" << std::endl;
	// Set the centerPoint for the sphere to the position given as an argument to the constructor
	glm::dvec3 centerPoint = position;
	
	// Calculate a, b and c
	a = 1.0;//(direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z);
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
		if(!_isShadowRay)
		{
			intersectedNormal = glm::dvec3(0.0,0.0,0.0);
		}
		//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta < 0)" << std::endl;
		
		return finalIntersection;
	}
	else if(delta == 0)								// Single intersection
	{
		t = -b/(2*a);
		finalIntersection = startingPoint + t * direction;
		if(!_isShadowRay)
		{
			intersectedNormal = glm::normalize(finalIntersection - centerPoint);
		}
		//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta == 0)" << std::endl;
		// std::cout << "1. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;
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
			finalIntersection = startingPoint + max_t * direction;
			if(!_isShadowRay)
			{
				intersectedNormal = glm::normalize(finalIntersection - centerPoint);
			}
			//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta > 0 + inside)" << std::endl;
			//std::cout << "I'm inside!" << std::endl;
			// std::cout << "2. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;
			return finalIntersection;
		}	
		else
		{

			// if the smallest value of t (t_min) is positive, it corresponds to the closest point in the positive direction of the ray,
			// which is the point of interest.

			if(min_t > 0.0)
			{
				finalIntersection = (1000.0 * startingPoint + 1000.0 * min_t * direction)/1000.0;
			}
			// if the smallest value of t (t_min) is zero, it corresponds to the ray origin, which is not of intersest. Instead,
			// the greatest value (max_t), which corresponds to a point farther along the ray direction, is of interest.
			else if(min_t == 0)
			{
				finalIntersection = (1000.0 * startingPoint + 1000.0 * max_t * direction)/1000.0;
			}
			// if the smallest value of t is negative, it corresponds to a point along the negative ray direction,
			// which never is of interest.
			else{
				// do nothing
			}
			
			/* ====== En annan variant... ======
			t = (-b + sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
				finalIntersection = startingPoint + (direction * t);
			}
			
			t = (-b - sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
				finalIntersection = startingPoint + (direction * t);
			}
			===================================*/

			// if the incoming ray is not a shadow ray, update intersectedNormal.
			if(!_isShadowRay)
			{
				intersectedNormal = glm::normalize(finalIntersection - centerPoint);
			}
			//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta > 0 + outside)" << std::endl;
			// std::cout << "3. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;

			return finalIntersection;
		}			
	}
}

void Sphere::calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint)				// TEMPORARY
{
	// 
	glm::dvec3 testIntersectionPoint = (1000.0*intersectionPoint + (1000.0* 0.1 * intersectedNormal) )/1000.0;
	/*testIntersectionPoint.x = testIntersectionPoint.x > 5 ? 4.9 : testIntersectionPoint.x;
	testIntersectionPoint.y = testIntersectionPoint.y > 5 ? 4.9 : testIntersectionPoint.y;
	testIntersectionPoint.z = testIntersectionPoint.z > 5 ? 4.9 : testIntersectionPoint.z;
*/
	// testIntersectionPoint.x > 5 ? testIntersectionPoint.x = 4.9 : testIntersectionPoint.x = testIntersectionPoint.x;
	// testIntersectionPoint.y > 5 ? testIntersectionPoint.y = 4.9 : testIntersectionPoint.y = testIntersectionPoint.y;
	// testIntersectionPoint.z > 5 ? testIntersectionPoint.z = 4.9 : testIntersectionPoint.z = testIntersectionPoint.z;
	//fattar inte på detta

	//std::cout << "HEEEEELLLLOOOOO???!?!?" << std::endl;
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
	glm::dvec3 direction = _ray->getDirection();
	//std::cout << "CalculateChildRay, direction " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;

	if(transparent)
	{
		//std::cout << "CALCULATING REFRACTION" << std::endl;
		if(_ray->isInsideObject())
		{
			//reflectedRayDirection = glm::reflect(_ray->getDirection(), -intersectedNormal);
			refractedRayDirection = glm::refract(direction, intersectedNormal, 1.0/refractiveIndex);
			refractedRayIsInside = false;
		}
		else
		{
			//reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
			refractedRayDirection = glm::refract(direction, intersectedNormal, refractiveIndex);
			refractedRayIsInside = true;
		}
		
		//_ray->isInsideObject() ? refractedRayIsInside = false : refractedRayIsInside = true;

		//_ray->childNodes = new Ray(intersectionPoint, reflectedRayDirection, _ray->getImportance(), color, false);
		//std::cout << "refracted ray direction in calculateChildRays = (" << refractedRayDirection.x << ", " << refractedRayDirection.y << ", " << refractedRayDirection.z << ")" << std::endl;
		//if(glm::length(refractedRayDirection) != 0)
		//{
			_ray->childNodes = new Ray(testIntersectionPoint, refractedRayDirection, _ray->getImportance(), color, refractedRayIsInside);
		//}
	}
	else
	{
		//std::cout << "CALCULATING REFLECTION" << std::endl;
		reflectedRayDirection = glm::reflect(glm::normalize(direction), glm::normalize(intersectedNormal));
		//std::cout << "interseted onormal: (" << intersectedNormal.x << ", " << intersectedNormal.y << ", " << intersectedNormal.z << ")" << std::endl;
		//std::cout << "IntersectionPoint = (" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ")" << std::endl;
		// std::cout << "Sphere::calcChild, Direction = (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
		// std::cout << "Sphere::calcChild, intersectedNormal = (" << intersectedNormal.x << ", " << intersectedNormal.y << ", " << intersectedNormal.z << ")" << std::endl;
		//std::cout << "testIntersectionPoint = (" << testIntersectionPoint.x << ", " << testIntersectionPoint.y << ", " << testIntersectionPoint.z << ")" << std::endl;
		glm::dvec3 test = _ray->reflectRay(direction, intersectedNormal);	// Kallar på den egna funktionen
		//std::cout << "ray direction in calculateChildRays: (" << test.x << ", " << test.y << ", " << test.z << ")" << std::endl;
		// std::cout << "reflected ray direction in calculateChildRays = (" << reflectedRayDirection.x << ", " << reflectedRayDirection.y << ", " << reflectedRayDirection.z << ")" << std::endl;
		_ray->childNodes = new Ray(testIntersectionPoint, test/*glm::normalize(reflectedRayDirection)*/, _ray->getImportance(), color, false);
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


