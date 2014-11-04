#include "../include/Rectangle.h"
#include <iostream>
/* 	
	Class Rectangle  

	private members:
	- double A,B,C,D
	- glm::dvec3 color
	- glm::vec2 normal
	
	public variables
	- glm::dvec3 positionsOfCorners[4]
*/

/* 
	Empty constructor
*/
Rectangle::Rectangle()
{
	positionsOfCorners[0] = glm::dvec3(0.0, 0.0, 0.0);
	positionsOfCorners[1] = glm::dvec3(0.0, 0.0, 0.0);
	positionsOfCorners[2] = glm::dvec3(0.0, 0.0, 0.0);
	positionsOfCorners[3] = glm::dvec3(0.0, 0.0, 0.0);
	normal = glm::dvec3(0.0, 0.0, 0.0);
}

/* 
	Destructor 
*/
Rectangle::~Rectangle()
{
	//TODO: Write code 
}

/*
	Calculations functions
*/

glm::dvec3 Rectangle::calculateIntersection(Ray* ray)
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

			glm::dvec3 normal = glm::cross(v1,v2);
			
			where 
			A = normal.x
			B = normal.y
			C = normal.z
			
			To get D, derive the plane equation by:
			glm::dvec3 D = glm::dot(positionsOfCorners[0], normal;

		When A, B, C and D is derived, combine the equation for the Plane and the Line
		to determine t (direction.xyz)
		
			double t = -( (A * startingPoint.x) + (B * startingPoint.y) + (C * startingPoint.z + D) )/
			( (A * direction.x) + (B * direction.y) +  (C * direction.z) )

		When t is derived, the intersectionPoint.xyz can be calculated!

	*/

	// Initializing the variables
	double A = 0.0, B = 0.0, C = 0.0, D = 0.0, t = 0.0;
	glm::dvec3 v1 = glm::dvec3(0.0, 0.0, 0.0), v2 = glm::dvec3(0.0, 0.0, 0.0);
	glm::dvec3 startingPoint = glm::dvec3(0.0, 0.0, 0.0);
	glm::dvec3 direction = glm::dvec3(0.0, 0.0, 0.0);

	// Get the startingPoint for the ray
	startingPoint = ray->getStartingPoint();
	
	// Get the direction for the ray
	direction = ray->getDirection();

	// Set the intersectionPoint to 
	glm::dvec3 intersectionPoint = glm::dvec3(0.0, 0.0, 0.0);

	// determine two vectors
	v1 = positionsOfCorners[1] - positionsOfCorners[0];
	v2 = positionsOfCorners[3] - positionsOfCorners[0];
	
	// determine the normal
	normal = glm::normalize(glm::cross(v1,v2));				// denna stämmer, det har vi fyrtrippelcheckat!
	
	// If the normal is orthogonal to the direction, then there are no intersections.	
	if(glm::dot(normal, direction) != 0.0)		// if not orthogonal
	{
		A = -normal.x;
		B = -normal.y;
		C = -normal.z;							// this is weird, we don't get it, but it works =/
		D = glm::dot(positionsOfCorners[0], normal);

		t = -( (A * startingPoint.x) + (B * startingPoint.y) + (C * startingPoint.z + D) ) /
			 ( (A * direction.x)     + (B * direction.y)     + (C * direction.z) );

		// std::cout << "t = " << t << std::endl;
		
		if(t <= 0)
		{
			return glm::dvec3(0.0, 0.0, 0.0);
		}

		// Determine intersectionPoint
		intersectionPoint.x = startingPoint.x + (t * direction.x);
		intersectionPoint.y = startingPoint.y + (t * direction.y);
		intersectionPoint.z = startingPoint.z + (t * direction.z);

		// Checking if intersection point is contained within rectangle bounds
		// Rectangle bounds (min(), max() needed due to orientation of rectangles)
		double xPosMin = std::min(positionsOfCorners[0].x, positionsOfCorners[2].x);
		double xPosMax = std::max(positionsOfCorners[0].x, positionsOfCorners[2].x);
		double yPosMin = std::min(positionsOfCorners[0].y, positionsOfCorners[2].y);
		double yPosMax = std::max(positionsOfCorners[0].y, positionsOfCorners[2].y);
		double zPosMin = std::min(positionsOfCorners[0].z, positionsOfCorners[2].z);
		double zPosMax = std::max(positionsOfCorners[0].z, positionsOfCorners[2].z);

		if( intersectionPoint.x >= xPosMin && intersectionPoint.x <= xPosMax &&
			intersectionPoint.y >= yPosMin && intersectionPoint.y <= yPosMax &&
			intersectionPoint.z >= zPosMin && intersectionPoint.z <= zPosMax )
		{
			return intersectionPoint;				// intersection point on the rectangle
		}
		else
		{
			return glm::dvec3(0.0, 0.0, 0.0);		// intersection point not on the rectangle
		}	
	}
	else
	{
		return glm::dvec3(0.0, 0.0, 0.0); 			// no intersection
	}
}


void calculateChildRays()
{
	//TODO: Write code
}			

/*
	Get functions
*/
glm::dvec3 Rectangle::getColor()
{
	return color;
}

glm::dvec3 Rectangle::getNormal()
{
	return normal;
}

/*
	Set functions
*/
void Rectangle::setColor(glm::dvec3 _color)
{
	color = _color;
}


		