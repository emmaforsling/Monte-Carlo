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
	Object(glm::vec3 _position, glm::vec3 _color, bool _diffuse, bool _transparent);
	
	// Default destructor
	~Object() = default;

	// Virtual calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint) = 0;
	virtual glm::vec3 calculateIntersection(Ray* _ray) = 0;
	
	// Virtual get functions
	virtual glm::vec3 getColor() = 0;
	virtual glm::vec3 getIntersectedNormal() = 0;
	virtual int getIntersectedSide() = 0;
	virtual float getRefractiveIndex() = 0;
	
	// Bool functions
	bool isDiffuse();
	bool isTransparent();

protected:
	glm::vec3 color;
	glm::vec3 position;
	bool diffuse;
	bool transparent;
};

#endif
