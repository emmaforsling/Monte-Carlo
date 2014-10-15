#include "../include/Sphere.h"

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

glm::vec3 Sphere::calculateIntersection()
{
	//TODO: Write code
	return glm::vec3(0.0,0.0,0.0);
}

void Sphere::calculateChildRays()
{
	//TODO: Write code
}