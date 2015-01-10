#ifndef WALL_H
#define WALL_H value
#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "Rectangle.h"
#include "Object.h"
#include "Ray.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

class Wall : public Object
{
public:
	// Empty constructor
	Wall();

	// Constructor
	Wall(glm::dvec3 _position, double _size, glm::dvec3 _color, bool _diffuse, bool _transparent);
	
	// Destructor
	~Wall();

	// Intialize functions called by the constructor
	void initializeRectangles();							// sets corners of rectangles to (0,0,0),
															// (1,0,0), (0,1,0) etc. and multiplies
															// them by size (double) and adds the
															// position (glm::dvec3)
	
	// Calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::dvec3 intersectionPoint);
	virtual glm::dvec3 calculateIntersection(Ray* _ray, bool _isShadowRay);		// either one intersection or none (ray leaving)
	
	// Get functions
	virtual glm::dvec3 getColor();
	virtual glm::dvec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual double getRefractiveIndex();
	
	// Public variables
	Rectangle* walls[5];
	double size;

private:
	glm::dvec3 intersectedNormal;
	int intersectedSide;
};

#endif