#ifndef CAMERA_H
#define CAMERA_H value

#include "glm/glm.hpp"
#include "Pixel.h"
#include "Wall.h"

class Camera
{
public:
	Camera();
	Camera(Wall* _room, float _eyeDistance, int _raysPerPixel);
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
	int viewPlaneSizeX;
	int viewPlaneSizeY;
	static const int resolutionX = 2;
	static const int resolutionY = 2;
	int raysPerPixel;
	Pixel* pixels[resolutionX * resolutionY];
};

#endif
