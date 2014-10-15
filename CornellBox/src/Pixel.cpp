#include "../include/Pixel.h"
#include <iostream>

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
	colorOfPixel = glm::vec3(0.0,0.0,0.0);		//black to begin with 
}

Pixel::Pixel(int raysPerPixel)
{
	//std::cout << "Pixel::full konstruktor" << std::endl;
	rays = new Ray[raysPerPixel]();
	colorOfPixel = glm::vec3(0.0,0.0,0.0);		//black to begin with 
}

/* Destructor */
Pixel::~Pixel()
{
	delete[] rays;
	//TODO: Write code
}

/* Should also track the rays within the scene (tree structure?) */
void Pixel::shootRays()
{
	std::cout << "shooting ray! " << std::endl;
	/*for(int i = 0; i <rays.size(); i++)
	{

	}*/
	// TODO: Write code
	// 1. Generate Camera::raysPerPixel random directions, and launch a new Ray into these.
	// 2. Append the new rays to Pixel::rays
	// 3. colorOfPixel += rays[i]->calculateColor()
}
