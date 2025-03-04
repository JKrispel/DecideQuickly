#include "algorithms/decision_trees/enemy_in_range/distance_from_path.h"
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"

std::unique_ptr<DecisionTreeNode> DistanceFromPath::getBranch()
{
    if (npcRef.getPathRef().distanceToPath() < distanceThreshold) {

        return std::make_unique<FinalDecision>(NpcAction::CHASE);
    }
    else {
        return std::make_unique<FinalDecision>(NpcAction::LOSE_PATIENCE);
    }
}
