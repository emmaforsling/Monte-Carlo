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
	glm::dvec3 calculateIntersection(Ray* _ray);
	
	// Get functions
	glm::dvec3 getColor();
	glm::dvec3 getNormal();

	// Set functions
	void setColor(glm::dvec3 _color);
	
	// Public variables
	glm::dvec3 positionsOfCorners[4];


private:
	double A, B, C, D;
	glm::dvec3 color;
	glm::dvec3 normal;

};

#endif
