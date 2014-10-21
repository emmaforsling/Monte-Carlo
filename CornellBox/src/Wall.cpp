#include "../include/Wall.h"

/* 	
	Class Wall  
	
	private members:
	- glm::vec3 position;
	- float size;
*/

/* Default Constructor */
Wall::Wall()
: Object(glm::vec3(0.0, 0.0, 0.0))
{
	// position = glm::vec3(0.0, 0.0, 0.0);
	size = 0.0;

	walls[0] = nullptr;
	walls[1] = nullptr;
	walls[2] = nullptr;
	walls[3] = nullptr;
	walls[4] = nullptr;
}

Wall::Wall(glm::vec3 _position, float _size)
: Object(_position)
{
	// position = _position;
	size = _size;

	walls[0] = nullptr;
	walls[1] = nullptr;
	walls[2] = nullptr;
	walls[3] = nullptr;
	walls[4] = nullptr;

	initializeRectangles();
	
}

/* Destructor */
Wall::~Wall()
{
	//TODO: Write code 
}

/* Sets corners of the Rectangle to (0,0,0), (1,0,0), (0,1,0) etc. 
	and multiplies them by size (float) and adds the position 
	(glm::vec3) */
	
void Wall::initializeRectangles()
{
	/*
	   3 -- 2
	   |    |
	   0 -- 1
	*/
	glm::vec3 WHITE = glm::vec3(255,255,255);
	glm::vec3 RED = glm::vec3(255,0,0);
	glm::vec3 BLUE = glm::vec3(0,255,0);
	glm::vec3 GREEN = glm::vec3(0,0,255);

	walls[0] = new Rectangle();		//left
	walls[0]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	walls[0]->positionsOfCorners[1] = glm::vec3(0.0, 0.0, 0.0) + position;
	walls[0]->positionsOfCorners[2] = glm::vec3(0.0, size, 0.0) + position;
	walls[0]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;
	walls[0]->setColor(GREEN); 	//green

	walls[1] = new Rectangle();		//up
	walls[1]->positionsOfCorners[0] = glm::vec3(0.0, size, 0.0) + position;
	walls[1]->positionsOfCorners[1] = glm::vec3(size, size, 0.0) + position;
	walls[1]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	walls[1]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;
	walls[1]->setColor(WHITE); 	//white

	walls[2] = new Rectangle();		//right
	walls[2]->positionsOfCorners[0] = glm::vec3(size, 0.0, 0.0) + position;
	walls[2]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	walls[2]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	walls[2]->positionsOfCorners[3] = glm::vec3(size, size, 0.0) + position;
	walls[2]->setColor(RED); 	//red

	walls[3] = new Rectangle();		//down
	walls[3]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	walls[3]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	walls[3]->positionsOfCorners[2] = glm::vec3(size, 0.0, 0.0) + position;
	walls[3]->positionsOfCorners[3] = glm::vec3(0.0, 0.0, 0.0) + position;
	walls[3]->setColor(WHITE); 	//white

	walls[4] = new Rectangle();		//back
	walls[4]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[1] = glm::vec3(size, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[2] = glm::vec3(size, size, 0.0) + position;
	walls[4]->positionsOfCorners[3] = glm::vec3(0.0, size, 0.0) + position;
	walls[4]->setColor(WHITE); 	//white
	/*
	std::cout << "Nu har jag initialiserat alla sidor på rummet! Titta så fina:" << std::endl;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			std::cout << "Vägg " << j << std::endl;
			std::cout << walls[i]->positionsOfCorners[j].x << " " << walls[i]->positionsOfCorners[j].y << " " << walls[i]->positionsOfCorners[j].z << std::endl;
		}
	}
	*/
}

void Wall::calculateChildRays(glm::vec3 _intersectionPoint)
{
	
}

/* either one intersection or none (ray leaving) */				
glm::vec3 Wall::calculateIntersection(Ray* _ray)
{
	//TODO: Write code
	/*
		To calculate the intesection point for the Wall,
		first calculate the intersection point for a plane, 
		then see if the intersection point on the plane is within the wall

		The approach for determine the intersection point for a plane 
		is the same that is used in Rectangle. 
	*/
	std::cout << "==== studying wall (" << position.x << ", " << position.y << ", " << position.z << "), size = " << size << " ==== \n";
	glm::vec3 intersection;
	glm::vec3 finalIntersection = glm::vec3(0.0,0.0,0.0);
	int wall = 666;
	for(int i=0; i<5; i++)
	{
		std::cout << " - studying rectangle " << i << " - "; // << std::endl;
		intersection = walls[i]->calculateIntersection(_ray);

		//std::cout << "walls[" << i << "]->calculateIntersection(_ray) returned: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;

		//if intersection == glm::vec(0.0,0.0,0.0) then no intersection
		if( intersection == glm::vec3(0.0, 0.0, 0.0) )
		{
			std::cout << "				- NO INTERSECTIONS - " << std::endl;
		}
		if( intersection != glm::vec3(0.0, 0.0, 0.0) )
		{
			// first detected intersection
			if(finalIntersection == glm::vec3(0.0, 0.0, 0.0))
			{
				std::cout << "Detected first intersection (";
				finalIntersection = intersection;
				wall = i;
				std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;

			}
			// second detected intersection
			else
			{
				std::cout << "Detected second intersection (";
				std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;
				/* message */
				// std::cout << "walls[" << i << "].calculateIntersection(Ray* _ray) = " << intersection.x << ", " 
				// << intersection.y << ", " << intersection.z << std::endl;
				/* end message */

				// Ray inside object
				if(_ray->isInsideObject())
				{
					//std::cout << "Ray inside object. ";
					if( glm::length(intersection - _ray->getStartingPoint()) > glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						//std::cout << "Choosing new intersection point (farther from ray origin - exit point)." << std::endl;
						wall = i;
						finalIntersection = intersection;
					}
					else
					{
						//std::cout << "Discarding new intersection point (closer to ray origin - entry point)" << std::endl;
					}
				}
				// Ray outside object
				else
				{
					//std::cout << "Ray outside object. ";
					if( glm::length(intersection - _ray->getStartingPoint()) < glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						//std::cout << "Choosing new intersection point (closer to ray origin - entry point)." << std::endl;
						wall = i;
						finalIntersection = intersection;
					}
					else
					{
						//std::cout << "Discarding new intersection point (farther from ray origin - exit point)" << std::endl;
					}
				}
			}			
		}
	}
	if(wall!=666)
	{
		intersectedNormal = walls[wall]->getNormal();
		std::cout << "Normal at intersection: " << intersectedNormal.x << ", " << intersectedNormal.y << ", " << intersectedNormal.z << std::endl;
	}

	std::cout << "Returning final intersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ")" << std::endl;
	return finalIntersection;


	// return glm::vec3(0.0, 0.0, 0.0);
}

float Wall::getRefractiveIndex()				// this is weird...
{
	return 0.0;
}

glm::vec3 Wall::getIntersectedNormal()
{
	return intersectedNormal;
}

