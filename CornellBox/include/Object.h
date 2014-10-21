#ifndef OBJECT_H
#define OBJECT_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Object
{
public:
	Object();
	Object(glm::vec3 _position, glm::vec3 _color);
	~Object();
	virtual glm::vec3 calculateIntersection(Ray* _ray) = 0;
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint) = 0;
	virtual float getRefractiveIndex() = 0;
	virtual glm::vec3 getIntersectedNormal() = 0;

	virtual int getIntersectedSide() = 0;
	
	virtual glm::vec3 getColor() = 0;
protected:
	glm::vec3 position;
	glm::vec3 color;
};

#endif
