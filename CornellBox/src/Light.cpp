#include "../include/Light.h"
#include <iostream>

/* Class Light
	private:
	- Rectangle* sumthin;
	- float radiance;
	- glm::vec3 position;
	- float size;
*/

/* 
	Emtpy constructor
*/
Light::Light()
{
	lightSource = new Rectangle();
	radiance = 0.0;
	position = glm::vec3(0.0, 0.0, 0.0);
	size = 0;
}

/*
	Constructor
*/
Light::Light(glm::vec3 _position, float _size, float _radiance)
{
	radiance = _radiance;
	//position = _position;
	size = _size;
	
	/* 
		For the new rectangle, the y coord, should be max, and thereby size 
		The x coord and z coord should then be divided by 6 to become the lightsource
	*/
	lightSource = new Rectangle();		// up
	// lightSource->positionsOfCorners[0] = glm::vec3(size/2.0 - size/6.0, size, size/2.0 - size/6.0);
	// lightSource->positionsOfCorners[1] = glm::vec3(size/2.0 + size/6.0, size, size/2.0 - size/6.0);
	// lightSource->positionsOfCorners[2] = glm::vec3(size/2.0 + size/6.0, size, size/2.0 + size/6.0);
	// lightSource->positionsOfCorners[3] = glm::vec3(size/2.0 - size/6.0, size, size/2.0 + size/6.0);

	lightSource->positionsOfCorners[0] = glm::vec3(2.0, 4.9, 2.0);
	lightSource->positionsOfCorners[1] = glm::vec3(3.0, 4.9, 2.0);
	lightSource->positionsOfCorners[2] = glm::vec3(3.0, 4.9, 3.0);
	lightSource->positionsOfCorners[3] = glm::vec3(2.0, 4.9, 3.0);

	position = lightSource->positionsOfCorners[0];

	/*
	// // std::cout << "Nu har jag initialiserat lampan i taket. Kolla på dessa koordinater:" << std::endl;
	for(int j=0; j<4; j++)
	{
		// // std::cout << lightSource->positionsOfCorners[j].x << " " << lightSource->positionsOfCorners[j].y << " " << lightSource->positionsOfCorners[j].z << std::endl;
	}
	*/
}


/* 
	Destructor 
*/
Light::~Light()
{
	delete lightSource;	
}

/*
	Get functions
*/
glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec3 Light::getRandomPosition()
{
	//srand(time(NULL));					// Only Chronos is the master of time!
	float randomPointX = lightSource->positionsOfCorners[0].x + ((size/6.0) * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
	float randomPointZ = lightSource->positionsOfCorners[0].z + ((size/6.0) * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);

	// The random point on the area light source
	glm::vec3 randomPoint = glm::vec3(randomPointX, lightSource->positionsOfCorners[0].y, randomPointZ);
	//std:: cout << "returning random point on light source: (" << randomPoint.x << ", " << randomPoint.y << ", " << randomPoint.z << ")" << std::endl;
	return randomPoint;
}


