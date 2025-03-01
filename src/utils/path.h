#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"
class Npc;	// forward declaration

class Path {

private:
	Npc& npcRef;
	std::vector<Vector2> pathPoints = {};
	int currentPointIndex = 0;

public:
	Path(Npc& npcRef);

	bool onPoint();
	void addPoint(float newX,float newY);
	Vector2 getPointAtIndex(int index);
	void nextPathPoint();
	int getCurrentIndex();
	float distanceToPath();
};
