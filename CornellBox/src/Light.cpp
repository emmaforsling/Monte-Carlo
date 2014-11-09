#include "../include/Light.h"
#include <iostream>

/* Class Light
	private:
	- Rectangle* sumthin;
	- double radiance;
	- glm::dvec3 position;
	- double size;
*/

/* 
	Emtpy constructor
*/
Light::Light()
{
	lightSource = new Rectangle();
	radiance = 0.0;
	position = glm::dvec3(0.0, 0.0, 0.0);
	size = 0;
}

/*
	Constructor
*/
Light::Light(glm::dvec3 _position, double _size, double _radiance)
{
	radiance = _radiance;
	//position = _position;
	size = _size;
	
	/* 
		For the new rectangle, the y coord, should be max, and thereby size 
		The x coord and z coord should then be divided by 6 to become the lightsource
	*/
	lightSource = new Rectangle();		// up
	// lightSource->positionsOfCorners[0] = glm::dvec3(size/2.0 - size/6.0, size, size/2.0 - size/6.0);
	// lightSource->positionsOfCorners[1] = glm::dvec3(size/2.0 + size/6.0, size, size/2.0 - size/6.0);
	// lightSource->positionsOfCorners[2] = glm::dvec3(size/2.0 + size/6.0, size, size/2.0 + size/6.0);
	// lightSource->positionsOfCorners[3] = glm::dvec3(size/2.0 - size/6.0, size, size/2.0 + size/6.0);

	lightSource->positionsOfCorners[0] = glm::dvec3(2.0, 4.5, 2.0);
	lightSource->positionsOfCorners[1] = glm::dvec3(3.0, 4.5, 2.0);
	lightSource->positionsOfCorners[2] = glm::dvec3(3.0, 4.5, 3.0);
	lightSource->positionsOfCorners[3] = glm::dvec3(2.0, 4.5, 3.0);

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
glm::dvec3 Light::getPosition()
{
	return position;
}

glm::dvec3 Light::getRandomPosition()
{
	//srand(time(NULL));					// Only Chronos is the master of time!
	double randomPointX = lightSource->positionsOfCorners[0].x + ( (lightSource->positionsOfCorners[1].x - lightSource->positionsOfCorners[0].x) * static_cast <double>(rand()) ) / static_cast<double>(RAND_MAX);
	double randomPointZ = lightSource->positionsOfCorners[0].z + ( (lightSource->positionsOfCorners[3].z - lightSource->positionsOfCorners[0].z) * static_cast <double>(rand()) ) / static_cast<double>(RAND_MAX);

	// The random point on the area light source
	glm::dvec3 randomPoint = glm::dvec3(randomPointX, lightSource->positionsOfCorners[0].y, randomPointZ);
	//std:: cout << "returning random point on light source: (" << randomPoint.x << ", " << randomPoint.y << ", " << randomPoint.z << ")" << std::endl;
	return randomPoint;
}

double Light::getRadiance()
{
	return radiance;
}

bool Light::isOnLightSource(glm::dvec3 _point)
{
	glm::dvec3 corner0 = lightSource->positionsOfCorners[0];
	glm::dvec3 corner1 = lightSource->positionsOfCorners[1];
	glm::dvec3 corner2 = lightSource->positionsOfCorners[2];
	glm::dvec3 corner3 = lightSource->positionsOfCorners[3];
	
	if(_point.y >= corner0.y)
	{
		if( _point.x >= corner0.x && _point.x <= corner1.x && 
			_point.z >= corner0.z && _point.z <= corner3.z)
		{
			return true;
		}
	}
	return false;
}
