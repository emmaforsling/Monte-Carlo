#ifndef PIXEL_H
#define PIXEL_H value

#include "glm/glm.hpp"
#include "Ray.h"
#include "Object.h"
#include "Light.h"

#include <stdlib.h>
#include <time.h>

class Pixel
{
public:
	Pixel();
	Pixel(int _raysPerPixel);
	~Pixel();
	void shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects, Light* _light);			// Should also track the rays
												// within the scene (tree structure?)
	void clearMemory();
	glm::vec3 getColorOfPixel();

private:
	static const int raysPerPixel = 32;
	Ray* rays[raysPerPixel];
	glm::vec3 colorOfPixel;						// vec4 for alpha?
	glm::vec3 position;
};

#endif
