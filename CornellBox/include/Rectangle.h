#ifndef RECTANGLE_H
#define RECTANGLE_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Rectangle
{
public:
	Rectangle();
	~Rectangle();
	glm::vec3 calculateIntersection(Ray* ray);
	void calculateChildRays();					// only called on cube

	glm::vec3 positionsOfCorners[4];

private:
	
};

#endif