#ifndef OBJECT_H
#define OBJECT_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Object
{
public:
	// Default empty constructor
	Object() = default;

	// Constructur
	Object(glm::dvec3 _position, glm::dvec3 _color, bool _diffuse, bool _transparent);
	
	// Default destructor
	~Object() = default;

	// Virtual calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint) = 0;
	virtual glm::dvec3 calculateIntersection(Ray* _ray, bool _isShadowRay) = 0;
	
	// Virtual get functions
	virtual glm::dvec3 getColor() = 0;
	virtual glm::dvec3 getIntersectedNormal() = 0;
	virtual int getIntersectedSide() = 0;
	virtual double getRefractiveIndex() = 0;
	
	// Bool functions
	bool isDiffuse();
	bool isTransparent();

protected:
	glm::dvec3 color;
	glm::dvec3 position;
	bool diffuse;
	bool transparent;
};

#endif
