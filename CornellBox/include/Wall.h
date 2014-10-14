#ifndef WALL_H
#define WALL_H value

#include "glm/glm.hpp"
#include "Rectangle.h"
#include <iostream>

class Wall
{
public:
	Wall();
	Wall(glm::vec3 _position, float _size);
	~Wall();
	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	glm::vec3 calculateIntersection();			// either one intersection or none (ray leaving)

	Rectangle* walls[5];

private:
	glm::vec3 position;
	float size;
};

#endif