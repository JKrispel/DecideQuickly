#include "actions/chase.h"

void Chase::execute()
{

	npcRef.setColor(RED);
	npcRef.moveTo(npcRef.getTargetRef().getPosition());
}
