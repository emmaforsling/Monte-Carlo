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
	Camera(Wall* _room, double _eyeDistance);
	
	// Destructor
	~Camera();

	// Image functions
	void renderImage(Object** _objects, Light* _light);		// - Loops over all pixels and computes
															//   their values.
	void saveImage();																		
private:
	glm::dvec3 direction;
	glm::dvec3 position;
	
	double viewPlaneDistance;
	
	const int viewPlaneSizeX = 1;
	const int viewPlaneSizeY = 1;
	
	static const int resolutionX = 1000;
	static const int resolutionY = 1000;
	
	Pixel* pixels[resolutionX * resolutionY];

	// private functions, used when to save the image
	int toInt(double _x);		// - Converts radiometric values into
								//   photometric ones.
};

#endif
