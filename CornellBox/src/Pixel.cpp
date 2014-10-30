#include "../include/Pixel.h"
#include <iostream>

/* 	
	Class Pixel  
	
	private members:
	- glm::vec3 colorOfPixel;						// vec4 for alpha?
	- glm::vec3 position;
	- static const int raysPerPixel = 32;
	- Ray* rays[raysPerPixel];
*/

/* 
	Empty constructor
*/
Pixel::Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);															// black to begin with
	position = glm::vec3(0.0, 0.0, 0.0);
}

/*
	Constructor
*/
Pixel::Pixel(int _raysPerPixel)
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);															// black to begin with
}

/*
	Destructor
*/
Pixel::~Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		delete rays[i];
	}
}

/*
	Shoot rays function
*/
void Pixel::shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects, Light* _light)
{
	float randomPointX;
	float randomPointY;
	glm::vec3 randomPoint;
	glm::vec3 direction;
	glm::vec3 color;
	srand(time(NULL));
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		// Calculating random point on the pixel
		randomPointX = _pixelPosition.x + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPointY = _pixelPosition.y + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPoint = glm::vec3(randomPointX, randomPointY, _pixelPosition.z);

		// Determining the normalized direction from eye to generated position
		direction = (randomPoint - _cameraPosition) / glm::length(randomPoint - _cameraPosition);

		rays[i] = new Ray(randomPoint, direction, 1.0/Pixel::raysPerPixel, glm::vec3(0.0, 0.0, 0.0), false);
		glm::vec3 intersectionPoints[4];																// e.g. sphere, sphere, cube, wall
		glm::vec3 finalIntersection = glm::vec3(0.0, 0.0, 0.0);
		
		int closestIntersectedObjectIndex = 666;														// temporary
		int numberOfObjects = 2;																		// temporary...
		int numberOfIterations = 30;																	// number of children
		int iteration = 1;		
		Ray* currentChildRay = rays[i];

		while(currentChildRay != nullptr && iteration <= numberOfIterations)
		{
			// resetting finalIntersection for each iteration
			finalIntersection = glm::vec3(0.0, 0.0, 0.0);		
			//closestIntersectedObjectIndex = 666;

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
				// calling mr dj, calling mr wrong, to find out diffuse/transp/intransp. object
				glm::vec3 something = currentChildRay->calculateLocalLightingContribution(_objects[closestIntersectedObjectIndex], shadowRay);
				//std::cout << something.x << something.y << something.z << std::endl;
				
				// accumulating color for current pixel
				colorOfPixel += currentChildRay->getImportance() * intersectionPointVisibleFromLightSource * something;// + 0.0002f * _objects[closestIntersectedObjectIndex]->getColor();

				// accumulating color for current pixel
				//colorOfPixel += currentChildRay->getImportance()/2.0f * intersectionPointVisibleFromLightSource * _objects[closestIntersectedObjectIndex]->getColor();// + 0.0002f * _objects[closestIntersectedObjectIndex]->getColor();				

				// calculating next child ray (iteration)
				_objects[closestIntersectedObjectIndex]->calculateChildRays(currentChildRay, finalIntersection);
			
				// free up memory
				delete shadowRay;
			}
			currentChildRay = currentChildRay->childNodes;
			iteration++;
		}
	}
	
	clearMemory();
}

/*
	Free up memory function
*/
void Pixel::clearMemory()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		Ray* currentNode = rays[i];
		while(currentNode->childNodes != nullptr)
		{
			Ray* tempNode = currentNode->childNodes;
			currentNode->childNodes = tempNode->childNodes;
			tempNode->childNodes = nullptr;
			delete tempNode;
		}
		delete currentNode;
	}
}

/*
	Get functions
*/
glm::vec3 Pixel::getColorOfPixel()
{
	return colorOfPixel;
}
