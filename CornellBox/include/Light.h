#ifndef LIGHT_H
#define LIGHT_H value

#include "glm/glm.hpp"
#include "Rectangle.h"

class Light
{
public:
	Light();
	~Light();

	glm::vec3 getRandomPosition();			// returns a random position on the
											// light source rectangle
	
private:
	Rectangle* sumthin;
	float radiance;
	glm::vec3 position;
	float size;
};

#endif