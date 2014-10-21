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
	// // std::cout << "Pixel::tom konstruktor" << std::endl;
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
	position = glm::vec3(0.0, 0.0, 0.0);
}

Pixel::Pixel(int _raysPerPixel)
{
	//// std::cout << "Pixel::full konstruktor" << std::endl;
	//rays = new Ray[_raysPerPixel]();
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		rays[i] = nullptr;
	}
	colorOfPixel = glm::vec3(0.0, 0.0, 0.0);		// black to begin with 
}

/* Destructor */
Pixel::~Pixel()
{
	for(int i = 0; i < Pixel::raysPerPixel; i++)
	{
		delete rays[i];
	}
	//TODO: Write code
}

/* Should also track the rays within the scene (tree structure?) */
void Pixel::shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects, Light* _light)
{
	// // std::cout << "entering pixel! " << std::endl << std::endl;
	float randomPointX;
	float randomPointY;
	glm::vec3 randomPoint;
	glm::vec3 direction;
	glm::vec3 color;
	srand(time(NULL));
	for(int i = 0; i < _raysPerPixel; i++)
	{
		// std::cout << "\n======= SHOOTING RAY =======\n" << std::endl;
		// // std::cout << "Slumpar mellan " << _pixelPosition.x << " och " << _pixelPosition.x + _pixelSize << " i x" << std::endl;
		// // std::cout << "Slumpar mellan " << _pixelPosition.y << " och " << _pixelPosition.y + _pixelSize << " i y" << std::endl;
		randomPointX = _pixelPosition.x + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		randomPointY = _pixelPosition.y + (_pixelSize * static_cast <float>(rand()) ) / static_cast<float>(RAND_MAX);
		//randomPointY = _pixelPosition.y + static_cast <float>(rand()) / (static_cast<float>(RAND_MAX / (_pixelPosition.y + _pixelSize - _pixelPosition.y)));
		
		// // std::cout << "Nu har jag slumpat ut two values for dig: " << randomPointX << ", " << randomPointY << std::endl;
		
		// The random point on the pixel
		randomPoint = glm::vec3(randomPointX, randomPointY, _pixelPosition.z);

		// Determine the normalized direction from eye to generated position
		direction = (randomPoint - _cameraPosition) / glm::length(randomPoint - _cameraPosition);

		/* === Debugging === */
		//// std::cout << "Kameraposition: " << _cameraPosition.x << ", " << _cameraPosition.y << ", " << _cameraPosition.z << ")" << std::endl;
		//// std::cout << "ger riktning: (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;

		//
		rays[i] = new Ray(randomPoint, direction, 1.0/_raysPerPixel, glm::vec3(0.0, 0.0, 0.0), false);
		glm::vec3 intersectionPoints[4];						// e.g. sphere, sphere, cube, wall
		glm::vec3 finalIntersection = glm::vec3(0.0, 0.0, 0.0);
		int closestIntersectedObjectIndex = 666;
		int numberOfObjects = 4;								// Temporary...
		int numberOfIterations = 10;
		int iteration = 0;
		for(Ray* currentChildRay = rays[i]; currentChildRay != nullptr && iteration <= numberOfIterations; currentChildRay = currentChildRay->childNodes, iteration++)
		{
			for(int j = 0; j < numberOfObjects; j++)				// loop through objects
			{
				// _objects[j]->calculateChildRays(_objects[j]->calculateIntersection(rays[i]));
				glm::vec3 normal = _objects[j]->getIntersectedNormal();
				int intersectedSide = _objects[j]->getIntersectedSide(); //is used primarily for walls
			
				intersectionPoints[j] = _objects[j]->calculateIntersection(rays[i]);
				if( glm::length(finalIntersection) == 0)			// first encountered object
				{
					if(glm::length(intersectionPoints[j]) != 0)
					{
						//// std::cout << "(This was the first studied object)" << std::endl;
						finalIntersection = intersectionPoints[j];
						closestIntersectedObjectIndex = j;
					}
				}
				else												// not the first object
				{
					//// std::cout << "(This was not the first studied object)" << std::endl;
					if( glm::length(intersectionPoints[j] - rays[i]->getStartingPoint()) < glm::length(finalIntersection - rays[i]->getStartingPoint()) )
					{
						//// std::cout << "Intersection closer to ray origin!" << std::endl;
						finalIntersection = intersectionPoints[j];	// object closest to ray origin
						closestIntersectedObjectIndex = j;
					}
					else
					{
						//// std::cout << "Intersection farther from ray origin!" << std::endl;
					}
				}
			}
			if(closestIntersectedObjectIndex != 666)
			{
				int intersectionPointVisibleFromLightSource = 1;			// 1 = visible, 0 = not visible
				glm::vec3 randomPositionOnLightSource = _light->getRandomPosition();
				// shadow ray defined as a ray from the light source to a surface, to be able to use Object::calculateIntersection();
				Ray* shadowRay = new Ray(randomPositionOnLightSource, (finalIntersection - randomPositionOnLightSource), 1.0, glm::vec3(0.0, 0.0, 0.0), false);
				// looping through all objects to check for occlusion
				glm::vec3 shadowIntersection;
				// std::cout << "\n= Checking for occlusion. p = (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << "), l = (" << randomPositionOnLightSource.x << ", " << randomPositionOnLightSource.y << ", " << randomPositionOnLightSource.z << ") =\n" << std::endl;
				for(int j = 0; j < numberOfObjects; j++)
				{
					shadowIntersection = _objects[j]->calculateIntersection(shadowRay);
					// // std::cout << "objects[" << j << "]->calculateIntersection(shadowRay) returned: (" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ")" << std::endl;
					if( shadowIntersection != glm::vec3(0.0, 0.0, 0.0) )
					{	
						//// std::cout << "Found intersection along shadowRay direction!" << std::endl;
						if( glm::length(randomPositionOnLightSource - shadowIntersection) != 0 && glm::length(randomPositionOnLightSource - shadowIntersection) < glm::length(randomPositionOnLightSource - finalIntersection) )
						{
							intersectionPointVisibleFromLightSource = 0;
							// std::cout << "Intersection point " << "(" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ") closer to the light source - occlusion!" << std::endl;
						}
						else
						{
							// std::cout << "Intersection point " << "(" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ") not closer to the light source - no occlusion!" << std::endl;
						}
					}
				}
				if(_objects[2]) //walls
				{
					colorOfPixel += currentChildRay->getImportance()/2.0f * intersectionPointVisibleFromLightSource * _objects[closestIntersectedObjectIndex]->getColor();
				}
				else
				{
					colorOfPixel += currentChildRay->getImportance()/2.0f * intersectionPointVisibleFromLightSource * _objects[closestIntersectedObjectIndex]->getColor();
					// std::cout << "colorOfPixel += " << currentChildRay->getImportance()/2.0f << " * " << intersectionPointVisibleFromLightSource << " * (" << _objects[closestIntersectedObjectIndex]->getColor().x << ", " << _objects[closestIntersectedObjectIndex]->getColor().y << ", " << _objects[closestIntersectedObjectIndex]->getColor().z << ")" << std::endl;	
				}
				
				// calculating child rays
				_objects[closestIntersectedObjectIndex]->calculateChildRays(currentChildRay, finalIntersection);
			}
		}
	}

	// TODO: Write code
	// 1. Generate Camera::raysPerPixel random directions, and launch a new Ray into these.
	// 2. Append the new rays to Pixel::rays
	// 3. colorOfPixel += rays[i]->calculateColor()

	// std::cout << "\n\n =-._.-=-._.-=  colorOfPixel = (" << colorOfPixel.x << ", " << colorOfPixel.y << ", " << colorOfPixel.z << ")" << std::endl << std::endl;
}

glm::vec3 Pixel::getColorOfPixel()
{
	return colorOfPixel;
}
