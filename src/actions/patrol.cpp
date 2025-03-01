#include "actions/patrol.h"

void Patrol::execute()
{
	npcRef.setColor(ORANGE);
	npcRef.moveTo(npcRef.getPatrolPoint());
}
