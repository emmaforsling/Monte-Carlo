#ifndef OBJECT_H
#define OBJECT_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Object
{
public:
	Object();
	~Object();
	virtual glm::vec3 calculateIntersection(Ray* _ray) = 0;

private:
	// glm::vec3 position;
};

#endif
