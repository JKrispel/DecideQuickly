#include "levels/follow_dt_level.h"
#include <memory>
#include "algorithms/decision_trees/npcs/npc_follow_dt.h"

FollowDTLevel::FollowDTLevel(): Level() {

	npcPtrs.push_back(std::make_unique<NpcFollowDT>(100.0f, 100.0f, 5.0f, 20.0f, *playerPtr, GREEN));
}
