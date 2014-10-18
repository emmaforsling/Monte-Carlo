#include "../include/Pixel.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

/* 	
	Class Pixel  
	
	private members:
	- Ray* rays;				// vec4 for alpha?
	- glm::vec3 colorOfPixel;
*/

/* Default Constructor */
Pixel::Pixel()
{
	// std::cout << "Pixel::tom konstruktor" << std::endl;
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
	position = glm::vec3(0.0, 0.0, 0.0);
}

Pixel::Pixel(int _raysPerPixel)
{
	//std::cout << "Pixel::full konstruktor" << std::endl;
	//rays = new Ray[_raysPerPixel]();
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
}

/* Destructor */
Pixel::~Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		delete rays[i];
	}
	//TODO: Write code
}

/* Should also track the rays within the scene (tree structure?) */
void Pixel::shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects)
{
	// std::cout << "entering pixel! " << std::endl << std::endl;
	float randomPointX;
	float randomPointY;
	glm::vec3 randomPoint;
	glm::vec3 direction;
	glm::vec3 color;
	srand(time(NULL));
	for(int i = 0; i < _raysPerPixel; i++)
	{
		std::cout << "\n======= SHOOTING RAY =======\n" << std::endl;
		// std::cout << "Slumpar mellan " << _pixelPosition.x << " och " << _pixelPosition.x + _pixelSize << " i x" << std::endl;
		// std::cout << "Slumpar mellan " << _pixelPosition.y << " och " << _pixelPosition.y + _pixelSize << " i y" << std::endl;
		randomPointX = _pixelPosition.x + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPointY = _pixelPosition.y + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		//randomPointY = _pixelPosition.y + static_cast <float>(rand()) / (static_cast<float>(RAND_MAX / (_pixelPosition.y + _pixelSize - _pixelPosition.y)));
		
		// std::cout << "Nu har jag slumpat ut two values for dig: " << randomPointX << ", " << randomPointY << std::endl;
		
		// The random point on the pixel
		randomPoint = glm::vec3(randomPointX, randomPointY, _pixelPosition.z);

		// Determine the normalized direction from eye to generated position
		direction = (randomPoint - _cameraPosition) / glm::length(randomPoint - _cameraPosition);

		/* === Debugging === */
		//std::cout << "Kameraposition: " << _cameraPosition.x << ", " << _cameraPosition.y << ", " << _cameraPosition.z << ")" << std::endl;
		//std::cout << "ger riktning: (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;

		// 
		rays[i] = new Ray(randomPoint, direction, 1.0/_raysPerPixel, colorOfPixel, false);
		glm::vec3 intersectionPoints[4];
		glm::vec3 finalIntersection = glm::vec3(0.0, 0.0, 0.0);
		int closestIntersectedObjectIndex;
		for(int j = 0; j < 2; j++)								// loop through objects
		{
			// _objects[j]->calculateChildRays(_objects[j]->calculateIntersection(rays[i]));
			
			intersectionPoints[j] = _objects[j]->calculateIntersection(rays[i]);
			if(glm::length(finalIntersection) == 0)				// first encountered object
			{
				std::cout << "First encountered object" << std::endl;
				finalIntersection = intersectionPoints[j];
				closestIntersectedObjectIndex = j;
			}
			else												// not the first object
			{
				std::cout << "Not first encountered object" << std::endl;
				if( glm::length(intersectionPoints[j] - rays[i]->getStartingPoint()) < glm::length(finalIntersection - rays[i]->getStartingPoint()) )
				{
					std::cout << "Intersection closer to ray origin!" << std::endl;
					finalIntersection = intersectionPoints[j];	// object closest to ray origin
					closestIntersectedObjectIndex = j;
				}
				else
				{
					std::cout << "Intersection farther from ray origin!" << std::endl;
				}
			}
		}
		std::cout << "Calculating child rays for intersection point " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << std::endl;
		_objects[closestIntersectedObjectIndex]->calculateChildRays(finalIntersection);
	}
	// TODO: Write code
	// 1. Generate Camera::raysPerPixel random directions, and launch a new Ray into these.
	// 2. Append the new rays to Pixel::rays
	// 3. colorOfPixel += rays[i]->calculateColor()
}
