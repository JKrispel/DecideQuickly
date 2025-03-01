#include "actions/change_direction.h"

void ChangeDirection::execute()
{
	npcRef.setColor(ORANGE);
	npcRef.getPathRef().nextPathPoint();
	npcRef.moveTo(npcRef.getPatrolPoint());
}
