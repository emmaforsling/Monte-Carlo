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


	float cameraDistance = 10.0;

	glm::vec3 cameraDirection = glm::vec3(0.0, 0.0, -1.0);
	float cameraViewPlaneDistance = 10.0;
	glm::vec3 oppositeWallCenterPosition = (room->walls[4]->positionsOfCorners[0] + room->walls[4]->positionsOfCorners[2])/2.0f;
	glm::vec3 cameraPosition = oppositeWallCenterPosition + cameraDirection * cameraDistance;
	
	Camera* camera = new Camera(cameraPosition, cameraDirection, cameraViewPlaneDistance, 512, 512, 1);
	//Loop over cols and rows

	//Write to file
}
