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
