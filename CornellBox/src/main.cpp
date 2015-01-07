#include <iostream>
#include "../include/classes.h"

/* TODO \
- Diffuse objects (+ handling of light)
- Local lighting model (Phong's if surface point is visible from light source)
- Transparent/intransparent objects (2 perfect/PDF)
- Russian Roulette
*/


int main(int argc, char *argv[])
{
	// char* argument1 = argv[0];
	// int argument2 = argc;
	
	/*
		=== Initializing variables ===
	*/
		// Eye
	double eyeDistance = 10.0;
	
		// Room
	double size = 5.0;													// also used in lightsource, for scale
	glm::dvec3 positionRoom = glm::dvec3(0.0, 0.0, 0.0);
	
		// Light
	double radiance = 1.0;		//calculateLightingContribution			// emitted radiance Le
	glm::dvec3 positionLight = glm::dvec3(1.0, 3.0, 5.0);
	
		// Cube
	glm::dvec3 positionCube = glm::dvec3(3.5, 3.5, 0.0);
	double sizeForCubeSpecular = 1.0;
	bool transparencyForCubeSpecular = false;
	double refractiveIndexForCubeSpecular = 1.5;						// glass
	
		// Sphere
	glm::dvec3 positionSphereSpecular = glm::dvec3(2.5, 2.5, 2.5);
	double radiusForSphereSpecular = 1.0;
	bool transparencyForSphereSpecular = true;
	double refractiveIndexForSphereSpecular = 1.5;						// glass

	// glm::dvec3 positionSphereTransparent = glm::dvec3(0.0, 0.0, 0.0);
	// double radiusForSphereTransparent = 1.0;
	// bool transparencyForSphereTransparent = true;
	// double refractiveIndexForSphereTransparent = 1.5;				// glass
	
	/*
		=== Creating Scene ===
	*/
	Wall* room = new Wall(positionRoom, size, glm::dvec3(1.0, 0.0, 0.5), true, false);
	Light* lightsource = new Light(positionLight, size, radiance);
	Cube* cubeSpecular = new Cube(positionCube, sizeForCubeSpecular, transparencyForCubeSpecular, refractiveIndexForCubeSpecular, glm::dvec3(0.0, 0.0, 0.0), false);
	Sphere* sphereSpecular = new Sphere(positionSphereSpecular, radiusForSphereSpecular, transparencyForSphereSpecular, refractiveIndexForSphereSpecular, glm::dvec3(0.0, 0.0, 0.0), false );

	Sphere* sphereSpecular2 = new Sphere(glm::dvec3(1.0, 4.0, 1.0), 1.0, false, refractiveIndexForSphereSpecular, glm::dvec3(0.0, 0.0, 0.0), false );

	// Sphere* sphereTransparent = new Sphere(positionSphereTransparent, radiusForSphereTransparent, transparencyForSphereTransparent, refractiveIndexForSphereTransparent, glm::dvec3(1.0, 0.0, 0.0));

	// Create camera
	//int raysPerPixel = 32;
	Camera* camera = new Camera(room, eyeDistance);

	// Object array
	Object* objects[4];
	objects[0] = room;
	objects[1] = sphereSpecular;
	objects[2] = sphereSpecular2;
	objects[3] = cubeSpecular;
	
	// TESTING TESTING
	/*
	Pixel* pixel = new Pixel();
	
	std::cout << "\nCalculating first ray..." << std::endl;
	Ray* ray = new Ray(glm::dvec3(2.5, 2.5, 10.0), glm::dvec3(0.0, 0.0, -1.0), 1.0, glm::dvec3(0.0, 0.0, 0.0), false);
	std::cout << "\nCalculating intersection for ray (on sphere): " << std::endl;
	std::cout << "Direction of first ray: (" << ray->getDirection().x << ", " << ray->getDirection().y << ", " << ray->getDirection().z << ")" << std::endl;
	glm::dvec3 point1 = sphereSpecular->calculateIntersection(ray, false);
	std::cout << "First intersection point: (" << point1.x << ", " << point1.y << ", " << point1.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating second ray..." << std::endl;
	sphereSpecular->calculateChildRays(ray, point1);
	Ray* secondRay = ray->refractedRay;
	std::cout << "Direction of child ray: (" << secondRay->getDirection().x << ", " << secondRay->getDirection().y << ", " << secondRay->getDirection().z << ")" << std::endl;
	std::cout << "\nCalculating intersection for second ray (on sphere): " << std::endl;
	glm::dvec3 point2 = sphereSpecular->calculateIntersection(secondRay, false);
	std::cout << "Second intersection point: (" << point2.x << ", " << point2.y << ", " << point2.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating third ray..." << std::endl;
	sphereSpecular->calculateChildRays(secondRay, point2);
	Ray* thirdRay = secondRay->refractedRay;
	std::cout << "Direction of child ray: (" << thirdRay->getDirection().x << ", " << thirdRay->getDirection().y << ", " << thirdRay->getDirection().z << ")" << std::endl;
	std::cout << "\nCalculating intersection for third ray (on room): " << std::endl;
	glm::dvec3 point3 = room->calculateIntersection(thirdRay, false);
	std::cout << "Third intersection point: (" << point3.x << ", " << point3.y << ", " << point3.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << room->getIntersectedNormal().x << ", " << room->getIntersectedNormal().y << ", " << room->getIntersectedNormal().z << ")" << std::endl;
	*/
	/*
	std::cout << "Shadow ray" << std:: endl;
	glm::dvec3 randomPositionOnLightSource = lightsource->getRandomPosition();
	std::cout << "visibility: " << pixel->castShadowRay(randomPositionOnLightSource, point2, objects, 2) << std::endl;
	glm::dvec3 localLightingContribution = ray->refractedRay->calculateLocalLightingContribution(room, (randomPositionOnLightSource - point2), lightsource->getRadiance(), 2);
	std::cout << "localLightingContribution = (" << localLightingContribution.x << ", " << localLightingContribution.y << ", " << localLightingContribution.z << ")" << std::endl;
	*/
	/*
	// super-duper test
	glm::dvec3 intersectionPoint = room->calculateIntersection(ray);
	srand(time(NULL));
	glm::dvec3 randomPositionOnLightSource = lightsource->getRandomPosition();
	Ray* shadowRay = new Ray(randomPositionOnLightSource, (intersectionPoint - randomPositionOnLightSource), 1.0, glm::dvec3(0.0, 0.0, 0.0), false);
	// looping through all objects to check for occlusion
	glm::dvec3 shadowIntersection;
	int numberOfObjects = 4;
	int intersectionPointVisibleFromLightSource = 1;
	std::cout << "\n ====== Checking for occlusion ====== \n" << std::endl;
	for(int j = 0; j < numberOfObjects; j++)
	{
		shadowIntersection = objects[j]->calculateIntersection(shadowRay);
		std::cout << "objects[" << j << "] calculateIntersection() returned: (" << shadowIntersection.x << ", " << shadowIntersection.y << ", " << shadowIntersection.z << ")" << std::endl;
		if( shadowIntersection  != glm::dvec3(0.0, 0.0, 0.0) )
		{	
			std::cout << "Found intersection along shadowRay direction!" << std::endl;
			if(glm::length(randomPositionOnLightSource - shadowIntersection) != 0 && glm::length(randomPositionOnLightSource - shadowIntersection) < glm::length(randomPositionOnLightSource - intersectionPoint) )
			{
				intersectionPointVisibleFromLightSource = 0;
				std::cout << "This intersection point is closer to the light source than the shadow ray origin - occlusion!" << std::endl;
			}
			else
			{
				std::cout << "This intersection point is not closer to the light source than the shadow ray origin - no occlusion!" << std::endl;
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
