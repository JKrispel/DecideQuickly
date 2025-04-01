#include "levels/patrol_sm_level.h"
#include <memory>
#include "algorithms/state_machines/npcs/enemy_patrol_sm.h"

PatrolSMLevel::PatrolSMLevel()
{
	npcPtrs.push_back(std::make_unique<EnemyPatrolSM>(100.0f, 100.0f, 5.0f, 20.0f, *playerPtr, ORANGE));
}
