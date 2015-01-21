#include "../include/Sphere.h"
#include <iostream>
/* 	
	Class Sphere  
	
	private members:
	- glm::dvec3 position;
	- double radius;
	- double transparency;
	- double refractiveIndex;
*/

/* 
	Emtpy constructor
*/
Sphere::Sphere()
: Object(glm::dvec3(0.0,0.0,0.0), glm::dvec3(0.0,0.0,0.0), false, false)
{
	radius = 0.0;
	refractiveIndex = 0.0;
	intersectedNormal = glm::dvec3(0.0,0.0,0.0);
}

/*
	Constructor
*/
Sphere::Sphere(glm::dvec3 _position, double _radius, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse)
: Object(_position, _color, _diffuse, _transparent)
{
	color = _color;
	radius = _radius;
	refractiveIndex = _refractiveIndex;
}
/*
	Calculation functions
*/
glm::dvec3 Sphere::calculateIntersection(Ray* _ray, bool _isShadowRay)
{
	//glm::dvec3 direction2 = _ray->getDirection();
	//std::cout << "\tSphere::calculateIntersection(), incoming direction of ray = (" << direction2.x << ", " << direction2.y << ", " << direction2.z << std::endl;
	
	/*
	This function should calculate the intersectionpoints between a ray 
	and the surface of the Sphere.

		Using the equations:
			S: r^2 = x^2 + y^2 + z^2		
			R = t*(x,y,z)
			where 
			t = direction

			The equation is then rewritten into this:

			a = (direction.x)^2 + (direction.y)^2 + (direction.z)^2;
			b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
					(direction.y)*(startingPoint.y - centerPoint.y) +
					(direction.z)*(startingPoint.z - centerPoint.z));
			c = (startingPoint.x - centerPoint.x)^2 +
				(startingPoint.y - centerPoint.y)^2 +
				(startingPoint.z - centerPoint.z)^2;

			then
			delta = b^2 + 4*a*c;

			if(delta<0) no intersection
			if(delta==0) one intersection
			if(delta>0) two intersection
	*/

	// Initializing the variables
	double a = 0.0, b = 0.0, c = 0.0;
	double delta = 0.0, t = 0.0, t1 = 0.0, t2 = 0.0;
	glm::dvec3 finalIntersection = glm::dvec3(0.0, 0.0, 0.0);

	// Get the startingPoint for the ray
	glm::dvec3 startingPoint = _ray->getStartingPoint();

	// Get the direction for the ray
	glm::dvec3 direction = glm::normalize(_ray->getDirection());
	// std::cout << "direction " << direction.x << ", " << direction.y << ", " << direction.z << std::endl; 
	//if(glm::length(direction) == 0)
		//std::cout << "EMMMMMMMMMAAAAAA" << std::endl;
	// Set the centerPoint for the sphere to the position given as an argument to the constructor
	glm::dvec3 centerPoint = position;
	
	// Calculate a, b and c
	a = 1.0;//(direction.x)*(direction.x) + (direction.y)*(direction.y) + (direction.z)*(direction.z);
	b = 2*( (direction.x)*(startingPoint.x - centerPoint.x) + 
			(direction.y)*(startingPoint.y - centerPoint.y) +
			(direction.z)*(startingPoint.z - centerPoint.z) );
	c = (startingPoint.x - centerPoint.x)*(startingPoint.x - centerPoint.x) +
		(startingPoint.y - centerPoint.y)*(startingPoint.y - centerPoint.y) +
		(startingPoint.z - centerPoint.z)*(startingPoint.z - centerPoint.z)
		- radius*radius;
	
	// Calculate delta
	delta = b*b - 4*a*c;
		
	if(delta<0)										// No intersection
	{	
		if(!_isShadowRay)
		{
			intersectedNormal = glm::dvec3(0.0,0.0,0.0);
		}
		//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta < 0)" << std::endl;
		
		return finalIntersection;
	}
	else if(delta == 0)								// Single intersection
	{
		t = -b/(2*a);
		finalIntersection = startingPoint + t * direction;
		if(!_isShadowRay)
		{
			intersectedNormal = glm::normalize(finalIntersection - centerPoint);
		}
		//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta == 0)" << std::endl;
		// std::cout << "1. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;
		return finalIntersection; //returns the point where it intersects
	}
	else //if(delta>0)								// Two intersections
	{
		
		t1 = (-b - sqrt(delta))/(2*a);
		t2 = (-b + sqrt(delta))/(2*a);

		double min_t = std::min(t1,t2);
		double max_t = std::max(t1,t2);

		if(_ray->isInsideObject())
		{

			if(max_t > 0)
			{
				finalIntersection = (1000.0 * startingPoint + 1000.0 * max_t * direction)/1000.0;		
			}
			else
			{
				// do nothing
			}
			//std::cout << "Ray inside object!" << std::endl;
			
			if(!_isShadowRay)
			{
				intersectedNormal = glm::normalize(finalIntersection - centerPoint);
			}
			//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta > 0 + inside)" << std::endl;
			//std::cout << "I'm inside!" << std::endl;
			// std::cout << "2. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;
			return finalIntersection;
		}	
		else
		{	
			//if(_ray->isRefractedRay()){
			//	finalIntersection = (1000.0 * startingPoint + 1000.0 * max_t * direction)/1000.0;	
			//}
			//else{
				// if the smallest value of t (t_min) is positive, it corresponds to the closest point in the positive direction of the ray,
				// which is the point of interest.
				if(min_t > 0.0)
				{
					finalIntersection = (1000.0 * startingPoint + 1000.0 * min_t * direction)/1000.0;
				}
				// if the smallest value of t (t_min) is zero, it corresponds to the ray origin, which is not of intersest. Instead,
				// the greatest value (max_t), which corresponds to a point farther along the ray direction, is of interest.
				else if(min_t == 0)
				{
					finalIntersection = (1000.0 * startingPoint + 1000.0 * max_t * direction)/1000.0;
				}
				// if the smallest value of t is negative, it corresponds to a point along the negative ray direction,
				// which never is of interest.
				else{
					// do nothing
				}
			//}
			/* ====== En annan variant... ======
			t = (-b + sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
				finalIntersection = startingPoint + (direction * t);
			}
			
			t = (-b - sqrt((b * b) - (4 * c)))/2;
			if(t > 0){
				finalIntersection = startingPoint + (direction * t);
			}
			===================================*/

			// if the incoming ray is not a shadow ray, update intersectedNormal.
			if(!_isShadowRay)
			{
				intersectedNormal = glm::normalize(finalIntersection - centerPoint);
			}
			//std::cout << "finalIntersection: (" << finalIntersection.x << ", " << finalIntersection.y << ", " << finalIntersection.z << ") (delta > 0 + outside)" << std::endl;
			// std::cout << "3. Är sfärens punkt rätt så att längden blir 1? Svar: Längd = " << glm::length(finalIntersection - centerPoint) << std::endl;

			return finalIntersection;
		}			
	}
}

void Sphere::calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint)				// TEMPORARY
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
	
	glm::dvec3 incidentRay = _ray->getDirection();					// I

	double cosTheta1;												// cos(t1)
	double importance = _ray->getImportance();						// Importance for the incident ray


	bool incidentRayIsInside = _ray->isInsideObject();
	bool refractedRayIsInside = incidentRayIsInside ? false : true;	// If the incident ray is inside, then the refractive ray will be outside
	bool reflectedRayIsInside = incidentRayIsInside;				// If the incident ray is inside, then the reflective ray will be so as well

	// Reflection
	intersectedNormal = incidentRayIsInside ? -intersectedNormal : intersectedNormal; 	// if inside object, flip the normal
	testIntersectionPoint = (1000.0*intersectionPoint + (1000.0* 0.001 * intersectedNormal) )/1000.0;
	
	cosTheta1 = glm::dot(intersectedNormal, incidentRay);
	cosTheta1 = cosTheta1 < 0 ? -cosTheta1 : cosTheta1;							// If cos(t1) < 0, set it to -cos(t1)

	reflectedRayDirection = incidentRay + 2.0 * cosTheta1 * intersectedNormal;	// Calculate the direction for the reflected ray
	_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, importance, color, reflectedRayIsInside);

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
			refractedRayDirection = n * incidentRay + (n * cosTheta1 - (double)sqrt(cosTheta2)) * intersectedNormal; // min
			_ray->refractedRay = new Ray(testIntersectionPoint, refractedRayDirection, importance * refractionRatio, color, refractedRayIsInside);	
			_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, importance * reflectanceRatio, color, reflectedRayIsInside);
		}
	}
}

/*
	Get functions
*/
glm::dvec3 Sphere::getColor()
{
	return color;
}

glm::dvec3 Sphere::getIntersectedNormal()
{
	return intersectedNormal;
}

int Sphere::getIntersectedSide()
{
	intersectedSide = 666;
	return intersectedSide;
}

double Sphere::getRefractiveIndex()
{
	return refractiveIndex;
}

/*
	Set functions
*/
void Sphere::setIntersectedNormal(glm::dvec3 _intersectedNormal)
{
	intersectedNormal = _intersectedNormal;
}


