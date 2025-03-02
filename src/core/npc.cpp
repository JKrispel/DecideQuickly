#include "core/npc.h"
#include "raylib.h"
#include "raymath.h"

Npc::Npc(float x, float y, float speed, float radius, Pawn& targetRef, Color color)
	: Pawn(x, y, speed, radius, color), 
	targetRef(targetRef), pathPtr(std::make_unique<Path>(*this)) {}

float Npc::distanceToTarget()
{
	float distanceToTarget = 
		Vector2Distance(this->getPosition(), targetRef.getPosition());

	return distanceToTarget;
}

Pawn& Npc::getTargetRef()
{
	return targetRef;
}

void Npc::moveToTarget()
{
	moveTo(targetRef.getPosition());
}

Path& Npc::getPathRef()
{
	return *pathPtr;
}

Vector2 Npc::getPatrolPoint()
{
	Vector2 point = pathPtr->getPointAtIndex(pathPtr->getCurrentIndex());
	return point;
}

float Npc::getPatience()
{
	return patience;
}

void Npc::losePatience(float amount)
{
	if (patience < 0.0f) {

		lostPatience = true;
	}
	else {
		patience -= amount;
	}
}

bool Npc::noPatience()
{
	return lostPatience;
}

void Npc::resetPatience()
{
	patience = 100.0f;
	lostPatience = false;
}
