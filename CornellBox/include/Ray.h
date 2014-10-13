#ifndef RAY_H
#define RAY_H value

class Ray
{
public:
	Ray();
	~Ray();
	glm::vec3 calculateColor();					// combines color contributions from
												// childNodes and a local lighting
												// model (Phong's?) to a single RGB
	 											// vector
	void calculateLocalLightingContribution();	// computes Le(x,theta) for the
												// point where a ray intersects
												// a surface.

private:
	glm::vec3 startingPoint;
	glm::vec3 direction;
	float importance;
	glm::vec3 color;							// vec4 for alpha?
	bool finalNode;
	Ray* childNodes;
	bool insideObject;
};

#endif