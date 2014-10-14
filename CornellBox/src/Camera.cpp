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
	resolutionX = 0;
	resolutionY = 0;
	raysPerPixel = 0;
	pixels = nullptr; 
}

Camera::Camera(glm::vec3 _position, glm::vec3 _direction, float _viewPlaneDistance, int _resolutionX, int _resolutionY, int _raysPerPixel)
{	
	position = _position - _direction * _viewPlaneDistance;
	direction = _direction;
	viewPlaneDistance = _viewPlaneDistance;
	resolutionX = _resolutionX;
	resolutionY = _resolutionY;
	raysPerPixel = _raysPerPixel;
	pixels = new Pixel[resolutionX * resolutionY]();
	
	std::cout << "Camera position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
}

/* Destructor */
Camera::~Camera()
{
	delete[] pixels;
	//TODO: Write code 
}

/* Loops over all pixels and computes their values. */
void Camera::renderImage()
{
	//TODO: Write code
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
