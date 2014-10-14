#ifndef SPHERE_H
#define SPHERE_H value

#include "glm/glm.hpp"

class Sphere
{
public:
	Sphere();
	Sphere(glm::vec3 pos, float rad, float trans, float refract);
	~Sphere();
	glm::vec3 calculateIntersection();
	void calculateChildRays();

private:
	glm::vec3 position;
	float radius;
	float transparency;
	float refractiveIndex;
};

#endif