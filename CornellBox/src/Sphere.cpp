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
: Object(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0 ,0.0), false, false)
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
	glm::dvec3 testIntersectionPoint;
	glm::dvec3 newRayDirection;
	glm::dvec3 reflectedRayDirection;
	glm::dvec3 refractedRayDirection;
	bool refractedRayIsInside;
	glm::dvec3 direction = _ray->getDirection();	

	if(!transparent){
		testIntersectionPoint = (1000.0*intersectionPoint + (1000.0* 0.001 * intersectedNormal) )/1000.0;
		reflectedRayDirection = glm::reflect(glm::normalize(direction), glm::normalize(intersectedNormal));
		//glm::dvec3 test = _ray->reflectRay(direction, intersectedNormal);	// Kallar på den egna funktionen
		_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance(), color, false);
		_ray->refractedRay = nullptr;
	}
	if(transparent)
	{
		// Refraction
		bool reflectedRayIsInside;
		double n1 = 1.0;
		double n2 = refractiveIndex;
		double cosTheta1;
		if(_ray->isInsideObject())
		{
			if(_ray->getIteration() == 2)
			{
				//std::cout << "Direction of ray: (" << _ray->getDirection().x << ", " << _ray->getDirection().y << ", " << _ray->getDirection().z << ")" << std::endl;
			}

			n1 = refractiveIndex;
			n2 = 1.0;
			// Flip normals
			intersectedNormal = -intersectedNormal;
			testIntersectionPoint = (1000.0*intersectionPoint + (1000.0 * 0.001 * intersectedNormal) )/1000.0;
			refractedRayDirection = glm::refract(direction, intersectedNormal, refractiveIndex); // test, ska tas bort
			cosTheta1 = glm::dot(intersectedNormal, -direction);
			if(cosTheta1<0){
				std::cout << "========= WRONG     1 ==========";
				cosTheta1 = glm::dot(intersectedNormal, direction);
			}
			else{
				//std::cout << "är jag hääääääääääääääääääääääääääääääääär 1?" << std::endl;
			}
		}
		else{
			testIntersectionPoint = (1000.0*intersectionPoint + (1000.0 * 0.001 * intersectedNormal) )/1000.0;
			refractedRayDirection = glm::refract(direction, intersectedNormal, 1.0/refractiveIndex); // test, ska tas bort
			cosTheta1 = glm::dot(intersectedNormal, -direction);
			if(cosTheta1<0){
				std::cout << "========= WRONG 2 ==========";
				cosTheta1 = glm::dot(intersectedNormal, direction);
			}
			else{
				//std::cout << "är jag hääääääääääääääääääääääääääääääääär2 ?" << std::endl;
			}
		}


		double n = n1/n2;	
		//double cosTheta1 = glm::dot(intersectedNormal, direction);
		double cosTheta2 = 1.0 - n * n * (1.0 - cosTheta1 * cosTheta1);
		//double sinT2 = 1.0 - n * n * (1.0 - cosTheta1 * cosTheta1); // tim

		if(cosTheta2 >= 0.0){
			//refractedRayDirection = n * direction - (n * cosTheta1 + (double)sqrt(cosTheta2)) * -intersectedNormal; //tims
			refractedRayDirection = n * direction + (n * cosTheta1 - (double)sqrt(cosTheta2)) * intersectedNormal; // min			
			if(_ray->isInsideObject()){
                refractedRayIsInside = false;
                reflectedRayIsInside = true;
            }else{
            	reflectedRayIsInside = false;
                refractedRayIsInside = true;
            }
            reflectedRayDirection = glm::reflect(glm::normalize(direction), glm::normalize(intersectedNormal));
		//glm::dvec3 test = _ray->reflectRay(direction, intersectedNormal);	// Kallar på den egna funktionen
			_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance()/16.0, color, false);
			_ray->refractedRay = new Ray(testIntersectionPoint, refractedRayDirection, (15.0 * _ray->getImportance())/16.0, color, refractedRayIsInside);	
		/* smallpt*/
			// refractedRayDirection = n * direction - (n * cosTheta1 + (double)sqrt(sinT2)) * -intersectedNormal; //tims
			// double a = 1.5 - 1.0; 	// n1 n2
			// double b = 1.5 + 1.0;	// n1 n2
			// double R0 = a * a / (b*b);
			// bool into = _ray->isInsideObject();
			// double c = (1 - into) ? (- cosTheta1) : glm::dot(refractedRayDirection, intersectedNormal);
			// double Re = R0 + (1-R0) * c * c * c * c * c;
			// double Tr = 1 - Re;
			// double P = 0.25 + 0.5 * Re;
			// double Rp = Re/P;
			// double Tp = Tr/(1-P);

			// int depth = _ray->getIteration();
			// if(_ray->getImportance() + (color * depth) > 2)
			// {
			// 	if(erand48(1)<P){

			// 	}
			// }


			//  double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
			//  return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette
   //   		radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) :
   // 			 radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr);
			//_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance()/2.0, color, reflectedRayIsInside);		

			//_ray->setIsRefractedRay(true);
		}
		else{ // if(cosTheta2 < 0) - total internal reflection
			intersectedNormal = -intersectedNormal;
			testIntersectionPoint = (1000.0*intersectionPoint + (1000.0* 0.001 * intersectedNormal) )/1000.0;
			reflectedRayDirection = glm::reflect(glm::normalize(direction), glm::normalize(intersectedNormal));
			//glm::dvec3 test = _ray->reflectRay(direction, intersectedNormal);	// Kallar på den egna funktionen
			//_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance(), color, _ray->isInsideObject());
			_ray->reflectedRay = nullptr;
			//_ray->refractedRay = new Ray(testIntersectionPoint, refractedRayDirection, _ray->getImportance(), color, refractedRayIsInside);	
			//std::cout << "================TOTAL INTERNAL REFLECTION ???????????????==============\n\n\n";
			//_ray->refractedRay = nullptr;
		}
		//_ray->reflectedRay = nullptr;
		//reflectedRayDirection = direction - 2 * cosTheta1 * intersectedNormal;	// mine
		//glm::dvec3 reflectedDirection = -1.0 * (2.0 * (glm::dot(intersectedNormal,direction) * intersectedNormal) - direction); //tim
		//reflectedRayDirection = glm::reflect(glm::normalize(direction), glm::normalize(intersectedNormal));
		//_ray->reflectedRay = new Ray(testIntersectionPoint, reflectedRayDirection, _ray->getImportance()/2.0, color, reflectedRayIsInside);	
	
		

		//
		
		/*
		glm::dvec3 reflectedDirection = -1.0 * (2.0 * (glm::dot(intersectionNormal,inDirection) * intersectionNormal) - inDirection);
		*/
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


