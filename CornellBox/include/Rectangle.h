#ifndef RECTANGLE_H
#define RECTANGLE_H value

#include "glm/glm.hpp"
#include "Ray.h"


class Rectangle
{
public:
	// Empty constructor
	Rectangle();

	// Destructor
	~Rectangle();

	// Calculation functions
	void calculateChildRays();					// only called on cube
	glm::vec3 calculateIntersection(Ray* ray);
	
	// Get functions
	glm::vec3 getColor();
	glm::vec3 getNormal();

	// Set functions
	void setColor(glm::vec3 _color);
	
	// Public variables
	glm::vec3 positionsOfCorners[4];


private:
	float A, B, C, D;
	glm::vec3 color;
	glm::vec3 normal;

};

#endif
