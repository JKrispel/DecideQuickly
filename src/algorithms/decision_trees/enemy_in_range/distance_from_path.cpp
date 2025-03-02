#include "algorithms/decision_trees/enemy_in_range/distance_from_path.h"
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"

std::unique_ptr<DecisionTreeNode> DistanceFromPath::getBranch()
{

    double now = GetTime();  // czas w sekundach

    if (npcRef.getPathRef().distanceToPath() > distanceThreshold) {
        npcRef.lostAggroTime = now;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
    else {
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::CHASE);
    }
}
