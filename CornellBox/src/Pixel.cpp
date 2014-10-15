#include "../include/Pixel.h"

/* 	
	Class Pixel  
	
	private members:
	- Ray* rays;				// vec4 for alpha?
	- glm::vec3 colorOfPixel;
*/

/* Default Constructor */
Pixel::Pixel()
{
	rays = nullptr;
	colorOfPixel = glm::vec3(0.0,0.0,0.0);		//black to begin with 
}

Pixel::Pixel(int raysPerPixel)
{
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
	// TODO: Write code
	// 1. Generate Camera::raysPerPixel random directions, and launch a new Ray into these.
	// 2. Append the new rays to Pixel::rays
}
