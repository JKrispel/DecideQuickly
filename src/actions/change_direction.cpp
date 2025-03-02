#include "actions/change_direction.h"

void ChangeDirection::execute()
{
	npcRef.getPathRef().nextPathPoint();
	npcRef.moveTo(npcRef.getPatrolPoint());
	npcRef.resetPatience();
}
