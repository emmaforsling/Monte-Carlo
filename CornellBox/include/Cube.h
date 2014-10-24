#ifndef CUBE_H
#define CUBE_H value

#include "glm/glm.hpp"
#include "Rectangle.h"
#include "Object.h"
#include "Ray.h"

class Cube : public Object
{
public:
	// Empty constructor
	Cube();

	// Constructor
	Cube(glm::vec3 _position, float _size, bool _transparent, float _refractiveIndex, glm::vec3 _color, bool _diffuse);
	
	// Default destructor
	~Cube() = default;

	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	
	// Calculation functions
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint);
	virtual glm::vec3 calculateIntersection(Ray* _ray);

	// Get functions
	virtual glm::vec3 getColor();
	virtual glm::vec3 getIntersectedNormal();
	virtual int getIntersectedSide();
	virtual float getRefractiveIndex();




private:
	Rectangle* sides[6];
	float size;
	float refractiveIndex;

	glm::vec3 intersectedNormal;
	int intersectedSide;
};

#endif