#include "../include/Camera.h"
#include <iostream>
/* 	
	Class Camera  
	
	private members:
	- glm::vec3 position;
	- glm::vec3 direction;
	- float viewPlaneDistance;
	- int resolutionX;
	- int resolutionY;
	- int raysPerPixel;
	- Pixel* pixels;
*/

/* Default Constructor */
Camera::Camera()
{	
	position = glm::vec3(0.0,0.0,0.0);
	direction = glm::vec3(0.0,0.0,0.0);
	viewPlaneDistance = 0.0;
	raysPerPixel = 0;
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		pixels[i] = nullptr;
	}
}

Camera::Camera(Wall* _room, float _eyeDistance, int _raysPerPixel)
{	
	direction = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 oppositeWallCenterPosition = (_room->walls[4]->positionsOfCorners[0] + _room->walls[4]->positionsOfCorners[2])/2.0f;
	
	position = oppositeWallCenterPosition + direction * _eyeDistance;
	
	viewPlaneSizeX = 1;
	viewPlaneSizeY = 1;

	viewPlaneDistance = _eyeDistance * std::max(viewPlaneSizeX, viewPlaneSizeY) / _room->size;

	raysPerPixel = _raysPerPixel;
		for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		pixels[i] = new Pixel(raysPerPixel);
	}
	
	std::cout << "Camera position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
	std::cout << "Viewplane distance: " << viewPlaneDistance << std::endl;
}

/* Destructor */
Camera::~Camera()
{
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		delete pixels[i];
	}
	//TODO: Write code 
}

/* Loops over all pixels and computes their values. */
void Camera::renderImage()
{
	// TODO: Write code
	// "pixels[i]->shootRays()"
	// "pixels[i]->calculate"
}

/* Converts radiometric values into photometric ones. */
void Camera::mappingFunction()
{
	//TODO: Write code
}

/* Alternatively displayImage() */						 
void Camera::saveImage()
{
	//TODO: Write code
}
