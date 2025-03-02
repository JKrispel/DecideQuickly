#include "actions/chase.h"

void Chase::execute()
{
	npcRef.setColor(RED);
	npcRef.moveToTarget();
}
