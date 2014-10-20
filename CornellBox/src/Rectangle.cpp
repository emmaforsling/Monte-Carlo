#include "../include/Rectangle.h"
#include <iostream>
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
	// std::cout << "\n\n Determine rectangle intersection \n\n";

	//initialize the variables
	float A = 0.0, B = 0.0, C = 0.0, D = 0.0, t = 0.0;
	glm::vec3 v1 = glm::vec3(0.0, 0.0, 0.0), v2 = glm::vec3(0.0, 0.0, 0.0), normal = glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 startingPoint = glm::vec3(0.0, 0.0, 0.0);

	startingPoint = ray->getStartingPoint();
	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);
	
	direction = ray->getDirection();
	glm::vec3 intersectionPoint = glm::vec3(0.0, 0.0, 0.0);

	//determine two vectors
	v1 = positionsOfCorners[1] - positionsOfCorners[0];
	v2 = positionsOfCorners[3] - positionsOfCorners[0];

	// std::cout << "v1 = " << v1.x << ", " << v1.y << ", " << v1.z << std::endl;
	// std::cout << "v2 = " << v2.x << ", " << v2.y << ", " << v2.z << std::endl;
	
	normal = glm::normalize(glm::cross(v1,v2));				// denna stämmer, det har vi fyrtrippelcheckat!
	// std::cout << "normalen = " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
	
	//if normal is orthogonal to the direction, then there are no intersections.
	//if the dot product = 0	
	// std::cout << "Skalärprodukten = " << glm::dot(normal,direction) << "\n";
	if(glm::dot(normal, direction) != 0.0)		// if not orthogonal
	{
		A = -normal.x;
		B = -normal.y;
		C = -normal.z;							// this is weird, we don't get it, but it works =/
		D = glm::dot(positionsOfCorners[0], normal);
		
		// std::cout << "A = " << A << std::endl;
		// std::cout << "B = " << B << std::endl;
		// std::cout << "C = " << C << std::endl;
		// std::cout << "D = " << D << std::endl;

		// std::cout << "direction = " << direction.x << "," << direction.y << "," << direction.z << std::endl;

		t = -( (A * startingPoint.x) + (B * startingPoint.y) + (C * startingPoint.z + D) ) /
			 ( (A * direction.x)     + (B * direction.y)     + (C * direction.z) );
		// std::cout << "t = " << t << std::endl;
		
		//Determine intersectionPoint
		intersectionPoint.x = startingPoint.x + (t * direction.x);
		intersectionPoint.y = startingPoint.y + (t * direction.y);
		intersectionPoint.z = startingPoint.z + (t * direction.z);

		// std::cout << "x1 = " << startingPoint.x << std::endl;
		// std::cout << "y1 = " << startingPoint.y << std::endl;
		// std::cout << "z1 = " << startingPoint.z << std::endl;
		// std::cout << "a = " << direction.x << std::endl;
		// std::cout << "b = " << direction.y << std::endl;
		// std::cout << "c = " << direction.z << std::endl;

		// std::cout << "intersectionPoint = " << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << std::endl;
		// std::cout << "\n\n";

		// Checking if intersection point is contained within rectangle bounds
		// Rectangle bounds (min(), max() needed due to orientation of rectangles)
		float xPosMin = std::min(positionsOfCorners[0].x, positionsOfCorners[2].x);
		float xPosMax = std::max(positionsOfCorners[0].x, positionsOfCorners[2].x);
		float yPosMin = std::min(positionsOfCorners[0].y, positionsOfCorners[2].y);
		float yPosMax = std::max(positionsOfCorners[0].y, positionsOfCorners[2].y);
		float zPosMin = std::min(positionsOfCorners[0].z, positionsOfCorners[2].z);
		float zPosMax = std::max(positionsOfCorners[0].z, positionsOfCorners[2].z);
		if( intersectionPoint.x >= xPosMin && intersectionPoint.x <= xPosMax &&
			intersectionPoint.y >= yPosMin && intersectionPoint.y <= yPosMax &&
			intersectionPoint.z >= zPosMin && intersectionPoint.z <= zPosMax )
		{
			//std::cout << "(" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ") is contained within " << "[(" << xPosMin << ", " << yPosMin << ", " << zPosMin << "), (" << xPosMax << ", " << yPosMax << ", " << zPosMax << ")]" << std::endl;

			return intersectionPoint;				// intersection point on the rectangle
		}
		else
		{
			//std::cout << "(" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ") is not contained within "  << "[(" << xPosMin << ", " << yPosMin << ", " << zPosMin << "), (" << xPosMax << ", " << yPosMax << ", " << zPosMax << ")]" << std::endl;

			return glm::vec3(0.0, 0.0, 0.0);			// intersection point not on the rectangle
		}	
	}
	else
	{
		// std::cout << "Alltså är det ingen intersection\n\n";
		return glm::vec3(0.0, 0.0, 0.0); // no intersection
	}
}


void calculateChildRays()
{
	//TODO: Write code
}					