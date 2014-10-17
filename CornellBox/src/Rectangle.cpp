#include "../include/Rectangle.h"

/* 	
	Class Rectangle  
	
	private members:
	- glm::vec3 positionsOfCorners[4];
*/

/* Default Constructor */
Rectangle::Rectangle()
{
	positionsOfCorners[0] = glm::vec3(0.0, 0.0, 0.0);
	positionsOfCorners[1] = glm::vec3(0.0, 0.0, 0.0);
	positionsOfCorners[2] = glm::vec3(0.0, 0.0, 0.0);
	positionsOfCorners[3] = glm::vec3(0.0, 0.0, 0.0);
}

/* Destructor */
Rectangle::~Rectangle()
{
	//TODO: Write code 
}


glm::vec3 Rectangle::calculateIntersection(Ray* ray)
{
	/*
		Plane: Ax + By + Cz + D = 0
		Line: x = startingPoint.x + (t * direction.x);
			  y = startingPoint.y + (t * direction.y);
			  z = startingPoint.z + (t * direction.z);
			 	(where x,y,z is the intersectionPoint)

		To determine A,B,C and D. Compute the crossproduct between two vectors
		v1 and v2.  Where
			v1 = positionsOfCorners[1] - positionsOfCorners[0];
			v2 = positionsOfCorners[3] - positionsOfCorners[0];

			glm::vec3 normal = glm::cross(v1,v2);
			
			where 
			A = normal.x
			B = normal.y
			C = normal.z
			
			To get D, derive the plane equation by:
			glm::vec3 D = glm::dot(positionsOfCorners[0], normal;

		When A, B, C and D is derived, combine the equation for the Plane and the Line
		to determine t (direction.xyz)
		
			float t = -( (A * startingPoint.x) + (B * startingPoint.y) + (C * startingPoint.z + D) )/
			( (A * direction.x) + (B * direction.y) +  (C * direction.z) )

		When t is derived, the intersectionPoint.xyz can be calculated!

	*/

	//initialize the variables
	float A = 0.0, B = 0.0, C = 0.0, D = 0.0, t = 0.0;
	glm::vec3 v1 = glm::vec3(0.0, 0.0, 0.0), v2 = glm::vec3(0.0, 0.0, 0.0), normal = glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 startingPoint = ray->getStartingPoint();
	glm::vec3 direction = ray->getDirection();
	glm::vec3 intersectionPoint = glm::vec3(0.0, 0.0, 0.0);

	//determine two vectors
	v1 = positionsOfCorners[1] - positionsOfCorners[0];
	v2 = positionsOfCorners[3] - positionsOfCorners[0];

	normal = glm::cross(v1,v2);

	A = normal.x;
	B = normal.y;
	C = normal.z;
	D = glm::dot(positionsOfCorners[0], normal);

	t = -( (A * startingPoint.x) + (B * startingPoint.y) + (C * startingPoint.z + D) )
				/( (A * direction.x) + (B * direction.y) +  (C * direction.z) );

	//Determine intersectionPoint
	intersectionPoint.x = startingPoint.x + (t * direction.x);
	intersectionPoint.y = startingPoint.y + (t * direction.y);
	intersectionPoint.z = startingPoint.z + (t * direction.z);

	return intersectionPoint;	//if glm::vec3(0.0,0.0,0.0) --> no intersection
}


void calculateChildRays()
{
	//TODO: Write code
}					