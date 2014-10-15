#ifndef LIGHT_H
#define LIGHT_H value

#include "glm/glm.hpp"
#include "Rectangle.h"

class Light
{
public:
	Light();
	Light(glm::vec3 _position, float _size, float _radiance);
	~Light();

	glm::vec3 getRandomPosition();			// returns a random position on the
											// light source rectangle
	
private:
	Rectangle* lightSource;
	float radiance;							//Le - emitted radiance
											//where the lightsource should be a diffuse emitter
	glm::vec3 position;
	float size;
};

#endif