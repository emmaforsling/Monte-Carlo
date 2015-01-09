#include "../include/Camera.h"
#include <iostream>

/* 	
	Class Camera  
	
	private members:
	- glm::dvec3 position;
	- glm::dvec3 direction;
	- double viewPlaneDistance;
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
	position = glm::dvec3(0.0,0.0,0.0);
	direction = glm::dvec3(0.0,0.0,0.0);
	viewPlaneDistance = 0.0;
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		pixels[i] = nullptr;
	}
}

/*
	Constructor
*/
Camera::Camera(Wall* _room, double _eyeDistance)
{	
	//DO not change direction //
	direction = glm::dvec3(0.0, 0.0, -1.0);
	
	glm::dvec3 oppositeWallCenterPosition = (_room->walls[4]->positionsOfCorners[0] + _room->walls[4]->positionsOfCorners[2])/2.0;
	position = /*glm::dvec3(2.5, 2.5, 15); //*/oppositeWallCenterPosition - direction * _eyeDistance;
	
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

	// Creating a one dimensional array, containing all pixels for the scene  
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		pixels[i] = new Pixel(Pixel::raysPerPixel);
	}
	
	// // // std::cout << "Camera position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
	// // // std::cout << "Viewplane distance: " << viewPlaneDistance << std::endl;
}

/* 
	Destructor
*/
Camera::~Camera()
{
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		delete pixels[i];
	}
}

/*
	Image functions
*/	
void Camera::renderImage(Object** _objects, Light* _light)
{
	/*
		Loops over all pixels and computes their values.

		To render image:
		* define the viewplane
		* determine the pixel size
		* the total amount of pixels
	*/

	// Defining the viewplane
	double viewPlanePosZ = position.z - viewPlaneDistance;
	glm::dvec3 viewPlaneCorner0 = glm::dvec3(position.x - viewPlaneSizeX/2.0, position.y - viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::dvec3 viewPlaneCorner1 = glm::dvec3(position.x + viewPlaneSizeX/2.0, position.y - viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::dvec3 viewPlaneCorner2 = glm::dvec3(position.x + viewPlaneSizeX/2.0, position.y + viewPlaneSizeY/2.0, viewPlanePosZ);
	glm::dvec3 viewPlaneCorner3 = glm::dvec3(position.x - viewPlaneSizeX/2.0, position.y + viewPlaneSizeY/2.0, viewPlanePosZ);
	
	// Determining the pixelsize
	double pixelSize = viewPlaneSizeX / (double)resolutionX;			// or viewPlaneSizeY / resolutionY
	
	// Initializing variables
	glm::dvec3 pixelPosition;
	int numberOfPixels = resolutionX * resolutionY;
	//srand(time(NULL));

	//#pragma omp parallel for
	for(int i = 0; i < numberOfPixels; i++)					//Loop through all the pixels
	{
		// To determine the pixelPosition
		//   pixelPosition.x: i % resolutionX) / (double)resolutionX + viewPlaneCorner0.x
		//   pixelPosition.y: viewPlaneCorner3.y - (i/(int)resolutionY) / (double)resolutionY 
		//   pixelPosition.z: viewPlanePosZ
		pixelPosition = glm::dvec3((i % resolutionX) / (double)resolutionX + viewPlaneCorner0.x, viewPlaneCorner3.y - (i/(int)resolutionY) / (double)resolutionY , viewPlanePosZ);
		
		// Take the current pixel, call the function shootRays 
		//  that shoots, the given amount of rays, though that pixel
		pixels[i]->shootRays(position, pixelPosition, pixelSize, _objects, _light);

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
				 
void Camera::saveImage()
{
	/* This code, for saving the image into ppm-format, is taken from http://www.kevinbeason.com/smallpt/ */ 
	glm::dvec3 colorOfPixel = glm::dvec3(0.0, 0.0, 0.0);
	FILE* _file = fopen("image.ppm","w");
	fprintf(_file, "P3\n%d %d\n%d\n", resolutionX, resolutionY, 255);
	for(int i = 0; i < resolutionX * resolutionY; i++)
	{
		colorOfPixel = pixels[i]->getColorOfPixel();
		//if(glm::length(colorOfPixel) == 0)
		//{
		//	std::cout << "colorOfPixel = (0, 0, 0)..." << std::endl;
		//}
		// // std::cout << "COLOR_OF_PIXEL " << colorOfPixel.x << ", " <<colorOfPixel.y << ", "<< colorOfPixel.z << std::endl;
 		fprintf(_file,"%d %d %d\n", toInt(colorOfPixel.x), toInt(colorOfPixel.y), toInt(colorOfPixel.z));
	}
}


void Camera::mappingFunction()
{
	/* Converts radiometric values into photometric ones. */
	//TODO: Write code
}

/*
	Private functions
	
	"The output of the radiance function is a set of unbounded
	colors.  This has to be converted to be between 0 and 255 for 
	display purposes.  The following functions do this.  The toInt 
	function applies a gamma correction of 2.2."
*/
double Camera::clamp(double _x)
{
	return _x<0 ? 0 : _x>1 ? 1 : _x;
}

int Camera::toInt(double _x)
{
	return int(pow(clamp(_x),1/2.2)*255+.5);
}


