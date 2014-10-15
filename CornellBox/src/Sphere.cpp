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
{
	position = glm::vec3(0.0,0.0,0.0);
	radius = 0.0;
	transparency = false;
	refractiveIndex = 0.0;
}

/* The real del constructor */
Sphere::Sphere(glm::vec3 _position, float _radius, bool _transparency, float _refractiveIndex)
{
	position = _position;
	radius = _radius;
	transparency = _transparency;
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
glm::vec3 Sphere::calculateIntersection(Ray* ray)
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
	glm::vec3 startingPoint = ray->getStartingPoint();
	glm::vec3 direction = ray->getDirection();
	glm::vec3 centerPoint = position;

	float a = 0.0, b = 0.0, c = 0.0;
	float delta = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;

	//calculates a, b and c
	a = (direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z);
	b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
			(direction.y)*(startingPoint.y - centerPoint.y) +
			(direction.z)*(startingPoint.z - centerPoint.z) );
	c = (startingPoint.x - centerPoint.x)*(startingPoint.x - centerPoint.x) +
		(startingPoint.y - centerPoint.y)*(startingPoint.y - centerPoint.y) +
		(startingPoint.z - centerPoint.z)*(startingPoint.z - centerPoint.z);

	//calculates delta
	delta = b*b - 4*a*c;
	
	std::cout << "delta = " << delta << std::endl;
	
	if(delta<0)	//no intersection
	{
		return glm::vec3(0.0,0.0,0.0); //no intersection
	}
	else if(delta == 0)	//single intersection
	{
		t = -b/(2*a);
		return t * direction; //returns the point where it intersects
	}
	else //if(delta>0)	//two intersections
	{
		t1 = (-b - sqrt(delta))/(2*a);
		t2 = (-b + sqrt(delta))/(2*a);
		if(ray->isInsideObject())			//if true
			return std::max(t1,t2) * direction;
		else
			return std::min(t1,t2) * direction;
	}

}

void Sphere::calculateChildRays()
{
	//TODO: Write code
}