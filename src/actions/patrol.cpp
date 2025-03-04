#include "actions/patrol.h"

void Patrol::execute()
{
	npcRef.setColor(LIGHTGRAY);
	npcRef.moveTo(npcRef.getPatrolPoint());
}
