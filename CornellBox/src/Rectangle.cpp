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


glm::vec3 Rectangle::calculateIntersection()
{
	//TODO: Write code
	return glm::vec3(0.0,0.0,0.0);
}


void calculateChildRays()
{
	//TODO: Write code
}					