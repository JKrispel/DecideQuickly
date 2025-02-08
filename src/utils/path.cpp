#include <utils/path.h>

void Path::addPoint(float newX, float newY)
{
	Vector2 newVector = { newX, newY };
	pathPoints.push_back(newVector);
}

Vector2 Path::getPointAtIndex(int index)
{
	return pathPoints[index];
}

void Path::nextPathPoint()
{
	if (!pathPoints.empty()) { 
		currentPointIndex = (currentPointIndex + 1) % pathPoints.size();
	}
}

int Path::getCurrentIndex()
{
	return currentPointIndex;
}
