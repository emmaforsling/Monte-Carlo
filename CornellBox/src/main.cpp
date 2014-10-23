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
	glm::vec3 positionLight = glm::vec3(1.0, 3.0, 5.0);
	
		// Cube
	glm::vec3 positionCube = glm::vec3(3.5, 0.0, 3.0);
	float sizeForCubeSpecular = 1.0;
	bool transparencyForCubeSpecular = false;
	float refractiveIndexForCubeSpecular = 1.5;				// glass
	
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
	Wall* room = new Wall(positionRoom, size, glm::vec3(1.0, 0.0, 0.5));
	Light* lightsource = new Light(positionLight, size, radiance); 
	Cube* cubeSpecular = new Cube(positionCube, sizeForCubeSpecular, transparencyForCubeSpecular, refractiveIndexForCubeSpecular, glm::vec3(0.8, 0.0, 0.6));
	Sphere* sphereSpecular = new Sphere(positionSphereSpecular, radiusForSphereSpecular, transparencyForSphereSpecular, refractiveIndexForSphereSpecular, glm::vec3(0.2, 1.0, 0.2) );
	Sphere* sphereSpecular2 = new Sphere(glm::vec3(0.5, 0.5, 3.25), 0.5, transparencyForSphereSpecular, 0, glm::vec3(0.2, 0.2, 1.0) );
	// Sphere* sphereTransparent = new Sphere(positionSphereTransparent, radiusForSphereTransparent, transparencyForSphereTransparent, refractiveIndexForSphereTransparent, glm::vec3(1.0, 0.0, 0.0));

	// Create camera
	int raysPerPixel = 16;
	Camera* camera = new Camera(room, eyeDistance, raysPerPixel);
	
	// Ray test
	Ray* ray = new Ray(glm::vec3(2.5, 5.0, 2.5), glm::vec3(0.0, -1.0, 0.0), 1.0, glm::vec3(0.0, 0.0, 0.0), false);
	//sphereSpecular->calculateIntersection(ray);

	Object* objects[4];
	objects[1] = sphereSpecular;
	objects[2] = sphereSpecular2;
	objects[0] = room;
	objects[3] = cubeSpecular;

	/*
	// super-duper test
	glm::vec3 intersectionPoint = cubeSpecular->calculateIntersection(ray);
	srand(time(NULL));
	glm::vec3 randomPositionOnLightSource = lightsource->getRandomPosition();
	Ray* shadowRay = new Ray(randomPositionOnLightSource, (intersectionPoint - randomPositionOnLightSource), 1.0, glm::vec3(0.0, 0.0, 0.0), false);
	// looping through all objects to check for occlusion
	glm::vec3 shadowIntersection;
	int numberOfObjects = 3;
	int intersectionPointVisibleFromLightSource = 1;
	// // std::cout << "\n ====== Checking for occlusion ====== \n" << std::endl;
	for(int j = 0; j < numberOfObjects; j++)
	{
		shadowIntersection = objects[j]->calculateIntersection(shadowRay);
		// // std::cout << "objects[" << j << "] calculateIntersection() returned: (" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ")" << std::endl;
		if( shadowIntersection  != glm::vec3(0.0, 0.0, 0.0) )
		{	
			// // std::cout << "Found intersection along shadowRay direction!" << std::endl;
			if(glm::length(randomPositionOnLightSource - shadowIntersection) < glm::length(randomPositionOnLightSource - intersectionPoint) )
			{
				intersectionPointVisibleFromLightSource = 0;
				// // std::cout << "This intersection point is closer to the light source than the shadow ray origin - occlusion!" << std::endl;
			}
			else
			{
				// // std::cout << "This intersection point is not closer to the light source than the shadow ray origin - no occlusion!" << std::endl;
			}
		}
	}
	*/

	//next
	// calc.child.rays
	// ta fram färger för pixlarna (importance * )

	// Render scene
	camera->renderImage(objects, lightsource);

	// Write to file
	camera->saveImage();

	return 0;
}
