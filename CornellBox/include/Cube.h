#ifndef CUBE_H
#define CUBE_H value

#include "glm/glm.hpp"

class Cube
{
public:
	Cube();
	~Cube();
	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	void calculateChildRays();

private:
	Rectangle* sides[6];
	glm::vec3 position;
	float size;
	float transparency;
	float refractiveIndex;
};

#endif