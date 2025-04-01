#include "levels/crowd_follow_dt_level.h"
#include <memory>
#include "algorithms/decision_trees/npcs/npc_follow_dt.h"

CrowdFollowDTLevel::CrowdFollowDTLevel() : Level() {

	for (int i = 1; i <= 101; i += 10) {

		npcPtrs.push_back(std::make_unique<NpcFollowDT>(0.0f + i, 100.0f, 5.0f + (10.0f / i), 20.0f, *playerPtr, GREEN));
	}
}
