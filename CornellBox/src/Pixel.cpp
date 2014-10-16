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
	std::cout << "Pixel::tom konstruktor" << std::endl;
	rays = nullptr;
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
	position = glm::vec3(0.0, 0.0, 0.0);
}

Pixel::Pixel(int _raysPerPixel)
{
	//std::cout << "Pixel::full konstruktor" << std::endl;
	//rays = new Ray[_raysPerPixel]();
	rays = nullptr;
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
}

/* Destructor */
Pixel::~Pixel()
{
	delete[] rays;
	//TODO: Write code
}

/* Should also track the rays within the scene (tree structure?) */
void Pixel::shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize)
{
	std::cout << "entering pixel! " << std::endl << std::endl;
	float randomPointX;
	float randomPointY;
	glm::vec3 randomPoint;
	glm::vec3 direction;
	glm::vec3 color;
	srand(time(NULL));
	for(int i = 0; i < _raysPerPixel; i++)
	{
		std::cout << "shooting ray! " << std::endl;
		std::cout << "Slumpar mellan " << _pixelPosition.x << " och " << _pixelPosition.x + _pixelSize << " i x" << std::endl;
		std::cout << "Slumpar mellan " << _pixelPosition.y << " och " << _pixelPosition.y + _pixelSize << " i y" << std::endl;
		randomPointX = _pixelPosition.x + static_cast <float>(rand()) / (static_cast<float>(RAND_MAX / (_pixelPosition.x + _pixelSize - _pixelPosition.x)));
		randomPointY = _pixelPosition.y + static_cast <float>(rand()) / (static_cast<float>(RAND_MAX / (_pixelPosition.y + _pixelSize - _pixelPosition.y)));
		
		std::cout << "Nu har jag slumpat ut två values for dig: " << randomPointX << ", " << randomPointY << std::endl;
		/*
		randomPoint = glm::vec3(randomPointX, randomPointY, _pixelPosition.z);
		direction = (randomPoint - _cameraPosition);

		glm::vec3 _color = glm::vec3(0.0, 0.0, 0.0);
		rays[i] = new Ray(randomPoint, direction, 1.0/_raysPerPixel, _color, false);*/
	}
	// TODO: Write code
	// 1. Generate Camera::raysPerPixel random directions, and launch a new Ray into these.
	// 2. Append the new rays to Pixel::rays
	// 3. colorOfPixel += rays[i]->calculateColor()
}
