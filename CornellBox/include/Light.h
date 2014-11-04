#ifndef LIGHT_H
#define LIGHT_H value

#include "glm/glm.hpp"
#include "Rectangle.h"

#include <stdlib.h>
#include <time.h>

class Light
{
public:
	// Empty constructor
	Light();

	// Constructor
	Light(glm::dvec3 _position, double _size, double _radiance);
	
	// Destructor
	~Light();

	// Get functions
	glm::dvec3 getPosition();
	glm::dvec3 getRandomPosition();			// returns a random position on the
	double getRadiance();										// light source rectangle
	
	
private:
	Rectangle* lightSource;
	double radiance;							//Le - emitted radiance
											//where the lightsource should be a diffuse emitter
	glm::dvec3 position;
	double size;
};

#endif