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
	void shootRays(glm::dvec3 _cameraPosition, glm::dvec3 _pixelPosition, double _pixelSize, Object** _objects, Light* _light);			// Should also track the rays
												// within the scene (tree structure?)
	// Cast shadow ray
	bool castShadowRay(glm::dvec3 _randomPositionOnLightSource, glm::dvec3 _intersection, Object** _objects, int _numberOfObjects);
	// Free up memory function
	void clearMemory();

	// Get functions
	glm::dvec3 getColorOfPixel();

	// Public variables
	static const int raysPerPixel = 1;

private:
	glm::dvec3 colorOfPixel;						// vec4 for alpha?
	glm::dvec3 position;
	Ray* rays[raysPerPixel];

};

#endif
