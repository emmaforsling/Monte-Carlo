#include "../include/Cube.h"
#include <iostream>

/* 	
	Class Cube  
	
	private members:
	- Rectangle* sides[6];
	- glm::vec3 position;
	- float size;
	- float transparency;
	- float refractiveIndex;
*/

/* Default Constructor */
Cube::Cube()
: Object(glm::vec3(0.0, 0.0, 0.0))
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	// position = glm::vec3(0.0, 0.0, 0.0);
	size = 0.0;
	transparent = false;
	refractiveIndex = 0.0;
}

Cube::Cube(glm::vec3 _position, float _size, bool _transparent, float _refractiveIndex)
: Object(_position)
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	// position = _position;
	size = _size;
	transparent = _transparent;
	refractiveIndex = _refractiveIndex;

	initializeRectangles();
}

/* Destructor */
Cube::~Cube()
{
	
	//TODO: Write code 
}

/*
	Sets corners of rectangles to (0,0,0), (1,0,0), (0,1,0) etc.
	and multiplies them by size (float) and adds the position (glm::vec3))
*/
void Cube::initializeRectangles()
{
	/*
	   3 -- 2
	   |    |
	   0 -- 1
	*/
	sides[0] = new Rectangle();		//left
	sides[0]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	sides[0]->positionsOfCorners[1] = glm::vec3(0.0, 0.0, 0.0) + position;
	sides[0]->positionsOfCorners[2] = glm::vec3(0.0, size, 0.0) + position;
	sides[0]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;

	sides[1] = new Rectangle();		//up
	sides[1]->positionsOfCorners[0] = glm::vec3(0.0, size, 0.0) + position;
	sides[1]->positionsOfCorners[1] = glm::vec3(size, size, 0.0) + position;
	sides[1]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	sides[1]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;

	sides[2] = new Rectangle();		//right
	sides[2]->positionsOfCorners[0] = glm::vec3(size, 0.0, 0.0) + position;
	sides[2]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	sides[2]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	sides[2]->positionsOfCorners[3] = glm::vec3(size, size, 0.0) + position;
	
	sides[3] = new Rectangle();		//down
	sides[3]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	sides[3]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	sides[3]->positionsOfCorners[2] = glm::vec3(size, 0.0, 0.0) + position;
	sides[3]->positionsOfCorners[3] = glm::vec3(0.0, 0.0, 0.0) + position;

	sides[4] = new Rectangle();		//back
	sides[4]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, 0.0) + position;
	sides[4]->positionsOfCorners[1] = glm::vec3(size, 0.0, 0.0) + position;
	sides[4]->positionsOfCorners[2] = glm::vec3(size, size, 0.0) + position;
	sides[4]->positionsOfCorners[3] = glm::vec3(0.0, size, 0.0) + position;

	sides[5] = new Rectangle();		//front
	sides[5]->positionsOfCorners[0] = glm::vec3(size, 0.0, size) + position;
	sides[5]->positionsOfCorners[1] = glm::vec3(0.0, 0.0, size) + position;
	sides[5]->positionsOfCorners[2] = glm::vec3(0.0, size, size) + position;
	sides[5]->positionsOfCorners[3] = glm::vec3(size, size, size) + position;
	
	/*
	std::cout << "Nu har jag initialiserat alla sidor på kuben! Titta så fina:" << std::endl;
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<4; j++)
		{
			std::cout << sides[i]->positionsOfCorners[j].x << " " << sides[i]->positionsOfCorners[j].y << " " << sides[i]->positionsOfCorners[j].z << std::endl;
		}
	}
	*/
}

glm::vec3 Cube::calculateIntersection(Ray* _ray) 
{
	glm::vec3 intersection;
	glm::vec3 finalIntersection = glm::vec3(0.0,0.0,0.0);

	// Loopa igenom de 6 rektanglarna
	// Kolla ifall de intersectar med kuben
	// Ta reda på insida/utsida

	for(int i=0; i<6; i++)
	{
		intersection = sides[i]->calculateIntersection(_ray);
		//if intersection == glm::vec(0.0,0.0,0.0) then no intersection

		if(intersection != glm::vec3(0.0, 0.0, 0.0))
		{
			// first detected intersection
			if(finalIntersection == glm::vec3(0.0, 0.0, 0.0))
			{
				finalIntersection = intersection;
			}
			// second detected intersection
			else
			{
				/* message */
				std::cout << "sides[" << i << "].calculateIntersection(Ray* _ray) = " << intersection.x << ", " 
				<< intersection.y << ", " << intersection.z << std::endl;
				/* end message */

				// Ray inside object
				if(_ray->isInsideObject())
				{
					if( glm::length(intersection - _ray->getStartingPoint()) > glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						finalIntersection = intersection;
					}
				}
				// Ray outside object
				else
				{
					if( glm::length(intersection - _ray->getStartingPoint()) < glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						finalIntersection = intersection;
					}
				}
			}			
		}
	}

	//Fulkod
	float backBottomLeftX = sides[0]->positionsOfCorners[1].x;
	float backBottomLeftY = sides[0]->positionsOfCorners[1].y;
	float backBottomLeftZ = sides[0]->positionsOfCorners[1].z;

	float frontCeilRightX = sides[3]->positionsOfCorners[2].x;
	float frontCeilRightY = sides[3]->positionsOfCorners[2].y;
	float frontCeilRightZ = sides[3]->positionsOfCorners[2].z;


	if( (finalIntersection.x >= backBottomLeftX && finalIntersection.y >= backBottomLeftY && finalIntersection.z >= backBottomLeftZ) && 
		(finalIntersection.x <= frontCeilRightX && finalIntersection.y <= frontCeilRightY && finalIntersection.z <= frontCeilRightZ) )
	{
		// then it is inside
		return finalIntersection;
	}
	return glm::vec3(0.0,0.0,0.0);
		
}				

void Cube::calculateChildRays(glm::vec3 _intersectionPoint)
{
	//TODO: Write code
}
