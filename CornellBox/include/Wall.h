#ifndef WALL_H
#define WALL_H value

#include "glm/glm.hpp"
#include "Rectangle.h"
#include "Object.h"
#include "Ray.h"
#include <iostream>

class Wall : public Object
{
public:
	// Empty constructor
	Wall();

	// Constructor
	Wall(glm::vec3 _position, float _size, glm::vec3 _color, bool _diffuse, bool _transparent);
	
	// Destructor
	~Wall();

	// Intialize functions called by the constructor
	void initializeRectangles();							// sets corners of rectangles to (0,0,0),
															// (1,0,0), (0,1,0) etc. and multiplies
															// them by size (float) and adds the
															// position (glm::vec3)
	
	// Calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint);
	virtual glm::vec3 calculateIntersection(Ray* _ray);		// either one intersection or none (ray leaving)
	
	// Get functions
	virtual glm::vec3 getColor();
	virtual glm::vec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual float getRefractiveIndex();
	
	// Public variables
	Rectangle* walls[5];
	float size;

private:
	glm::vec3 intersectedNormal;
	int intersectedSide;
};

#endif