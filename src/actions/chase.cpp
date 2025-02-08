#include "actions/chase.h"

void Chase::execute()
{

	enemyRef.setColor(RED);
	enemyRef.moveTo(enemyRef.getTargetRef().position);
}
