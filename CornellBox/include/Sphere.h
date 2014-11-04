#ifndef SPHERE_H
#define SPHERE_H value

#include "glm/glm.hpp"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
	// Empty constructor
	Sphere();

	// Constructor 
	Sphere(glm::dvec3 _position, double _radius, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse);
	
	// Default destructor
	~Sphere() = default;
	
	// Calculation functions
	virtual glm::dvec3 calculateIntersection(Ray* _ray, bool _isShadowRay);
	virtual void calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint);

	// Get functions
	virtual glm::dvec3 getColor();
	virtual glm::dvec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual double getRefractiveIndex();

	// Set functions 
	void setIntersectedNormal(glm::dvec3 _intersectedNormal);

private:
	double radius;				
	double refractiveIndex;		//glass = 1.5, air = 1.0

	glm::dvec3 intersectedNormal;
	int intersectedSide;
};

#endif
