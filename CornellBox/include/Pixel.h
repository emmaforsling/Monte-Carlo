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
	void shootRays(glm::dvec3 _cameraPosition, int _raysPerPixel, glm::dvec3 _pixelPosition, double _pixelSize, Object** _objects, Light* _light);			// Should also track the rays
												// within the scene (tree structure?)
	// Free up memory function
	void clearMemory();

	// Get functions
	glm::dvec3 getColorOfPixel();

private:
	glm::dvec3 colorOfPixel;						// vec4 for alpha?
	glm::dvec3 position;
	static const int raysPerPixel = 1;
	Ray* rays[raysPerPixel];

};

#endif
