#ifndef CUBE_H
#define CUBE_H value

#include "glm/glm.hpp"
#include "Rectangle.h"
#include "Object.h"
#include "Ray.h"

class Cube : public Object
{
public:
	Cube();
	Cube(glm::vec3 _position, float _size, bool _transparent, float _refractiveIndex);
	~Cube();
	void initializeRectangles();				// sets corners of rectangles to (0,0,0),
												// (1,0,0), (0,1,0) etc. and multiplies
												// them by size (float) and adds the
												// position (glm::vec3)
	virtual void calculateChildRays(glm::vec3 _intersectionPoint);
	virtual glm::vec3 calculateIntersection(Ray* _ray);

private:
	Rectangle* sides[6];
	float size;
	bool transparent;
	float refractiveIndex;
};

#endif