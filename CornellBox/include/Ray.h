#ifndef RAY_H
#define RAY_H value

#include "glm/glm.hpp"

class Ray
{
public:
	Ray();
	Ray(glm::vec3 _startingPoint, glm::vec3 _direction, float _importance, glm::vec3 _color, bool _insideObject);
	~Ray();
	glm::vec3 calculateColor();					// combines color contributions from
												// childNodes and a local lighting
												// model (Phong's?) to a single RGB
	 											// vector
	void calculateLocalLightingContribution();	// computes Le(x,theta) for the
												// point where a ray intersects
												// a surface.
	glm::vec3 getStartingPoint();
	glm::vec3 getDirection();
	bool isInsideObject();
	float getImportance();
	glm::vec3 getColor();

	Ray* childNodes;							// maybe just one

private:
	glm::vec3 startingPoint;
	glm::vec3 direction;
	float importance;
	glm::vec3 color;							// vec4 for alpha?
	bool finalNode;
	bool insideObject;
};

#endif