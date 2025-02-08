#include "actions/change_direction.h"

void ChangeDirection::execute()
{
	enemyRef.setColor(ORANGE);
	enemyRef.getPathRef().nextPathPoint();
	enemyRef.moveTo(enemyRef.getPatrolPoint());
}
