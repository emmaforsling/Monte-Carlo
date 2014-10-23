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
	Camera();
	Camera(Wall* _room, float _eyeDistance, int _raysPerPixel);
	~Camera();
	void renderImage(Object** _objects, Light* _light);		// - Loops over all pixels and computes
															//   their values.
	void mappingFunction();									// - Converts radiometric values into
															//   photometric ones.
	void saveImage();										// - Alternatively displayImage()

private:
	glm::vec3 position;
	glm::vec3 direction;
	float viewPlaneDistance;
	
	const int viewPlaneSizeX = 1;
	const int viewPlaneSizeY = 1;
	
	static const int resolutionX = 1080;
	static const int resolutionY = 1080;
	
	int raysPerPixel;
	Pixel* pixels[resolutionX * resolutionY];

	float clamp(float _x);
	int toInt(float _x);
};

#endif
