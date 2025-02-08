#pragma once
#include <raylib.h>
#include <vector>

class Path {

private:
	std::vector<Vector2> pathPoints = {};
	int currentPointIndex = 0;

public:
	void addPoint(float newX,float newY);
	Vector2 getPointAtIndex(int index);
	void nextPathPoint();
	int getCurrentIndex();
};
