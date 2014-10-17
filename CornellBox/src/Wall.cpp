#include "../include/Wall.h"

/* 	
	Class Wall  
	
	private members:
	- glm::vec3 position;
	- float size;
*/

/* Default Constructor */
Wall::Wall()
{
	position = glm::vec3(0.0, 0.0, 0.0);
	size = 0.0;

	walls[0] = nullptr;
	walls[1] = nullptr;
	walls[2] = nullptr;
	walls[3] = nullptr;
	walls[4] = nullptr;
}

Wall::Wall(glm::vec3 _position, float _size)
{
	position = _position;
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
	walls[0] = new Rectangle();		//left
	walls[0]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	walls[0]->positionsOfCorners[1] = glm::vec3(0.0, 0.0, 0.0) + position;
	walls[0]->positionsOfCorners[2] = glm::vec3(0.0, size, 0.0) + position;
	walls[0]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;

	walls[1] = new Rectangle();		//up
	walls[1]->positionsOfCorners[0] = glm::vec3(0.0, size, 0.0) + position;
	walls[1]->positionsOfCorners[1] = glm::vec3(size, size, 0.0) + position;
	walls[1]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	walls[1]->positionsOfCorners[3] = glm::vec3(0.0, size, size) + position;

	walls[2] = new Rectangle();		//right
	walls[2]->positionsOfCorners[0] = glm::vec3(size, 0.0, 0.0) + position;
	walls[2]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	walls[2]->positionsOfCorners[2] = glm::vec3(size, size, size) + position;
	walls[2]->positionsOfCorners[3] = glm::vec3(size, size, 0.0) + position;
	
	walls[3] = new Rectangle();		//down
	walls[3]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, size) + position;
	walls[3]->positionsOfCorners[1] = glm::vec3(size, 0.0, size) + position;
	walls[3]->positionsOfCorners[2] = glm::vec3(size, 0.0, 0.0) + position;
	walls[3]->positionsOfCorners[3] = glm::vec3(0.0, 0.0, 0.0) + position;

	walls[4] = new Rectangle();		//back
	walls[4]->positionsOfCorners[0] = glm::vec3(0.0, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[1] = glm::vec3(size, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[2] = glm::vec3(size, size, 0.0) + position;
	walls[4]->positionsOfCorners[3] = glm::vec3(0.0, size, 0.0) + position;

	std::cout << "Nu har jag initialiserat alla sidor på rummet! Titta så fina:" << std::endl;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			std::cout << "Vägg " << j << std::endl;
			std::cout << walls[i]->positionsOfCorners[j].x << " " << walls[i]->positionsOfCorners[j].y << " " << walls[i]->positionsOfCorners[j].z << std::endl;
		}
	} 
}

/* either one intersection or none (ray leaving) */				
glm::vec3 Wall::calculateIntersection(Ray* _ray)
{
	//TODO: Write code
	return glm::vec3(0,0,0);
}