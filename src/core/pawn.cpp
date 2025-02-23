#include "pawn.h"

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

void Pawn::setPosition(Vector2 newPosition)
{
	position = newPosition;
}
