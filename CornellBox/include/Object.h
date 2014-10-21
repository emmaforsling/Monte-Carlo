#ifndef OBJECT_H
#define OBJECT_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Object
{
public:
	Object();
	Object(glm::vec3 _position);
	~Object();
	virtual glm::vec3 calculateIntersection(Ray* _ray) = 0;
	virtual void calculateChildRays(glm::vec3 _intersectionPoint) = 0;
	virtual float getRefractiveIndex() = 0;
	virtual glm::vec3 getIntersectedNormal() = 0;
protected:
	glm::vec3 position;
};

#endif
