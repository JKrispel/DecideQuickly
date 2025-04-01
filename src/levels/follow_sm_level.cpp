#include "levels/follow_sm_level.h"
#include <memory>
#include "algorithms/state_machines/npcs/npc_follow_sm.h"

FollowSMLevel::FollowSMLevel()
{
	npcPtrs.push_back(std::make_unique<NpcFollowSM>(100.0f, 100.0f, 5.0f, 20.0f, *playerPtr, GREEN));
}
