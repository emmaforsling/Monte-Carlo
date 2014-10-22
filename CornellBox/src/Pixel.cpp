#include "../include/Pixel.h"
#include <iostream>

/* 	
	Class Pixel  
	
	private members:
	- Ray* rays;
	- glm::vec3 colorOfPixel;
*/

/* Default Constructor */
Pixel::Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);															// black to begin with
	position = glm::vec3(0.0, 0.0, 0.0);
}

Pixel::Pixel(int _raysPerPixel)
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);															// black to begin with
}

/* Destructor */
Pixel::~Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		delete rays[i];
	}
}

void Pixel::shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects, Light* _light)
{
	float randomPointX;
	float randomPointY;
	glm::vec3 randomPoint;
	glm::vec3 direction;
	glm::vec3 color;
	srand(time(NULL));
	for(int i = 0; i < _raysPerPixel; i++)
	{
		// Calculating random point on the pixel
		randomPointX = _pixelPosition.x + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPointY = _pixelPosition.y + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPoint = glm::vec3(randomPointX, randomPointY, _pixelPosition.z);

		// Determining the normalized direction from eye to generated position
		direction = (randomPoint - _cameraPosition) / glm::length(randomPoint - _cameraPosition);

		rays[i] = new Ray(randomPoint, direction, 1.0/_raysPerPixel, glm::vec3(0.0, 0.0, 0.0), false);
		glm::vec3 intersectionPoints[4];																// e.g. sphere, sphere, cube, wall
		glm::vec3 finalIntersection = glm::vec3(0.0, 0.0, 0.0);
		int closestIntersectedObjectIndex = 666;														// temporary
		int numberOfObjects = 4;																		// temporary...
		int numberOfIterations = 12;																	// number of children
		int iteration = 1;
		
		for(Ray* currentChildRay = rays[i]; currentChildRay != nullptr && iteration <= numberOfIterations; currentChildRay = currentChildRay->childNodes, iteration++)
		{
			// resetting finalIntersection for each iteration
			finalIntersection = glm::vec3(0.0, 0.0, 0.0);		

			// looping through objects to find intersections
			for(int j = 0; j < numberOfObjects; j++)
			{			
				intersectionPoints[j] = _objects[j]->calculateIntersection(currentChildRay);
				glm::vec3 normal = _objects[j]->getIntersectedNormal();
				int intersectedSide = _objects[j]->getIntersectedSide(); 								// is used primarily for walls
				
				// if an intersection has been found && no previous intersections have been stored (first encountered object)
				if(glm::length(intersectionPoints[j]) != 0 && glm::length(finalIntersection) == 0)
				{
					finalIntersection = intersectionPoints[j];
					currentChildRay->intersectionPoint = intersectionPoints[j];
					closestIntersectedObjectIndex = j;
				}
				// if an intersection has been found + not the first encountered object && not the object with the starting point of the ray (encountered another object)
				else if(glm::length(intersectionPoints[j]) != 0 && intersectionPoints[j] != currentChildRay->getStartingPoint())
				{
					// if new intersection point is closer to the ray origin than any found on previous objects
					if( glm::length(intersectionPoints[j] - currentChildRay->getStartingPoint()) < glm::length(finalIntersection - currentChildRay->getStartingPoint()) )
					{
						finalIntersection = intersectionPoints[j];	// object closest to ray origin
						currentChildRay->intersectionPoint = intersectionPoints[j];
						closestIntersectedObjectIndex = j;
					}
					// if new intersection point is farther from the ray origin than any found on previous objects
					else
					{

					}		
				}
			}

			if(closestIntersectedObjectIndex != 666)
			{
				int intersectionPointVisibleFromLightSource = 1;										// 1 = visible, 0 = not visible
				glm::vec3 randomPositionOnLightSource = _light->getRandomPosition();			

				// calculating shadow ray - defined as a ray from the light source to a surface, to be able to use Object::calculateIntersection();
				Ray* shadowRay = new Ray(randomPositionOnLightSource, (finalIntersection - randomPositionOnLightSource), 1.0, glm::vec3(0.0, 0.0, 0.0), false);
				glm::vec3 shadowIntersection;
				
				// looping through all objects to check for occlusion
				for(int j = 0; j < numberOfObjects; j++)
				{
					// calculating intersection between shadow ray and object
					shadowIntersection = _objects[j]->calculateIntersection(shadowRay);
					// if intersection
					if( shadowIntersection != glm::vec3(0.0, 0.0, 0.0) )
					{	
						// occlusion if returned point is closer to the light source
						if( glm::length(randomPositionOnLightSource - shadowIntersection) != 0 && glm::length(randomPositionOnLightSource - shadowIntersection) < glm::length(randomPositionOnLightSource - finalIntersection) )
						{
							intersectionPointVisibleFromLightSource = 0;
							break;
						}
						// no occlusion if returned point is farther from the light source
						else
						{

						}
					}
				}
				
				// accumulating color for current pixel
				colorOfPixel += currentChildRay->getImportance()/2.0f * intersectionPointVisibleFromLightSource * _objects[closestIntersectedObjectIndex]->getColor();// + 0.0002f * _objects[closestIntersectedObjectIndex]->getColor();				
				
				// calculating next child ray (iteration)
				_objects[closestIntersectedObjectIndex]->calculateChildRays(currentChildRay, finalIntersection);
			}
		}
	}
}

glm::vec3 Pixel::getColorOfPixel()
{
	return colorOfPixel;
}
