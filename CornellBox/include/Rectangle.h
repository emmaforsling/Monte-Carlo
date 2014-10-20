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

	void setColor(glm::vec3 _color);
	glm::vec3 getColor();
	glm::vec3 getNormal();


private:
	float A, B, C, D;
	glm::vec3 color;
	glm::vec3 normal;

};

#endif