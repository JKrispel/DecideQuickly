#include "actions/lose_patience.h"

void LosePatience::execute()
{
	npcRef.setColor(ORANGE);
	npcRef.losePatience();
	npcRef.moveToTarget();
	npcRef.damageTarget();
}
