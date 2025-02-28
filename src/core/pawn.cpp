#include "core/pawn.h"

void Pawn::dealDmg(int hpAmount)
{
	hp -= hpAmount;
}

void Pawn::healPawn(int hpAmount)
{
	hp += hpAmount;
}

int Pawn::getHp()
{
	return hp;
}

Vector2 Pawn::getPosition()
{
	return position;
}

void Pawn::setPosition(float newX, float newY)
{
	position = Vector2{ newX, newY };
}

void Pawn::updateFinished()
{
	{
		std::lock_guard<std::mutex> lock(pawnMutex);
		newUpdate = true;
	}
	updateCondition.notify_one();
}

void Pawn::drawAfterUpdate()
{
	std::unique_lock<std::mutex> lock(pawnMutex);
	updateCondition.wait(lock, [this] { return newUpdate; });  // renderuje dopiero jak zajdzie zmiana
	newUpdate = false;
}
