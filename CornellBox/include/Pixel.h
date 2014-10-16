#ifndef PIXEL_H
#define PIXEL_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Pixel
{
public:
	Pixel();
	Pixel(int _raysPerPixel);
	~Pixel();
	void shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize);			// Should also track the rays
												// witin the scene (tree structure?)
private:
	static const int raysPerPixel = 4;
	Ray* rays[raysPerPixel];
	glm::vec3 colorOfPixel;						// vec4 for alpha?
	glm::vec3 position;
};

#endif
