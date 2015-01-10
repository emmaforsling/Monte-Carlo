#include "../include/Cube.h"
#include <iostream>

/* 	
	Class Cube  
	
	private members:
	- Rectangle* sides[6];
	- glm::dvec3 position;
	- double size;
	- double transparency;
	- double refractiveIndex;
*/

/* 
	Default Constructor 
*/
Cube::Cube()
: Object(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), false, false) //position, color
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	// position = glm::dvec3(0.0, 0.0, 0.0);
	size = 0.0;
	transparent = false;
	refractiveIndex = 0.0;
	intersectedNormal = glm::dvec3(0.0,0.0,0.0);
}

/*
	Constructor
*/
Cube::Cube(glm::dvec3 _position, double _size, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse)
: Object(_position, _color, _diffuse, _transparent)
{
	sides[0] = nullptr;
	sides[1] = nullptr;
	sides[2] = nullptr;
	sides[3] = nullptr;
	sides[4] = nullptr;
	sides[5] = nullptr;

	// position = _position;
	size = _size;
	refractiveIndex = _refractiveIndex;

	initializeRectangles();
}

/*
	Sets corners of rectangles to (0,0,0), (1,0,0), (0,1,0) etc.
	and multiplies them by size (double) and adds the position (glm::dvec3))
*/
void Cube::initializeRectangles()
{
	/*
	   3 -- 2
	   |    |
	   0 -- 1
	*/
	   
	sides[0] = new Rectangle();		// left
	sides[0]->positionsOfCorners[0] = glm::dvec3(0.0, 0.0, 0.0) + position;
	sides[0]->positionsOfCorners[1] = glm::dvec3(0.0, 0.0, size) + position;
	sides[0]->positionsOfCorners[2] = glm::dvec3(0.0, size, size) + position;
	sides[0]->positionsOfCorners[3] = glm::dvec3(0.0, size, 0.0) + position;

	sides[1] = new Rectangle();		// up
	sides[1]->positionsOfCorners[0] = glm::dvec3(size, size, 0.0) + position;
	sides[1]->positionsOfCorners[1] = glm::dvec3(0.0, size, 0.0) + position;
	sides[1]->positionsOfCorners[2] = glm::dvec3(0.0, size, size) + position;
	sides[1]->positionsOfCorners[3] = glm::dvec3(size, size, size) + position;
	
	sides[2] = new Rectangle();		// right
	sides[2]->positionsOfCorners[0] = glm::dvec3(size, 0.0, size) + position;
	sides[2]->positionsOfCorners[1] = glm::dvec3(size, 0.0, 0.0) + position;
	sides[2]->positionsOfCorners[2] = glm::dvec3(size, size, 0.0) + position;
	sides[2]->positionsOfCorners[3] = glm::dvec3(size, size, size) + position;
		
	sides[3] = new Rectangle();		// down
	sides[3]->positionsOfCorners[0] = glm::dvec3(size, 0.0, size) + position;
	sides[3]->positionsOfCorners[1] = glm::dvec3(0.0, 0.0, size) + position;
	sides[3]->positionsOfCorners[2] = glm::dvec3(0.0, 0.0, 0.0) + position;
	sides[3]->positionsOfCorners[3] = glm::dvec3(size, 0.0, 0.0) + position;
	
	sides[4] = new Rectangle();		// back
	sides[4]->positionsOfCorners[0] = glm::dvec3(size, 0.0, 0.0) + position;
	sides[4]->positionsOfCorners[1] = glm::dvec3(0.0, 0.0, 0.0) + position;
	sides[4]->positionsOfCorners[2] = glm::dvec3(0.0, size, 0.0) + position;
	sides[4]->positionsOfCorners[3] = glm::dvec3(size, size, 0.0) + position;

	sides[5] = new Rectangle();		// front
	sides[5]->positionsOfCorners[0] = glm::dvec3(0.0, 0.0, size) + position;
	sides[5]->positionsOfCorners[1] = glm::dvec3(size, 0.0, size) + position;
	sides[5]->positionsOfCorners[2] = glm::dvec3(size, size, size) + position;
	sides[5]->positionsOfCorners[3] = glm::dvec3(0.0, size, size) + position;
	
	/*
	// // std::cout << "Nu har jag initialiserat alla sidor på kuben! Titta så fina:" << std::endl;
	for(int i=0; i<6; i++)
	{
		// // std::cout << "side " << i << std::endl;
		for(int j=0; j<4; j++)
		{
			// // std::cout << sides[i]->positionsOfCorners[j].x << " " << sides[i]->positionsOfCorners[j].y << " " << sides[i]->positionsOfCorners[j].z << std::endl;
		}
	}
	*/
}

/*
	Calculation functions
*/
glm::dvec3 Cube::calculateIntersection(Ray* _ray, bool _isShadowRay) 
{
	glm::dvec3 intersection;
	glm::dvec3 finalIntersection = glm::dvec3(0.0,0.0,0.0);
	//finalIntersection = _ray->getStartingPoint();

	// Loopa igenom de 6 rektanglarna
	// Kolla ifall de intersectar med kuben
	// Ta reda på insida/utsida
	for(int i = 0; i < 6; i++)
	{
		intersection = sides[i]->calculateIntersection(_ray);

		if(intersection != glm::dvec3(0.0, 0.0, 0.0))
		{
			if(intersection != _ray->getStartingPoint())
			{
				if(glm::length(intersection - _ray->getStartingPoint()) < glm::length(finalIntersection - _ray->getStartingPoint()))
				{
					finalIntersection = intersection;
					intersectedNormal = sides[i]->getNormal();
					intersectedSide = i;
				}
			}
		}

		/* // HÄR

		// if intersection == glm::vec(0.0,0.0,0.0) then no intersection
		if( intersection == glm::dvec3(0.0, 0.0, 0.0) )
		{
			// std::cout << "				- NO INTERSECTIONS - " << std::endl;
		}
		if( intersection != glm::dvec3(0.0, 0.0, 0.0) )
		{
			// first detected intersection
			if(finalIntersection == glm::dvec3(0.0, 0.0, 0.0))
			{
				// std::cout << "Detected first intersection (";
				finalIntersection = intersection;

				// store which side was intersected
				side = i;
				// std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;
			}
			
			// second detected intersection
			else
			{
				// // std::cout << "Detected second intersection (";
				// // std::cout << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;
				
				// === message
				// // // std::cout << "sides[" << i << "].calculateIntersection(Ray* _ray) = " << intersection.x << ", " 
				// << intersection.y << ", " << intersection.z << std::endl;
				// === end message

				// Ray inside object
				if(_ray->isInsideObject())
				{
					// std::cout << "Ray inside object. ";
					if( glm::length(intersection - _ray->getStartingPoint()) > glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						// std::cout << "Choosing new intersection point (farther from ray origin - exit point)." << std::endl;
						side = i;
						finalIntersection = intersection;
					}
					else
					{
						// std::cout << "Discarding new intersection point (closer to ray origin - entry point)" << std::endl;
					}
				}
				// Ray outside object
				else
				{
					// std::cout << "Ray outside object. ";
					if( glm::length(intersection - _ray->getStartingPoint()) < glm::length(finalIntersection - _ray->getStartingPoint()) )
					{
						// std::cout << "Choosing new intersection point (closer to ray origin - entry point)." << std::endl;
						side = i;
						finalIntersection = intersection;
					}
					else
					{
						// std::cout << "Discarding new intersection point (farther from ray origin - exit point)" << std::endl;
					}
				}
			}			
		}
		*/
	}

	// if(side != 666)
	// {
	// 	// std::cout << "The side for the final intersection point is " << side << std::endl;
	// 	// std::cout << "The normal is " << sides[side]->getNormal().x << ", " << sides[side]->getNormal().y << ", " << sides[side]->getNormal().z << std::endl;
	// 	intersectedNormal = sides[side]->getNormal();
	// 	intersectedSide = side;
	// }
		
	
	/*
	//Fulkod
	double backBottomLeftX = sides[0]->positionsOfCorners[1].x;
	double backBottomLeftY = sides[0]->positionsOfCorners[1].y;
	double backBottomLeftZ = sides[0]->positionsOfCorners[1].z;

	// // // std::cout << "backBottomLeftX = " << backBottomLeftX << std::endl;
	// // // std::cout << "backBottomLeftY = " << backBottomLeftY << std::endl;
	// // // std::cout << "backBottomLeftZ = " << backBottomLeftZ << std::endl;

	double frontCeilRightX = sides[2]->positionsOfCorners[2].x;
	double frontCeilRightY = sides[2]->positionsOfCorners[2].y;
	double frontCeilRightZ = sides[2]->positionsOfCorners[2].z;

	// // // std::cout << "frontCeilRightX = " << frontCeilRightX << std::endl;
	// // // std::cout << "frontCeilRightY = " << frontCeilRightY << std::endl;
	// // // std::cout << "frontCeilRightZ = " << frontCeilRightZ << std::endl;

	// // // std::cout << "\n\n ======= finalIntersection ========\n\n";
	if( (finalIntersection.x >= backBottomLeftX && finalIntersection.y >= backBottomLeftY && finalIntersection.z >= backBottomLeftZ) && 
		(finalIntersection.x <= frontCeilRightX && finalIntersection.y <= frontCeilRightY && finalIntersection.z <= frontCeilRightZ) )
	{
		// then it is inside
		// // // std::cout << "finalIntersection = " << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << "\n\n";
		return finalIntersection;
	}
	// // // std::cout << "No finalIntersection\n\n";
	return glm::dvec3(0.0,0.0,0.0);
	*/
	// // std::cout << "Returning final intersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ")" << std::endl;

	return finalIntersection;
}

void Cube::calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint)				// TEMPORARY
{
	//intersectedNormal = glm::dvec3(0.0, 1.0, 0.0);
	glm::dvec3 testIntersectionPoint = (1000.0 * intersectionPoint + (1000.0 * 0.001 * intersectedNormal))/1000.0;
	// // std::cout << "\nCalculating child ray for intersection point " << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << std::endl << std::endl;
	// calculate direction for reflected or transmitted ray - WHITTED - (TEMPORARY)
	// // std::cout << "====== Reflection/refraction =====" << std::endl;
	glm::dvec3 reflectedRayDirection = glm::reflect(_ray->getDirection(), intersectedNormal);
	// // std::cout << "reflection = (" << reflectedRayDirection.x << ", " << reflectedRayDirection.y << ", " << reflectedRayDirection.z << ")" << std::endl;

	// glm::dvec3 refractedRayDirection = glm::refract(_ray->getDirection(), intersectedNormal, refractiveIndex);
	// // std::cout << "refraction = (" << refractedRayDirection.x << ", " << refractedRayDirection.y << ", " << refractedRayDirection.z << ")" << std::endl;

	_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance(), color, false);
}

/*
	Get functions
*/
glm::dvec3 Cube::getColor()
{
	return color;
}

glm::dvec3 Cube::getIntersectedNormal()
{
	return intersectedNormal;
}

int Cube::getIntersectedSide()
{
	return intersectedSide;
}

double Cube::getRefractiveIndex()
{
	return refractiveIndex;
}			




