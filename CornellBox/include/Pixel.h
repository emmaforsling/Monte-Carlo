#ifndef PIXEL_H
#define PIXEL_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Pixel
{
public:
	Pixel();
	Pixel(int raysPerPixel);
	~Pixel();
	void shootRays();							// Should also track the rays
												// witin the scene (tree structure?)
private:
	Ray* rays;
	glm::vec3 colorOfPixel;						// vec4 for alpha?
};


#endif