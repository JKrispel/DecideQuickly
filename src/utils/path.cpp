#include "utils/path.h"
#include "utils/is_close.h"
#include "core/npc.h"

Path::Path(Npc& npcRef) : npcRef(npcRef) {}

bool Path::onPoint()
{
	return isClose(distanceToPath(), 0.0f);
}

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

float Path::distanceToPath()
{
	float distanceToPath = Vector2Distance(
		npcRef.getPosition(), 
		getPointAtIndex(getCurrentIndex()));

	return distanceToPath;
}
