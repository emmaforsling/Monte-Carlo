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
	Ray(glm::dvec3 _startingPoint, glm::dvec3 _direction, double _importance, glm::dvec3 _color, bool _insideObject);
	
	// Destructor
	~Ray();

	// Calculation functions
	glm::dvec3 calculateColor();					// combines color contributions from
												// childNodes and a local lighting
												// model (Phong's?) to a single RGB
	 											// vector
	glm::dvec3 calculateLocalLightingContribution(Object* _object, Ray* _shadowRay);	// computes Le(x,theta) for the
												// point where a ray intersects
												// a surface.


	// Get functions
	glm::dvec3 getColor();
	glm::dvec3 getDirection();
	double getImportance();
	glm::dvec3 getStartingPoint();
	
	// Bool functions
	bool isInsideObject();
	bool russianRoulette(glm::vec3 colorForTheReflectedRay, double survivalOds);

	// Public variables
	Ray* childNodes;							// maybe just one
	glm::dvec3 intersectionPoint;

	void setIsInsideObject(bool _insideObject);

private:
	glm::dvec3 color;							// vec4 for alpha?
	glm::dvec3 direction;
	bool insideObject;
	bool finalNode;
	double importance;
	glm::dvec3 startingPoint;

};

#endif