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
	transparency = 0.0;
	refractiveIndex = 0.0;
	//TODO: Write code 
}

/* The real del constructor */
Sphere::Sphere(glm::vec3 pos, float rad, float trans, float refract)
{
	position = pos;
	radius = rad;
	transparency = trans;
	refractiveIndex = refract;
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