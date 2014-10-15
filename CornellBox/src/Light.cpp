#include "../include/Light.h"
#include <iostream>
/* Class Light
	private:
	- Rectangle* sumthin;
	- float radiance;
	- glm::vec3 position;
	- float size;
*/

/* Default constructor */
Light::Light()
{
	sumthin = new Rectangle();
	radiance = 0.0;
	position = glm::vec3(0.0,0.0,0.0);
	size = 0;
}

/*
	Constructor
	To construct a light source,
	the position in the room should be passed to the constructor,
	the which is passed to the constructor is the size of the wall, 
	and in this constructor it should be 1/6 of the roof)

*/
Light::Light(glm::vec3 _position, float _size, float _radiance)
{
	radiance = _radiance;
	position = _position;
	size = _size;
	
	/* 
		For the new rectangle, the y coord, should be max, and thereby size 
		The x coord and z coord should then be divided by 6 to become the lightsource
	*/
	sumthin = new Rectangle();		//up
	sumthin->positionsOfCorners[0] = glm::vec3(0.0, size, 0.0) + position;
	sumthin->positionsOfCorners[1] = glm::vec3(size/6.0, size, 0.0) + position;
	sumthin->positionsOfCorners[2] = glm::vec3(size/6.0, size, size/6.0) + position;
	sumthin->positionsOfCorners[3] = glm::vec3(0.0, size, size/6.0) + position;

	std::cout << "Nu har jag initialiserat lampan i taket. Kolla på dessa koordinater:" << std::endl;
	for(int j=0; j<4; j++)
	{
		std::cout << sumthin->positionsOfCorners[j].x << " " << sumthin->positionsOfCorners[j].y << " " << sumthin->positionsOfCorners[j].z << std::endl;
	}
}


/* Destructor */
Light::~Light()
{
	delete sumthin;	
}

glm::vec3 Light::getRandomPosition()
{
	//TODO: Write code
	return glm::vec3(0,0,0);
}
