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
	// position = glm::vec3(0.0,0.0,0.0);
	radius = 0.0;
	transparent = false;
	refractiveIndex = 0.0;
}

/* The real del constructor */
Sphere::Sphere(glm::vec3 _position, float _radius, bool _transparent, float _refractiveIndex)
: Object(_position)
{
	// position = _position;
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
	std::cout << "\n\n TIME FOR SPHERE \n\n";
	//initialize the variables
	glm::vec3 startingPoint = _ray->getStartingPoint();
	std::cout << "startingPoint: " << startingPoint.x << ", " << startingPoint.y << ", " << startingPoint.z << std::endl;
	glm::vec3 direction = _ray->getDirection();
	std::cout << "Direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
	glm::vec3 centerPoint = position;
	std::cout << "CenterPoint: " << centerPoint.x << ", " << centerPoint.y << ", " << centerPoint.z << std::endl;

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

	std::cout << "a = " << a << "\nb = " << b << "\nc = "<< c << std::endl;
	//calculates delta
	delta = b*b - 4*a*c;
	
	std::cout << "delta = " << delta << std::endl;
	
	if(delta<0)	//no intersection
	{
		std::cout << "NO intersection" << std::endl;
		return glm::vec3(0.0,0.0,0.0); //no intersection
	}
	else if(delta == 0)	//single intersection
	{
		std::cout << "One intersection" << std::endl;
		t = -b/(2*a);
		std::cout << "t = " << t << std::endl;
		std::cout << "Returning glm::vec3(" << t*direction.x << ", " << t*direction.y << ", " << t*direction.z << ")"<< std::endl;
		return t * direction; //returns the point where it intersects
	}
	else //if(delta>0)	//two intersections
	{
		std::cout << "Two intersections" << std::endl;
		t1 = (-b - sqrt(delta))/(2*a);
		t2 = (-b + sqrt(delta))/(2*a);

		std::cout << "t1 = " << t1 << std::endl;
		std::cout << "t2 = " << t2 << std::endl;
		if(_ray->isInsideObject())			//if true
		{
			glm::vec3 tmp;
			tmp.x = startingPoint.x + std::max(t1,t2) * direction.x;
			tmp.y = startingPoint.y + std::max(t1,t2) * direction.y;
			tmp.z = startingPoint.z + std::max(t1,t2) * direction.z;
			std::cout << "Returning glm::vec3(" << tmp.x << ", " << tmp.y << ", " << tmp.z << ")"<< std::endl;
			return tmp;
		}	
		else
		{
			glm::vec3 tmp;
			tmp.x = startingPoint.x + std::min(t1,t2) * direction.x;
			tmp.y = startingPoint.y + std::min(t1,t2) * direction.y;
			tmp.z = startingPoint.z + std::min(t1,t2) * direction.z;
			std::cout << "Returning glm::vec3(" << tmp.x << ", " << tmp.y << ", " << tmp.z << ")"<< std::endl;
			//return startingPoint + std::min(t1,t2) * direction;
			return tmp;
		}			
	}
}

void Sphere::calculateChildRays()
{
	//Here we shall change the bool insideobject
	//TODO: Write code
}
