#include "../include/Wall.h"

/* 	
	Class Wall  
	
	private members:
	- glm::dvec3 intersectedNormal
	- int intersectedSide

	public variables:
	- glm::dvec3 position;
	- double size;
*/

/* 
	Empty constructor
*/
Wall::Wall()
: Object(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), false, false)
{
	// position = glm::dvec3(0.0, 0.0, 0.0);
	size = 0.0;

	walls[0] = nullptr;
	walls[1] = nullptr;
	walls[2] = nullptr;
	walls[3] = nullptr;
	walls[4] = nullptr;
}

/*
	Constructor
*/
Wall::Wall(glm::dvec3 _position, double _size, glm::dvec3 _color, bool _diffuse, bool _transparent)
: Object(_position, _color, _diffuse, _transparent)
{
	// position = _position;
	size = _size;

	walls[0] = nullptr;
	walls[1] = nullptr;
	walls[2] = nullptr;
	walls[3] = nullptr;
	walls[4] = nullptr;

	color = _color;
	initializeRectangles();
	
}

/* Destructor */
Wall::~Wall()
{
	//TODO: Write code 
	// std::cout << "Hello me" << std::endl;
}

/*
	Initialze functions
*/	
void Wall::initializeRectangles()
{
	/*
	   3 -- 2
	   |    |
	   0 -- 1
	*/
	glm::dvec3 WHITE = glm::dvec3(1.0,1.0,1.0);
	glm::dvec3 RED = glm::dvec3(0.8,0.1,0.1);
	glm::dvec3 GREEN = glm::dvec3(0.1,0.8,0.1);
	glm::dvec3 BLUE = glm::dvec3(0.1,0.1,0.8);
	glm::dvec3 GRAY = glm::dvec3(0.5, 0.5, 0.5);

	walls[0] = new Rectangle();		//left
	walls[0]->positionsOfCorners[0] = glm::dvec3(0.0, 0.0, size) + position;
	walls[0]->positionsOfCorners[1] = glm::dvec3(0.0, 0.0, 0.0) + position;
	walls[0]->positionsOfCorners[2] = glm::dvec3(0.0, size, 0.0) + position;
	walls[0]->positionsOfCorners[3] = glm::dvec3(0.0, size, size) + position;
	walls[0]->setColor(BLUE);

	walls[1] = new Rectangle();		//up
	walls[1]->positionsOfCorners[0] = glm::dvec3(0.0, size, 0.0) + position;
	walls[1]->positionsOfCorners[1] = glm::dvec3(size, size, 0.0) + position;
	walls[1]->positionsOfCorners[2] = glm::dvec3(size, size, size) + position;
	walls[1]->positionsOfCorners[3] = glm::dvec3(0.0, size, size) + position;
	walls[1]->setColor(WHITE);

	walls[2] = new Rectangle();		//right
	walls[2]->positionsOfCorners[0] = glm::dvec3(size, 0.0, 0.0) + position;
	walls[2]->positionsOfCorners[1] = glm::dvec3(size, 0.0, size) + position;
	walls[2]->positionsOfCorners[2] = glm::dvec3(size, size, size) + position;
	walls[2]->positionsOfCorners[3] = glm::dvec3(size, size, 0.0) + position;
	walls[2]->setColor(RED);

	walls[3] = new Rectangle();		//down
	walls[3]->positionsOfCorners[0] = glm::dvec3(0.0, 0.0, size) + position;
	walls[3]->positionsOfCorners[1] = glm::dvec3(size, 0.0, size) + position;
	walls[3]->positionsOfCorners[2] = glm::dvec3(size, 0.0, 0.0) + position;
	walls[3]->positionsOfCorners[3] = glm::dvec3(0.0, 0.0, 0.0) + position;
	walls[3]->setColor(GREEN);

	walls[4] = new Rectangle();		//back
	walls[4]->positionsOfCorners[0] = glm::dvec3(0.0, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[1] = glm::dvec3(size, 0.0, 0.0) + position;
	walls[4]->positionsOfCorners[2] = glm::dvec3(size, size, 0.0) + position;
	walls[4]->positionsOfCorners[3] = glm::dvec3(0.0, size, 0.0) + position;
	walls[4]->setColor(GRAY);
	
	// // std::cout << "Nu har jag initialiserat alla sidor på rummet! Titta så fina:" << std::endl;
	// for(int i=0; i<5; i++)
	// {
	// 	// std::cout << "Vägg " << i << std::endl;
	// 	for(int j=0; j<4; j++)
	// 	{
	// 		// std::cout << walls[i]->positionsOfCorners[j].x << " " << walls[i]->positionsOfCorners[j].y << " " << walls[i]->positionsOfCorners[j].z << std::endl;
	// 	}
	// }
	
}

/*
	Calculation functions
*/
void Wall::calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint)				// TEMPORARY
{
	// Russian Roulette
	// // std::cout << "\nCalculating child ray for intersection point " << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << std::endl << std::endl;
	// calculate direction for reflected or transmitted ray - WHITTED - (TEMPORARY)
	// // std::cout << "====== Reflection/refraction =====" << std::endl;
	// std::cout << "\n\n\n CalculateChildRays .. IntersectionPOINT: " << intersectionPoint.x << ", " << intersectionPoint.y << ", "<< intersectionPoint.z << std::endl;
	// glm::dvec3 reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
	// glm::dvec3 refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, getRefractiveIndex());

	// _ray->childNodes = new Ray(intersectionPoint, reflectedRayDirection, _ray->getImportance()/2.0, getColor(), false);
}

/* either one intersection or none (ray leaving) */
glm::dvec3 Wall::calculateIntersection(Ray* _ray)
{
	//TODO: Write code
	/*
		To calculate the intesection point for the Wall,
		first calculate the intersection point for a plane,
		then see if the intersection point on the plane is within the wall

		The approach for determine the intersection point for a plane
		is the same that is used in Rectangle.
	*/
	// // std::cout << "==== studying wall (" << position.x << ", " << position.y << ", " << position.z << "), size = " << size << " ==== \n";
	glm::dvec3 intersection;
	glm::dvec3 finalIntersection = glm::dvec3(0.0, 0.0, 0.0);
	glm::dvec3 _startPoint = _ray->getStartingPoint(); 		//nu fristaijlar jag
	int wall = 666;
	for(int i=0; i<5; i++)
	{
		// // std::cout << " - studying rectangle " << i << " - "; // << std::endl;
		intersection = walls[i]->calculateIntersection(_ray);
		if(intersection != _startPoint)
		{
			// std::cout << "INTERSECTION POINT != START POINT" << std::endl;
			// std::cout << "intersection = " << intersection.x << ", " << intersection.y << ", " << intersection.z 
			//<< "\n start point = " << _startPoint.x << ", "<< _startPoint.y << ", "<< _startPoint.z << std::endl;
						//// // std::cout << "walls[" << i << "]->calculateIntersection(_ray) returned: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;

			//if intersection == glm::vec(0.0,0.0,0.0) then no intersection
			if( intersection == glm::dvec3(0.0, 0.0, 0.0) )
			{
				// // std::cout << "				- NO INTERSECTIONS - " << std::endl;
			}
			if( intersection != glm::dvec3(0.0, 0.0, 0.0) )
			{
				// first detected intersection
				if(finalIntersection == glm::dvec3(0.0, 0.0, 0.0))
				{
					// // std::cout << "Detected first intersection (";
					finalIntersection = intersection;
					wall = i;
					// // std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;

				}
				// second detected intersection
				else
				{
					// // std::cout << "Detected second intersection (";
					// // std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;
					/* message */
					// // // std::cout << "walls[" << i << "].calculateIntersection(Ray* _ray) = " << intersection.x << ", " 
					// << intersection.y << ", " << intersection.z << std::endl;
					/* end message */
					double intersectionDistance = glm::length(intersection - _ray->getStartingPoint());
					// std::cout << "STARTPUNKTEN = " << _ray->getStartingPoint().x << ", " << _ray->getStartingPoint().y << ", " << _ray->getStartingPoint().z ;
					// Ray inside object
					if(_ray->isInsideObject())
					{
						//// // std::cout << "Ray inside object. ";
						if(intersectionDistance  > glm::length(finalIntersection - _ray->getStartingPoint()) )
						{
							//// // std::cout << "Choosing new intersection point (farther from ray origin - exit point)." << std::endl;
							wall = i;
							finalIntersection = intersection;
						}
						else
						{
							//// // std::cout << "Discarding new intersection point (closer to ray origin - entry point)" << std::endl;
						}
					}
					// Ray outside object
					else
					{
						//// // std::cout << "Ray outside object. ";
						if( intersectionDistance > 0.0 && intersectionDistance < glm::length(finalIntersection - _ray->getStartingPoint()) )
						{
							// std::cout << "Choosing new intersection point (closer to ray origin - entry point)." << std::endl;
							wall = i;
							finalIntersection = intersection;
						}
						else
						{
							//// // std::cout << "Discarding new intersection point (farther from ray origin - exit point)" << std::endl;
						}
					}
				}			
			}	
		}

	}
	if(wall!=666)
	{
		intersectedNormal = walls[wall]->getNormal();
		intersectedSide = wall;
		// // std::cout << "Normal at intersection: " << intersectedNormal.x << ", " << intersectedNormal.y << ", " << intersectedNormal.z << std::endl;
	}

	// std::cout << "Returning final intersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ")" << std::endl;
	return finalIntersection;


	// return glm::dvec3(0.0, 0.0, 0.0);
}

/*
	Get functions
*/
glm::dvec3 Wall::getColor()
{
	return walls[intersectedSide]->getColor();
}

glm::dvec3 Wall::getIntersectedNormal()
{
	return intersectedNormal;
}

int Wall::getIntersectedSide()
{
	return intersectedSide;
}

double Wall::getRefractiveIndex()				// this is weird...
{
	return 0.0;
}

