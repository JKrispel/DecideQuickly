#include "algorithms/decision_trees/distance_decision/close_enough_decision.h"
#include <memory>
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"


std::unique_ptr<DecisionTreeNode> CloseEnoughDecision::getBranch()
{

    if (distanceToTarget < stopThreshold) {

        return std::make_unique<FinalDecision>(NpcAction::STOP);
    }
    else {

        return std::make_unique<FinalDecision>(NpcAction::WALK);
    }
}
