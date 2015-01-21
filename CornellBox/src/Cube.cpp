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
	
}

/*
	Calculation functions
*/
glm::dvec3 Cube::calculateIntersection(Ray* _ray, bool _isShadowRay) 
{
	glm::dvec3 intersection;
	glm::dvec3 finalIntersection = glm::dvec3(0.0,0.0,0.0);

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

	/*
		This function calculates the reflection (and refraction for transparent objects)
	   I   N   R
		\t1|t'/				where 
	n1	 \-|-/						t1 		- angle between incident ray, I, and the normal N.
		-----						t' 		- angle between the normal, N, and the reflected ray R 
	n2	   |-\							 	  (and for perfect reflection t' = t1)
		   |t2\						t2 		- angle between the normal, N, and the refracted ray T
		       T 					n1,n2  	- refractive indicies

		To calculate the reflection, following equations have been used (in vector form):
			cos(t1) = dot(N, -I)		(where cos(t1) > 0 (if < 0 set it to -cos(t1) ) ) 
			Vreflect = I + 2.0 * cos(t1) * n

		To calculate the refraction, following equations have been used (in vector form):
			n = n1/n2 
			cos(t2) = 1.0 - n * n * (1.0 - cos(t1) * cos(t1) );
	*/
	

	glm::dvec3 testIntersectionPoint;								// A temporary intersection point is used, in which the point is either
																	// moved inwards or outwards in the normal direction, in order to avoid 
																	// that the new ray is created on the wrong side of the sphere
	
	glm::dvec3 reflectedRayDirection;								// R		
	glm::dvec3 refractedRayDirection;								// T
	
	glm::dvec3 incidentRayDirection = _ray->getDirection();					// I

	double cosTheta1;												// cos(t1)
	double importance = _ray->getImportance();						// Importance for the incident ray
	

	bool incidentRayIsInside = _ray->isInsideObject();
	bool refractedRayIsInside = incidentRayIsInside ? false : true;	// If the incident ray is inside, then the refractive ray will be outside
	bool reflectedRayIsInside = incidentRayIsInside;				// If the incident ray is inside, then the reflective ray will be so as well

	if(intersectedNormal == glm::dvec3(0.0,-1.0,0.0))
		// std::cout << "intersectedNormal : " << intersectedNormal.x << ", " << intersectedNormal.y << ", " << intersectedNormal.z << std::endl;
	// Reflection
	intersectedNormal = incidentRayIsInside ? -intersectedNormal : intersectedNormal; 	// if inside object, flip the normal
	testIntersectionPoint = (1000.0*intersectionPoint + (1000.0* 0.001 * intersectedNormal) )/1000.0;
	
	cosTheta1 = glm::dot(intersectedNormal, incidentRayDirection);
	cosTheta1 = cosTheta1 < 0 ? -cosTheta1 : cosTheta1;							// If cos(t1) < 0, set it to -cos(t1)

	reflectedRayDirection = incidentRayDirection + 2.0 * cosTheta1 * intersectedNormal;	// Calculate the direction for the reflected ray


	/* Fultest */

	double PI = 3.14159265358979323846;
	double randomAngle1 =  0.025 * PI * (static_cast <double>(rand()) / static_cast<double>(RAND_MAX) - 0.5);
	double randomAngle2 =  0.025 * PI * (static_cast <double>(rand()) / static_cast<double>(RAND_MAX) - 0.5);

	double randomNumber = static_cast <double>(rand()) / static_cast<double>(RAND_MAX);

	// left
	if(intersectedNormal == glm::dvec3(1.0, 0.0, 0.0))
	{
		reflectedRayDirection = glm::rotateY(reflectedRayDirection, randomAngle1);
		reflectedRayDirection = glm::rotateZ(reflectedRayDirection, randomAngle2);
	}
	
	// top
	else if(intersectedNormal == glm::dvec3(0.0, -1.0, 0.0))
	{
		reflectedRayDirection = glm::rotateX(reflectedRayDirection, randomAngle1);
		reflectedRayDirection = glm::rotateZ(reflectedRayDirection, randomAngle2);
	}
	
	// right
	else if(intersectedNormal == glm::dvec3(-1.0, 0.0, 0.0))
	{
		reflectedRayDirection = glm::rotateY(reflectedRayDirection, randomAngle1);
		reflectedRayDirection = glm::rotateZ(reflectedRayDirection, randomAngle2);
	}
	
	// bottom
	else if(intersectedNormal == glm::dvec3(0.0, 1.0, 0.0))
	{
		reflectedRayDirection = glm::rotateX(intersectedNormal, randomAngle1);
		reflectedRayDirection = glm::rotateZ(reflectedRayDirection, randomAngle2);
	}
	
	// back
	else if(intersectedNormal == glm::dvec3(0.0, 0.0, 1.0))
	{
		reflectedRayDirection = glm::rotateX(reflectedRayDirection, randomAngle1);
		reflectedRayDirection = glm::rotateY(reflectedRayDirection, randomAngle2);
	}

	glm::dvec3 eyePosition = glm::dvec3(2.5, 2.5, 9.0);
	glm::dvec3 directionToEye = glm::normalize(eyePosition - testIntersectionPoint);
	double cosineOfAngle = glm::dot(directionToEye, reflectedRayDirection);
	if(cosineOfAngle > 1.0)
	{
		cosineOfAngle = 1.0;
	}
	if(cosineOfAngle < 0.0)
	{
		cosineOfAngle = 0.0;
	}
	double importanceWeight = pow(cosineOfAngle, 20.0);
	double test = std::max(2.0,50.0);
	//std::cout << "testar max = " << test << std::endl;

	_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, importance * importanceWeight, color, reflectedRayIsInside);

	/* slut */


	//_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, importance, color, reflectedRayIsInside);

	// Refraction
	if(transparent)
	{
		double n1 = incidentRayIsInside ? refractiveIndex : 1.0;				// Refractive index n1
		double n2 = incidentRayIsInside ? 1.0 : refractiveIndex;				// Refractive index n2
		double n = n1/n2;		
		double cosTheta2 = 1.0 - n * n * (1.0 - cosTheta1 * cosTheta1);

		double reflectanceRatio = (pow(n1-n2,2.0))/(pow(n1+n2,2.0));
		double refractionRatio = 1.0 - reflectanceRatio;
		if(cosTheta2 >= 0.0)
		{
			refractedRayDirection = n * incidentRayDirection + (n * cosTheta1 - (double)sqrt(cosTheta2)) * intersectedNormal; // min
			_ray->refractedRay = new Ray(testIntersectionPoint, refractedRayDirection, importance * refractionRatio, color, refractedRayIsInside);	
			_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, importance * reflectanceRatio, color, reflectedRayIsInside);
		}
	}
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




