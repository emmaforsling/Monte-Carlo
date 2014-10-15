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

/*
	This function should calculate the intersectionpoints between a ray 
	and the surface of the Sphere. //For the surface of the sphere, use the radius
	and the centerpoint. //
	Zero intersection corresponds to a miss
	One intersection corresponds to tangential hit
	If(two)
		If(Outside the sphere)
			//determine correct intersectionPoint
			compare the length of the vectors from the ray's 
			origin to the two intersection points
			Select the closer one....
		If(Inside the sphere)
*/
glm::vec3 Sphere::calculateIntersection(Ray* ray{
	//TODO: Write code
	return glm::vec3(0.0,0.0,0.0);
}

void Sphere::calculateChildRays()
{
	//TODO: Write code
}