#ifndef SPHERE_H
#define SPHERE_H value

#include "glm/glm.hpp"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(glm::vec3 _position, float _radius, bool _transparent, float _refractiveIndex);
	~Sphere();
	virtual glm::vec3 calculateIntersection(Ray* _ray);
	void calculateChildRays();

private:
	float radius;				
	bool transparent;			//true = transparent, false = not transparent
	float refractiveIndex;		//glass = 1.5, air = 1.0
};

#endif
