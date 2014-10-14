#include <iostream>
#include "../include/classes.h"

int main(int argc, char *argv[])
{
	// char* argument1 = argv[0];
	// int argument2 = argc;
	
	std::cout << "Hello World" << std::endl;

	//Create Scene
	Wall* room = new Wall(glm::vec3(0.0, 0.0, 0.0), 5.0);
	Cube* c1 = new Cube(glm::vec3(0.0, 0.0, 0.0), 1.0, 0.0, 0.0);


	float eyeDistance = 2.0;
	Camera* camera = new Camera(room, eyeDistance, 512, 512, 1);
	//Loop over cols and rows

	//Write to file
}
