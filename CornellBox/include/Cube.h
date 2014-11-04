#ifndef CUBE_H
#define CUBE_H value

#include "glm/glm.hpp"
#include "Rectangle.h"
#include "Object.h"
#include "Ray.h"

class Cube : public Object
{
public:
	// Empty constructor
	Cube();

	// Constructor
	Cube(glm::dvec3 _position, double _size, bool _transparent, double _refractiveIndex, glm::dvec3 _color, bool _diffuse);
	
	// Default destructor
	~Cube() = default;

	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (double) and adds the
												// position (glm::dvec3)
	
	// Calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint);
	virtual glm::dvec3 calculateIntersection(Ray* _ray);

	// Get functions
	virtual glm::dvec3 getColor();
	virtual glm::dvec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual double getRefractiveIndex();




private:
	Rectangle* sides[6];
	double size;
	double refractiveIndex;

	glm::dvec3 intersectedNormal;
	int intersectedSide;
};

#endif