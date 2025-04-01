#include "levels/patrol_dt_level.h"
#include <memory>
#include "algorithms/decision_trees/npcs/enemy_patrol_dt.h"

PatrolDTLevel::PatrolDTLevel()
{
	npcPtrs.push_back(std::make_unique<EnemyPatrolDT>(100.0f, 100.0f, 5.0f, 20.0f, *playerPtr, ORANGE));
}
