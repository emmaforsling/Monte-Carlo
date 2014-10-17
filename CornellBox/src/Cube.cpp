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
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	position = glm::vec3(0.0, 0.0, 0.0);
	size = 0.0;
	transparency = 0.0;
	refractiveIndex = 0.0;
}

Cube::Cube(glm::vec3 _position, float _size, float _transparency, float _refractiveIndex)
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	position = _position;
	size = _size;
	transparency = _transparency;
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
	


	//std::cout << "Nu har jag initialiserat alla sidor på kuben! Titta så fina:" << std::endl;
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<4; j++)
		{
			std::cout << sides[i]->positionsOfCorners[j].x << " " << sides[i]->positionsOfCorners[j].y << " " << sides[i]->positionsOfCorners[j].z << std::endl;
		}
	} 
}				

void Cube::calculateChildRays()
{
	//TODO: Write code
}

glm::vec3 Cube::calculateIntersection(Ray* _ray)
{
	return glm::vec3(0,0,0);
}