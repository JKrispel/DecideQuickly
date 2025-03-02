#include "actions/lose_patience.h"

void LosePatience::execute()
{
	npcRef.losePatience();
	npcRef.moveToTarget();
}
