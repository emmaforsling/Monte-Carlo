#ifndef SPHERE_H
#define SPHERE_H value

#include "glm/glm.hpp"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere();
	Sphere(glm::vec3 _position, float _radius, bool _transparent, float _refractiveIndex, glm::vec3 _color, bool _diffuse);
	~Sphere();
	virtual glm::vec3 calculateIntersection(Ray* _ray);
	virtual void calculateChildRays(Ray* _ray, glm::vec3 intersectionPoint);
	virtual float getRefractiveIndex();
	virtual glm::vec3 getIntersectedNormal();
	void setIntersectedNormal(glm::vec3 _intersectedNormal);
	virtual glm::vec3 getColor();
	virtual int getIntersectedSide();

private:
	float radius;				
	float refractiveIndex;		//glass = 1.5, air = 1.0

	glm::vec3 intersectedNormal;
	int intersectedSide;
};

#endif
