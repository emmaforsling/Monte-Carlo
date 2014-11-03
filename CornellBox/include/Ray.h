#ifndef RAY_H
#define RAY_H value

#include "glm/glm.hpp"
class Object;
class Ray
{
public:
	// Empty constructor
	Ray();

	// Constructor
	Ray(glm::vec3 _startingPoint, glm::vec3 _direction, float _importance, glm::vec3 _color, bool _insideObject);
	
	// Destructor
	~Ray();

	// Calculation functions
	glm::vec3 calculateColor();					// combines color contributions from
												// childNodes and a local lighting
												// model (Phong's?) to a single RGB
	 											// vector
	glm::vec3 calculateLocalLightingContribution(Object* _object, Ray* _shadowRay);	// computes Le(x,theta) for the
												// point where a ray intersects
												// a surface.


	// Get functions
	glm::vec3 getColor();
	glm::vec3 getDirection();
	float getImportance();
	glm::vec3 getStartingPoint();
	
	// Bool functions
	bool isInsideObject();
	bool russianRoulette(glm::vec3 colorForTheReflectedRay, double survivalOds);

	// Reflect and refract
	glm::vec3 reflectRay(glm::vec3 _direction, glm::vec3 _intersectedNormal);
	glm::vec3 refractRay();

	// Public variables
	Ray* childNodes;							// maybe just one
	glm::vec3 intersectionPoint;

private:
	
	glm::vec3 color;							// vec4 for alpha?
	glm::vec3 direction;
	bool insideObject;
	bool finalNode;
	float importance;
	glm::vec3 startingPoint;

};

#endif