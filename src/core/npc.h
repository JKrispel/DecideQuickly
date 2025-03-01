#pragma once
#include "core/pawn.h"
#include "utils/path.h"

// virtual class
class Npc : public Pawn {

private:	// Pawn z obsługą ścieżek
	std::unique_ptr<Path> pathPtr;
	Pawn& targetRef;

public:
	Npc(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);

	float distanceToTarget();
	Pawn& getTargetRef();
	Path& getPathRef();
	Vector2 getPatrolPoint();

	// TODO przenieść do private
	// pathing and aggro debounce:
	double directionChangeTime = 0.0f;  // ostatnia Akcja CHANGE_DIRECTION
	const double debounceDelay = 0.5f;  // debounce
	double lostAggroTime = 0.0f;  // ostatnie stracenie aggro
	double aggroDelay = 2.0f;	// cooldown dla CHASE
};