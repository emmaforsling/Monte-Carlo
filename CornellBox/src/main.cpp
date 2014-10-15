#include <iostream>
#include "../include/classes.h"

int main(int argc, char *argv[])
{
	// char* argument1 = argv[0];
	// int argument2 = argc;
	
	std::cout << "Hello World" << std::endl;

	//Initialize variables
	float size = 5.0;
	glm::vec3 positionRoom = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 positionLight = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 positionCube = glm::vec3(0.0, 0.0, 0.0);
	float radiance = 1.0;	//emitted radiance Le

	//Create Scene
	Wall* room = new Wall(positionRoom, size);
	Light* lightsource = new Light(positionLight, size, radiance); 
	Cube* c1 = new Cube(positionCube, 1.0, 0.0, 0.0);



	float eyeDistance = 2.0;
	Camera* camera = new Camera(room, eyeDistance, 512, 512, 1);
	//Loop over cols and rows

	//Write to file
}
