#include "levels/crowd_patrol_dt_level.h"
#include <memory>
#include "algorithms/decision_trees/npcs/enemy_patrol_dt.h"

CrowdPatrolDTLevel::CrowdPatrolDTLevel() : Level() {

	for (int i = 1; i <= 1001; i += 10) {

		npcPtrs.push_back(std::make_unique<EnemyPatrolDT>(0.0f + i, 100.0f, 5.0f + (10.0f / i), 20.0f, *playerPtr, GREEN));
	}
}
