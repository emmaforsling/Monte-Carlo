#ifndef CUBE_H
#define CUBE_H value

#include "glm/glm.hpp"
#include "Rectangle.h"

class Cube
{
public:
	Cube();
	Cube(glm::vec3 _position, float _size, float _transparency, float _refractiveIndex);
	~Cube();
	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	void calculateChildRays();
	glm::vec3 calculateIntersection(Ray* ray); 

private:
	Rectangle* sides[6];
	glm::vec3 position;
	float size;
	float transparency;
	float refractiveIndex;
};

#endif