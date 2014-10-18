#include <iostream>
#include "../include/classes.h"

int main(int argc, char *argv[])
{
	// char* argument1 = argv[0];
	// int argument2 = argc;
	
	/*
		=== Initializing variables ===
	*/
		// Eye
	float eyeDistance = 10.0;
		// Room
	float size = 5.0;										// also used in lightsource, for scale
	glm::vec3 positionRoom = glm::vec3(0.0, 0.0, 0.0);
		// Light
	float radiance = 1.0;									// emitted radiance Le
	glm::vec3 positionLight = glm::vec3(size/2.0, 0.0, size/2);
		// Cube
	glm::vec3 positionCube = glm::vec3(0.0, 0.0, 0.0);	
		// Sphere
	glm::vec3 positionSphereSpecular = glm::vec3(2.5, 2.5, 2.5);
	float radiusForSphereSpecular = 1.0;
	bool transparencyForSphereSpecular = false;
	float refractiveIndexForSphereSpecular = 1.5;			// glass

	// glm::vec3 positionSphereTransparent = glm::vec3(0.0, 0.0, 0.0);
	// float radiusForSphereTransparent = 1.0;
	// bool transparencyForSphereTransparent = true;
	// float refractiveIndexForSphereTransparent = 1.5;		// glass
	
	/*
		=== Creating Scene ===
	*/
	Wall* room = new Wall(positionRoom, size);
	Light* lightsource = new Light(positionLight, size, radiance); 
	Cube* c1 = new Cube(positionCube, 1.0, 0.0, 0.0);
	Sphere* sphereSpecular = new Sphere(positionSphereSpecular, radiusForSphereSpecular, transparencyForSphereSpecular, refractiveIndexForSphereSpecular );
	//Sphere* sphereTransparent = new Sphere(positionSphereTransparent, radiusForSphereTransparent, transparencyForSphereTransparent, refractiveIndexForSphereTransparent);

	// Create camera
	Camera* camera = new Camera(room, eyeDistance, 4);
	
	// Ray test
	// Ray* ray = new Ray(glm::vec3(1.0, 2.0, 3.0), glm::vec3(1.0, 0.0, -2.0), 1.0, glm::vec3(0.0,0.0,0.0), false);
	// sphereSpecular->calculateIntersection(ray);

	Object* objects[4];
	objects[0] = sphereSpecular;

	// Render scene
	camera->renderImage(objects);

	//Write to file
}
