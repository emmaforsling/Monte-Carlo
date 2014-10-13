#include "../include/Ray.h"

/* 	Class Ray  
	
	private members:
	- glm::vec3 startingPoint;
	- glm::vec3 direction;
	- float importance;
	- glm::vec3 color;							// vec4 for alpha?
	- bool finalNode;
	- Ray* childNodes;
	- bool insideObject;
*/

/* Default Constructor */
Ray::Ray()
{
	//TODO: Write code 
}

/* Destructor */
Ray::~Ray()
{
	//TODO: Write Code
}

/* 	Combines color contributions from childNodes and
	 a local lighting model (Phong's) to a single RGB vector 
*/
glm::vec3 Ray::calculateColor()
{
	//TODO: Write Code
	return glm::vec3(0.0, 0.0, 0.0);
}


/* Computes Le(x,theta) for the point where a ray
	intersects a surface
*/
void Ray::calculateLocalLightingContribution()
{
	//TODO: Write Code
}

