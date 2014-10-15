#include <iostream>
#include "../include/classes.h"

int main(int argc, char *argv[])
{
	// char* argument1 = argv[0];
	// int argument2 = argc;
	
	std::cout << "Hello Martin, time to create a beautiful cornell boss" << std::endl;

	/* 
		Initialize variables 
	*/
		// Eye
	float eyeDistance = 2.0;
	
		// Room
	float size = 5.0;		// Is also used in lightsource, where it is scaled
	glm::vec3 positionRoom = glm::vec3(0.0, 0.0, 0.0);

		// Light
	float radiance = 1.0;	//emitted radiance Le
	glm::vec3 positionLight = glm::vec3(0.0, 0.0, 0.0);
	
		// Cube
	glm::vec3 positionCube = glm::vec3(0.0, 0.0, 0.0);
		
		// Sphere
	glm::vec3 positionSphereSpecular = glm::vec3(0.0, 0.0, 0.0);
	float radiusForSphereSpecular = 0.5;
	bool transparencyForSphereSpecular = false;
	float refractiveIndexForSphereSpecular = 1.5;	//glass

	// glm::vec3 positionSphereTransparent = glm::vec3(0.0, 0.0, 0.0);
	// float radiusForSphereTransparent = 1.0;
	// bool transparencyForSphereTransparent = true;
	// float refractiveIndexForSphereTransparent = 1.5;	//glass

	/*
		Create Scene
	*/
	Wall* room = new Wall(positionRoom, size);
	Light* lightsource = new Light(positionLight, size, radiance); 
	Cube* c1 = new Cube(positionCube, 1.0, 0.0, 0.0);
	Sphere* sphereSpecular = new Sphere(positionSphereSpecular, radiusForSphereSpecular, transparencyForSphereSpecular, refractiveIndexForSphereSpecular );
	//Sphere* sphereTransparent = new Sphere(positionSphereTransparent, radiusForSphereTransparent, transparencyForSphereTransparent, refractiveIndexForSphereTransparent);

	// Create camera
	Camera* camera = new Camera(room, eyeDistance, 4);
	
	// Render scene
	camera->renderImage();

	//Write to file
}
