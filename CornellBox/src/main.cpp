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
	glm::dvec3 positionCube = glm::dvec3(1.5, 1.5, -1.9);
	double sizeForCubeSpecular = 2.0;
	bool transparencyForCubeSpecular = false;
	double refractiveIndexForCubeSpecular = 1.5;						// glass
	
		// Sphere
	glm::dvec3 positionSphereSpecular = glm::dvec3(3.5, 1.0, 3.5);
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

	Sphere* sphereSpecular2 = new Sphere(glm::dvec3(1.5, 1.0, 2.5), 1.0, false, refractiveIndexForSphereSpecular, glm::dvec3(0.0, 0.0, 0.0), false );
	// Sphere* sphereTransparent = new Sphere(positionSphereTransparent, radiusForSphereTransparent, transparencyForSphereTransparent, refractiveIndexForSphereTransparent, glm::dvec3(1.0, 0.0, 0.0));

	// Create camera
	//int raysPerPixel = 32;
	Camera* camera = new Camera(room, eyeDistance);

	// Object array
	Object* objects[4];
	objects[0] = room;
	objects[1] = cubeSpecular;
	objects[2] = sphereSpecular;
	objects[3] = sphereSpecular2;
	
	// TESTING TESTING
	/*
	Pixel* pixel = new Pixel();
	
	std::cout << "\nCalculating first ray..." << std::endl;
	Ray* ray = new Ray(glm::dvec3(2.5, 2.5, 10.0), glm::dvec3(0.0, 0.0, -1.0), 1.0, glm::dvec3(0.0, 0.0, 0.0), false);
	std::cout << "Ray isInsideObject: " << ray->isInsideObject() << std::endl;
	std::cout << "Calculating intersection for ray (on first sphere): " << std::endl;
	std::cout << "Direction of first ray: (" << ray->getDirection().x << ", " << ray->getDirection().y << ", " << ray->getDirection().z << ")" << std::endl;
	glm::dvec3 point1 = sphereSpecular->calculateIntersection(ray, false);
	std::cout << "First intersection point: (" << point1.x << ", " << point1.y << ", " << point1.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating second ray..." << std::endl;
	sphereSpecular->calculateChildRays(ray, point1);
	Ray* secondRay = ray->refractedRay;
	std::cout << "Second ray isInsideObject: " << secondRay->isInsideObject() << std::endl;
	std::cout << "Direction of second ray: (" << secondRay->getDirection().x << ", " << secondRay->getDirection().y << ", " << secondRay->getDirection().z << ")" << std::endl;
	std::cout << "Calculating intersection for second ray (on first sphere): " << std::endl;
	glm::dvec3 point2 = sphereSpecular->calculateIntersection(secondRay, false);
	std::cout << "Second intersection point: (" << point2.x << ", " << point2.y << ", " << point2.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating third ray..." << std::endl;
	sphereSpecular->calculateChildRays(secondRay, point2);
	Ray* thirdRay = secondRay->refractedRay;
	std::cout << "Third ray isInsideObject: " << thirdRay->isInsideObject() << std::endl;
	std::cout << "Direction of third ray: (" << thirdRay->getDirection().x << ", " << thirdRay->getDirection().y << ", " << thirdRay->getDirection().z << ")" << std::endl;
	std::cout << "Calculating intersection for third ray (on second sphere): " << std::endl;
	glm::dvec3 point3 = sphereSpecular2->calculateIntersection(thirdRay, false);
	std::cout << "Third intersection point: (" << point3.x << ", " << point3.y << ", " << point3.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular2->getIntersectedNormal().x << ", " << sphereSpecular2->getIntersectedNormal().y << ", " << sphereSpecular2->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating fourth ray..." << std::endl;
	sphereSpecular2->calculateChildRays(thirdRay, point3);
	Ray* fourthRay = thirdRay->reflectedRay;
	std::cout << "Fourth ray isInsideObject: " << fourthRay->isInsideObject() << std::endl;
	std::cout << "Direction of fourth ray: (" << fourthRay->getDirection().x << ", " << fourthRay->getDirection().y << ", " << fourthRay->getDirection().z << ")" << std::endl;
	std::cout << "Calculating intersection for fourth ray (on first sphere): " << std::endl;
	glm::dvec3 point4 = sphereSpecular->calculateIntersection(fourthRay, false);
	std::cout << "Third intersection point: (" << point4.x << ", " << point4.y << ", " << point4.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating fifth ray..." << std::endl;
	sphereSpecular->calculateChildRays(fourthRay, point4);
	Ray* fifthRay = fourthRay->refractedRay;
	std::cout << "Fifth ray isInsideObject: " << fifthRay->isInsideObject() << std::endl;
	std::cout << "Direction of fifth ray: (" << fifthRay->getDirection().x << ", " << fifthRay->getDirection().y << ", " << fifthRay->getDirection().z << ")" << std::endl;
	std::cout << "Calculating intersection for fifth ray (on first sphere): " << std::endl;
	glm::dvec3 point5 = sphereSpecular->calculateIntersection(fifthRay, false);
	std::cout << "Third intersection point: (" << point5.x << ", " << point5.y << ", " << point5.z << ")" << std::endl;
	std::cout << "Normal at intersection point: (" << sphereSpecular->getIntersectedNormal().x << ", " << sphereSpecular->getIntersectedNormal().y << ", " << sphereSpecular->getIntersectedNormal().z << ")" << std::endl;
	
	std::cout << "\nCalculating sixth ray..." << std::endl;
	sphereSpecular->calculateChildRays(fifthRay, point5);
	Ray* sixthRay = fifthRay->refractedRay;
	std::cout << "Sixth ray isInsideObject: " << sixthRay->isInsideObject() << std::endl;
	std::cout << "Direction of sixth ray: (" << sixthRay->getDirection().x << ", " << sixthRay->getDirection().y << ", " << sixthRay->getDirection().z << ")" << std::endl;
	std::cout << "Calculating intersection for sixth ray (on room): " << std::endl;
	glm::dvec3 point6 = room->calculateIntersection(sixthRay, false);
	std::cout << "Third intersection point: (" << point6.x << ", " << point6.y << ", " << point6.z << ")" << std::endl;
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
