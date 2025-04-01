#pragma once
#include "core/pawn.h"
#include "utils/path.h"

// virtual class
class Npc : public Pawn {

private:	// Pawn z obsługą ścieżek i cierpliwością
	std::unique_ptr<Path> pathPtr;
	Pawn& targetRef;
	bool lostPatience = false;
	float patience = 100;

public:
	Npc(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);
	virtual ~Npc() = default;

	float distanceToTarget();
	Pawn& getTargetRef();
	void moveToTarget();
	Path& getPathRef();
	Vector2 getPatrolPoint();
	float getPatience();
	void losePatience(float amount = 1.0f);
	bool noPatience();
	void resetPatience();
	void damageTarget();
	// TODO przenieść do private
	// debounce:
	double directionChangeTime = 0.0f;  // ostatnia zmiana kierunku
	const double directionChangeDelay = 0.5f;
	double lastDmgTime{};	// ostatnie zadanie obrażeń
	const double dmgDelay = 0.5;
};
