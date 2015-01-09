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
	glm::dvec3 calculateLocalLightingContribution(Object* _object, glm::dvec3 _directionFromLight, double _radiance, int _iteration);	// computes Le(x,theta) for the
												// point where a ray intersects
												// a surface.


	// Get functions
	glm::dvec3 getColor();
	glm::dvec3 getDirection();
	double getImportance();
	glm::dvec3 getStartingPoint();
	
	// Set functions
	void setIsInsideObject(bool _insideObject);
	void setIsRefractedRay(bool refracted){isRefracted = refracted;};
	// Bool functions
	bool isInsideObject();
	bool russianRoulette(glm::dvec3 colorForTheReflectedRay, double survivalOds);
	bool isRefractedRay(){return isRefracted;};
	// Reflect and refract
	glm::dvec3 reflectRay(glm::dvec3 _direction, glm::dvec3 _intersectedNormal);
	glm::dvec3 refractRay();

	int getIteration(){return iteration;};
	void setIteration(int _iteration){iteration = _iteration;};

	// Public variables
	//Ray* childNodes;							// maybe just one
	Ray* reflectedRay;
	Ray* refractedRay;
	glm::dvec3 intersectionPoint;

private:
	int iteration;
	glm::dvec3 color;							// vec4 for alpha?
	glm::dvec3 direction;
	bool insideObject;
	bool isRefracted;
	bool finalNode;
	double importance;
	glm::dvec3 startingPoint;

};

#endif