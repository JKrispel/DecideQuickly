#include "levels/crowd_follow_sm_level.h"
#include <memory>
#include "algorithms/state_machines/npcs/npc_follow_sm.h"

CrowdFollowSMLevel::CrowdFollowSMLevel() : Level() {

	for (int i = 1; i <= 1001; i += 10) {

		npcPtrs.push_back(std::make_unique<NpcFollowSM>(0.0f + i, 100.0f, 5.0f + (10.0f / i), 20.0f, *playerPtr, GREEN));
	}
}
