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

/* 
	Empty constructor 
*/
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

/*
	Constructor
*/
Camera::Camera(Wall* _room, float _eyeDistance, int _raysPerPixel)
{	
	//DO not change direction //
	direction = glm::vec3(0.0, 0.0, -1.0);
	
	glm::vec3 oppositeWallCenterPosition = (_room->walls[4]->positionsOfCorners[0] + _room->walls[4]->positionsOfCorners[2])/2.0f;
	position = /*glm::vec3(2.5, 2.5, 15); //*/oppositeWallCenterPosition - direction * _eyeDistance;
	
	/*
		z' - avståndet till scenen 		(eyedistance)
		x' - storlek på scenen i x  	(room->size) 
		y' - storlek på scenen i y 		(room->size)

		x - storlek på viewplane i x 	(viewPlaneSizeX)
		y - storlek på viewplane i y 	(viewPlaneSizeY)
		z - avståndet till viewplane 	(viewPlaneDistance) --- denna är sökt

		x'/x = y'/y = z'/z
	*/


	viewPlaneDistance = /*2.0; //*/(_eyeDistance - _room->size) * std::max(viewPlaneSizeX, viewPlaneSizeY) / _room->size;
	raysPerPixel = _raysPerPixel;

	// Creating a one dimensional array, containing all pixels for the scene  
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		pixels[i] = new Pixel(raysPerPixel);
	}
	
	// // // std::cout << "Camera position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
	// // // std::cout << "Viewplane distance: " << viewPlaneDistance << std::endl;
}

/* Destructor */
Camera::~Camera()
{
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		delete pixels[i];
	}
}

/* Loops over all pixels and computes their values. */
void Camera::renderImage(Object** _objects, Light* _light)
{
	/*
		To render image:
		* define the viewplane
		* determine the pixel size
		* the total amount of pixels
	*/

	// Defining the viewplane
	float viewPlanePosZ = position.z - viewPlaneDistance;
	glm::vec3 viewPlaneCorner0 = glm::vec3(position.x - viewPlaneSizeX/2.0, position.y - viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::vec3 viewPlaneCorner1 = glm::vec3(position.x + viewPlaneSizeX/2.0, position.y - viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::vec3 viewPlaneCorner2 = glm::vec3(position.x + viewPlaneSizeX/2.0, position.y + viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::vec3 viewPlaneCorner3 = glm::vec3(position.x - viewPlaneSizeX/2.0, position.y + viewPlaneSizeY/2.0, viewPlanePosZ);
	
	// Determining the pixelsize
	float pixelSize = viewPlaneSizeX / (float)resolutionX;			// or viewPlaneSizeY / resolutionY
	
	// Initializing variables
	glm::vec3 pixelPosition;
	int numberOfPixels = resolutionX * resolutionY;
	
	//#pragma omp parallel for
	for(int i = 0; i < numberOfPixels; i++)					//Loop through all the pixels
	{
		// To determine the pixelPosition
		//   pixelPosition.x: i % resolutionX) / (float)resolutionX + viewPlaneCorner0.x
		//   pixelPosition.y: viewPlaneCorner3.y - (i/(int)resolutionY) / (float)resolutionY 
		//   pixelPosition.z: viewPlanePosZ
		pixelPosition = glm::vec3((i % resolutionX) / (float)resolutionX + viewPlaneCorner0.x, viewPlaneCorner3.y - (i/(int)resolutionY) / (float)resolutionY , viewPlanePosZ);
		
		// Take the current pixel, call the function shootRays 
		//  that shoots, the given amount of rays, though that pixel
		pixels[i]->shootRays(position, raysPerPixel, pixelPosition, pixelSize, _objects, _light);

		/* 
			Progress bar 
		*/
		if(i % 100 == 0)
		{
			std::cout << "Progress: " << (i/(double)numberOfPixels) * 100 << "%" << std::endl;
		}
	}
	std::cout << "Progress: 100%" << std::endl;
	// // std::cout << "color of pixels:" << std::endl;
	// for(int i = 0; i < numberOfPixels; i++)
	// {
	// 	// // std::cout << "(" << pixels[i]->getColorOfPixel().x << ", " << pixels[i]->getColorOfPixel().y << ", " << pixels[i]->getColorOfPixel().z << ")" << std::endl;
	// }
	// "pixels[i]->calculateIntersections" 
}

/* Converts radiometric values into photometric ones. */
void Camera::mappingFunction()
{
	//TODO: Write code
}


float Camera::clamp(float _x)
{
	return _x<0 ? 0 : _x>1 ? 1 : _x;
}

int Camera::toInt(float _x)
{
	return int(pow(clamp(_x),1/2.2)*255+.5);
}

/* Alternatively displayImage() */						 
void Camera::saveImage()
{
	/* This code, for saving the image into ppm-format, is taken from http://www.kevinbeason.com/smallpt/ */ 
	glm::vec3 colorOfPixel = glm::vec3(0.0, 0.0, 0.0);
	FILE* _file = fopen("image.ppm","w");
	fprintf(_file, "P3\n%d %d\n%d\n", resolutionX, resolutionY, 255);
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		colorOfPixel = pixels[i]->getColorOfPixel();
		// // std::cout << "COLOR_OF_PIXEL " << colorOfPixel.x << ", " <<colorOfPixel.y << ", "<< colorOfPixel.z << std::endl;
 		fprintf(_file,"%d %d %d\n", toInt(colorOfPixel.x), toInt(colorOfPixel.y), toInt(colorOfPixel.z));
	}
}
