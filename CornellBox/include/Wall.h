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
	Wall();
	Wall(glm::vec3 _position, float _size);
	~Wall();
	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	virtual void calculateChildRays(glm::vec3 _intersectionPoint);
	virtual glm::vec3 calculateIntersection(Ray* _ray);			// either one intersection or none (ray leaving)
	virtual float getRefractiveIndex();
	virtual glm::vec3 getIntersectedNormal();
	
	Rectangle* walls[5];
	float size;

private:
	glm::vec3 intersectedNormal;
};

#endif