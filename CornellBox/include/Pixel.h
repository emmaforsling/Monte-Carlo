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
	// Empty constructor
	Pixel();

	// Constructor
	Pixel(int _raysPerPixel);
	
	// Destructor
	~Pixel();

	// ShootRay function
	void shootRays(glm::vec3 _cameraPosition, int _raysPerPixel, glm::vec3 _pixelPosition, float _pixelSize, Object** _objects, Light* _light);			// Should also track the rays
												// within the scene (tree structure?)
	// Free up memory function
	void clearMemory();

	// Get functions
	glm::vec3 getColorOfPixel();

private:
	glm::vec3 colorOfPixel;						// vec4 for alpha?
	glm::vec3 position;
	static const int raysPerPixel = 48;
	Ray* rays[raysPerPixel];

};

#endif
