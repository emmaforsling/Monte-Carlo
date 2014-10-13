#ifndef CAMERA_H
#define CAMERA_H value

#include "glm/glm.hpp"
#include "Pixel.h"

class Camera
{
public:
	Camera();
	~Camera();
	void renderImage();							// Loops over all pixels and computes
												// their values.
	void mappingFunction();						// Converts radiometric values into
												// photometric ones.
	void saveImage();							// Alternatively displayImage()

private:
	glm::vec3 position;
	glm::vec3 direction;
	float viewPlaneDistance;
	int resolutionX;
	int resolutionY;
	int raysPerPixel;
	Pixel* pixels;
};

#endif