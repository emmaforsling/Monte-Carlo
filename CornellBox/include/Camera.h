#ifndef CAMERA_H
#define CAMERA_H value

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#include "glm/glm.hpp"
#include "Pixel.h"
#include "Wall.h"
#include "Light.h"

//#include <omp.h>

class Camera
{
public:
	// Empty constructor
	Camera();

	// Constructor
	Camera(Wall* _room, float _eyeDistance, int _raysPerPixel);
	
	// Destructor
	~Camera();

	// Image functions
	void renderImage(Object** _objects, Light* _light);		// - Loops over all pixels and computes
															//   their values.
	void saveImage();										
	void mappingFunction();									// - Converts radiometric values into
															//   photometric ones.
private:
	glm::vec3 direction;
	glm::vec3 position;
	
	float viewPlaneDistance;
	
	const int viewPlaneSizeX = 1;
	const int viewPlaneSizeY = 1;
	
	static const int resolutionX = 300;
	static const int resolutionY = 300;
	
	int raysPerPixel;
	Pixel* pixels[resolutionX * resolutionY];

	// private functions, used when to save the image
	float clamp(float _x);
	int toInt(float _x);
};

#endif
