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
glm::vec3 Sphere::calculateIntersection(Ray* ray){
	//TODO: Write code
	
	glm::vec3 intersection = position + glm::vec3(radius,radius,radius);
	/*
		Using the equations:
			S: r^2 = x^2 + y^2 + z^2		//for sphere
			R = t*(x,y,z)
			where 
			t = direction.xyz
			//förfinar denna text snart

			And rewrote them into 
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
	ray->startingPoint

	return glm::vec3(0.0,0.0,0.0); //returns the point where it intersects
}

void Sphere::calculateChildRays()
{
	//TODO: Write code
}