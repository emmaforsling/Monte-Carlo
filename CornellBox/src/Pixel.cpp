#include "../include/Pixel.h"
#include <iostream>

/* 	
	Class Pixel  
	
	private members:
	- glm::dvec3 colorOfPixel;
	- glm::dvec3 position;
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
	colorOfPixel = glm::dvec3(0.0, 0.0, 0.0);															// black to begin with
	position = glm::dvec3(0.0, 0.0, 0.0);
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
	colorOfPixel = glm::dvec3(0.0, 0.0, 0.0);															// black to begin with
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
void Pixel::shootRays(glm::dvec3 _cameraPosition, glm::dvec3 _pixelPosition, double _pixelSize, Object** _objects, Light* _light)
{
	double randomPointX;
	double randomPointY;
	glm::dvec3 randomPoint;
	glm::dvec3 direction;
	glm::dvec3 color;
	bool intersectionPointVisibleFromLightSource;

	//srand(time(NULL));
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		// Calculating random point on the pixel
		randomPointX = _pixelPosition.x + (_pixelSize * static_cast <double>(rand()) ) / static_cast<double>(RAND_MAX);
		randomPointY = _pixelPosition.y + (_pixelSize * static_cast <double>(rand()) ) / static_cast<double>(RAND_MAX);
		randomPoint = glm::dvec3(randomPointX, randomPointY, _pixelPosition.z);

		// Determining the normalized direction from eye to generated position
		direction = (randomPoint - _cameraPosition) / glm::length(randomPoint - _cameraPosition);

		rays[i] = new Ray(randomPoint, direction, 1.0/Pixel::raysPerPixel, glm::dvec3(0.0, 0.0, 0.0), false);
																												// e.g. sphere, sphere, cube, wall
		glm::dvec3 finalIntersection;
		int closestIntersectedObjectIndex;																		// temporary
		const int numberOfObjects = 2;																			// temporary...
		int numberOfIterations = 4;																				// number of children
		int iteration = 0;
		rays[i]->setImportance(1 / raysPerPixel); //emma 2015-01-08
		std::cout << "rays[i]->getImportance()" << rays[i]->getImportance() << std::endl;		
		
		glm::dvec3 intersectionPoints[numberOfObjects];
		
		std::vector<Ray*> childRays;
		childRays.push_back(rays[i]);
		int rayChildIndex = 0;
		Ray* currentChildRay = nullptr;

		while(rayChildIndex < childRays.size() && iteration < numberOfIterations)
		{
			currentChildRay = childRays.at(rayChildIndex);
			//std::cout << "direction in iteration " << iteration << " (" << currentChildRay->getDirection().x << ", " << currentChildRay->getDirection().y << ", " << currentChildRay->getDirection().z << ")" << std::endl;
			// resetting finalIntersection for each iteration
			closestIntersectedObjectIndex = 666;
			finalIntersection = glm::dvec3(0.0, 0.0, 0.0);		
			//closestIntersectedObjectIndex = 666;
			//std::cout << "\niteration = " << iteration << std::endl;
			// looping through objects to find intersections
			for(int j = 0; j < numberOfObjects; j++)
			{			
				intersectionPoints[j] = _objects[j]->calculateIntersection(currentChildRay, false);
				glm::dvec3 normal = _objects[j]->getIntersectedNormal();
				int intersectedSide = _objects[j]->getIntersectedSide(); 									// is used primarily for walls
				
				// if an intersection has been found && no previous intersections have been stored (first encountered object)
				if(glm::length(intersectionPoints[j]) != 0.0 && glm::length(finalIntersection) == 0.0)
				{
					finalIntersection = intersectionPoints[j];
					currentChildRay->intersectionPoint = intersectionPoints[j];
					closestIntersectedObjectIndex = j;
					// std::cout << "1, closestIntersectedObjectIndex = " << closestIntersectedObjectIndex << std::endl;
					// std::cout << "finalIntersection = " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << std::endl;
				}
				// if an intersection has been found + not the first encountered object && not the object with the starting point of the ray (encountered another object)
				else if(glm::length(intersectionPoints[j]) != 0.0 && intersectionPoints[j] != currentChildRay->getStartingPoint())
				{
					// std::cout << "currentChildRay->getStartingPoint = (" << currentChildRay->getStartingPoint().x << ", " << currentChildRay->getStartingPoint().y << ", " << currentChildRay->getStartingPoint().z << ")" << std::endl;
					// if new intersection point is closer to the ray origin than any found on previous objects
					if( glm::length(intersectionPoints[j] - currentChildRay->getStartingPoint()) < glm::length(finalIntersection - currentChildRay->getStartingPoint()) )
					{
						finalIntersection = intersectionPoints[j];	// object closest to ray origin
						currentChildRay->intersectionPoint = intersectionPoints[j];
						closestIntersectedObjectIndex = j;
						// std::cout << "2, closestIntersectedObjectIndex = " << closestIntersectedObjectIndex << std::endl;
						// std::cout << "finalIntersection = " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << std::endl;
					}
					// if new intersection point is farther from the ray origin than any found on previous objects
					else
					{

					}		
				}
				
				else
				{
					//std::cout << "ingen intersection?" << std::endl;
					//std::cout << "finalIntersection = " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << std::endl;
				}
				
			}
			// std::cout << "3, THE FINAL closestIntersectedObjectIndex = " << closestIntersectedObjectIndex << std::endl;
			// std::cout << "THE FINAL finalIntersection = " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << std::endl;

			if(closestIntersectedObjectIndex != 666)
			{
				// Shadow ray
				glm::dvec3 randomPositionOnLightSource = _light->getRandomPosition();
				intersectionPointVisibleFromLightSource = castShadowRay(randomPositionOnLightSource, finalIntersection, _objects, numberOfObjects);

				// calling mr dj, calling mr wrong, to find out diffuse/transp/intransp. object
				glm::dvec3 localLightingContribution = currentChildRay->calculateLocalLightingContribution(_objects[closestIntersectedObjectIndex], (randomPositionOnLightSource - finalIntersection), _light->getRadiance(), iteration);

				// accumulating color for current pixel	
				if(_light->isOnLightSource(finalIntersection))
				{
					colorOfPixel = glm::dvec3(1.0,1.0,1.0);
				}
				else
				{
					//std::cout << "IntersectionPointVisibleFromLightSource " << intersectionPointVisibleFromLightSource << std::endl; 
					// if(iteration == 2)
					// {
					// 	std::cout << "closest object: " << closestIntersectedObjectIndex << std::endl;
					// 	std::cout << "localLightingContribution = (" << localLightingContribution.x << ", " << localLightingContribution.y << ", " << localLightingContribution.z << ")"  << std::endl;;
					// }
					colorOfPixel += currentChildRay->getImportance() * intersectionPointVisibleFromLightSource * localLightingContribution;
				}

				//if(colorOfPixel == glm::dvec3(0.0,0.0,0.0))
				//{
					//std::cout << "closestIntersectedObjectIndex: " << closestIntersectedObjectIndex << std::endl; 

				//}
				//std::cout << "colorOfPixel = (" << colorOfPixel.x << ", " << colorOfPixel.y << ", " << colorOfPixel.z << ")" << std::endl;
				// accumulating color for current pixel
				//colorOfPixel += currentChildRay->getImportance()/2.0f * intersectionPointVisibleFromLightSource * _objects[closestIntersectedObjectIndex]->getColor();// + 0.0002f * _objects[closestIntersectedObjectIndex]->getColor();				

				// calculating next child ray (iteration)
				//std::cout << "closest object = " << closestIntersectedObjectIndex << std::endl;
				if(currentChildRay->getDirection() != currentChildRay->getDirection())
				{
					colorOfPixel = glm::dvec3(1.0, 0.6, 0.1);
					//std::cout << "Pixle::shootRays(), currentChildRay->getDirection=(" << currentChildRay->getDirection().x << ", " << currentChildRay->getDirection().y << ", " << currentChildRay->getDirection().z << ")" << std::endl;
					//std::cout << "Pixle::shootRays(), currentChildRay->getStartingPoint=(" << currentChildRay->getStartingPoint().x << ", " << currentChildRay->getStartingPoint().y << ", " << currentChildRay->getStartingPoint().z << ")" << std::endl;
				}
				//std::cout << "nu gör jag en ny stråle" << std::endl;

				_objects[closestIntersectedObjectIndex]->calculateChildRays(currentChildRay, finalIntersection);
				//currentChildRay = currentChildRay->childNodes;
				if(currentChildRay->reflectedRay != nullptr)
				{
					childRays.push_back(currentChildRay->reflectedRay);
				}
				if(currentChildRay->refractedRay != nullptr)
				{
					childRays.push_back(currentChildRay->refractedRay);
				}
			}
			else
			{
				//std::cout << "\nclosest object = " << closestIntersectedObjectIndex << std::endl;
				colorOfPixel = glm::dvec3(1.0,0.0,0.0); //testing something emma, 2015-01-05
			
			}
			
			iteration++;
			rayChildIndex++;
		}
	}

	if(glm::length(colorOfPixel) == 0)
	{
		//std::cout << "============== colorOfPixel = (0, 0, 0) ==============" << std::endl;
	}
	
	clearMemory();
}

/*
	Free up memory function
*/
void Pixel::clearMemory()
{
	/*
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
	*/
}

/*
	Get functions
*/
glm::dvec3 Pixel::getColorOfPixel()
{
	return colorOfPixel;
}

bool Pixel::castShadowRay(glm::dvec3 _randomPositionOnLightSource, glm::dvec3 _intersection, Object** _objects, int _numberOfObjects)
{
	bool intersectionPointVisibleFromLightSource = true;										// 1 = visible, 0 = not visible	

	// calculating shadow ray - defined as a ray from the light source to a surface, to be able to use Object::calculateIntersection();
	Ray* shadowRay = new Ray(_randomPositionOnLightSource, (_intersection - _randomPositionOnLightSource), 1.0, glm::dvec3(0.0, 0.0, 0.0), false);
	glm::dvec3 shadowIntersection;

	//std::cout << "Shadow ray:" << std::endl;
	
	// looping through all objects to check for occlusion
	for(int j = 0; j < _numberOfObjects; j++)
	{
		// calculating intersection between shadow ray and object
		shadowIntersection = _objects[j]->calculateIntersection(shadowRay, true);
		//std::cout << "ShadowIntersection = (" << shadowIntersection.x  << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ")" << std::endl;
		// if intersection
		if( shadowIntersection != glm::dvec3(0.0, 0.0, 0.0) )
		{	
			// occlusion if returned point is closer to the light source
			if( glm::length(_randomPositionOnLightSource - shadowIntersection) != 0 && (float)glm::length(_randomPositionOnLightSource - shadowIntersection) < (float)glm::length(_randomPositionOnLightSource - _intersection) )
			{
				/*std::cout << "=== occlusion ===!" << std::endl;
				std::cout << "randomPositionOnLightSource = (" << _randomPositionOnLightSource.x << ", " << _randomPositionOnLightSource.y << ", " << _randomPositionOnLightSource.z << ")" << std::endl;
				std::cout << "shadowIntersection = (" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ")" << std::endl;
				glm::dvec3 temp1 = _randomPositionOnLightSource - shadowIntersection;
				glm::dvec3 temp2 = _randomPositionOnLightSource - _intersection;
				std::cout << "_randomPositionOnLightSource - shadowIntersection = (" << temp1.x << ", " << temp1.y << ", " << temp1.z << ")" << std::endl;
				std::cout << "_randomPositionOnLightSource - _intersection = (" << temp2.x << ", " << temp2.y << ", " << temp2.z << ")" << std::endl;
				double length1 = glm::length(_randomPositionOnLightSource - shadowIntersection);
				double length2 = glm::length(_randomPositionOnLightSource - _intersection);
				std::cout << "length1 = " << length1 << std::endl;
				std::cout << "length2 = " << length1 << std::endl;
				std::cout << "length1 < length2: " << ((float)length1 < (float)length2) << std::endl;*/
				intersectionPointVisibleFromLightSource = false;
				// free up memory
				delete shadowRay;
				return intersectionPointVisibleFromLightSource;
			}
			// no occlusion if returned point is farther from the light source
			else
			{

			}
		}
	}
	// free up memory
	delete shadowRay;
	return intersectionPointVisibleFromLightSource;
}
