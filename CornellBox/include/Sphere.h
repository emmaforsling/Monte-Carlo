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
	Sphere(glm::vec3 _position, float _radius, bool _transparent, float _refractiveIndex, glm::vec3 _color, bool _diffuse);
	
	// Default destructor
	~Sphere() = default;
	
	// Calculation functions
	virtual glm::vec3 calculateIntersection(Ray* _ray);
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint);

	// Get functions
	virtual glm::vec3 getColor();
	virtual glm::vec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual float getRefractiveIndex();

	// Set functions 
	void setIntersectedNormal(glm::vec3 _intersectedNormal);

private:
	float radius;				
	float refractiveIndex;		//glass = 1.5, air = 1.0

	glm::vec3 intersectedNormal;
	int intersectedSide;
};

#endif
