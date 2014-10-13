/**
* Monte Carlo Ray Tracer
* Emma Forsling Parborg, Martin Gråd
* TNGC15 - Global Illumination and Rendering
* Linköping University
* 2014-10-11
*
* ====== Comments ======
* - "cl /EHsc classes.cpp" in "Developer Command Prompt for VS2013" in Windows
* - "something else" in OSX
**/

#include "../include/classes.h"

// class Ray
// {
// public:
// 	Ray();
// 	~Ray();
// 	glm::vec3 calculateColor();					// combines color contributions from
// 												// childNodes and a local lighting
// 												// model (Phong's?) to a single RGB
// 	 											// vector
// 	void calculateLocalLightingContribution();	// computes Le(x,theta) for the
// 												// point where a ray intersects
// 												// a surface.

// private:
// 	glm::vec3 startingPoint;
// 	glm::vec3 direction;
// 	float importance;
// 	glm::vec3 color;							// vec4 for alpha?
// 	bool finalNode;
// 	Ray* childNodes;
// 	bool insideObject;
// };

// class Pixel
// {
// public:
// 	Pixel();
// 	~Pixel();
// 	void shootRays();							// Should also track the rays
// 												// witin the scene (tree structure?)
// private:
// 	Ray* rays;
// 	glm::vec3 colorOfPixel;						// vec4 for alpha?
// };

// class Camera
// {
// public:
// 	Camera();
// 	~Camera();
// 	void renderImage();							// Loops over all pixels and computes
// 												// their values.
// 	void mappingFunction();						// Converts radiometric values into
// 												// photometric ones.
// 	void saveImage();							// Alternatively displayImage()

// private:
// 	glm::vec3 position;
// 	glm::vec3 direction;
// 	float viewPlaneDistance;
// 	int resolutionX;
// 	int resolutionY;
// 	int raysPerPixel;
// 	Pixel* pixels;
// };

// class Sphere
// {
// public:
// 	Sphere();
// 	~Sphere();
// 	glm::vec3 calculateIntersection();
// 	void calculateChildRays();

// private:
// 	glm::vec3 position;
// 	float radius;
// 	float transparency;
// 	float refractiveIndex;
// };

// class Rectangle
// {
// public:
// 	Rectangle();
// 	~Rectangle();
// 	glm::vec3 calculateIntersection();
// 	void calculateChildRays();					// only called on cube

// private:
// 	glm::vec3 positionsOfCorners[4];
// };

// class Cube
// {
// public:
// 	Cube();
// 	~Cube();
// 	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
// 												// (1,0,0), (0,1,0) etc. and multiplies
// 												// them by size (float) and adds the
// 												// position (glm::vec3)
// 	void calculateChildRays();

// private:
// 	Rectangle* sides[6];
// 	glm::vec3 position;
// 	float size;
// 	float transparency;
// 	float refractiveIndex;
// };

// class Wall
// {
// public:
// 	Wall();
// 	~Wall();
// 	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
// 												// (1,0,0), (0,1,0) etc. and multiplies
// 												// them by size (float) and adds the
// 												// position (glm::vec3)
// 	glm::vec3 calculateIntersection();			// either one intersection or none (ray leaving)

// private:
// 	glm::vec3 position;
// 	float size;
// };