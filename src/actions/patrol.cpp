#include "actions/patrol.h"

void Patrol::execute()
{
	enemyRef.setColor(ORANGE);
	enemyRef.moveTo(enemyRef.getPatrolPoint());
}
