#ifndef SPHERE_H
#define SPHERE_H value

#include "glm/glm.hpp"
#include "Ray.h"

class Sphere
{
public:
	Sphere();
	Sphere(glm::vec3 _position, float _radius, bool _transparency, float _refractiveIndex);
	~Sphere();
	glm::vec3 calculateIntersection(Ray* ray);
	void calculateChildRays();

private:
	glm::vec3 position;			//where the position is the centerpoint of the sphere
	float radius;				
	bool transparency;			//true = transparent, false = not transparent
	float refractiveIndex;		//glass = 1.5, air = 1.0
};

#endif