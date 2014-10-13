#ifndef RECTANGLE_H
#define RECTANGLE_H value

class Rectangle
{
public:
	Rectangle();
	~Rectangle();
	glm::vec3 calculateIntersection();
	void calculateChildRays();					// only called on cube

private:
	glm::vec3 positionsOfCorners[4];
};

#endif