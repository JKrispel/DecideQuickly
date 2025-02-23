#include "drzewa_decyzyjne/distance_decision/distance_decision.h"
#include <decisions/decision_tree/final_decision.h>
#include "utils/npc_action.h"
#include "drzewa_decyzyjne/distance_decision/close_enough_decision.h"


std::unique_ptr<DecisionTreeNode> DistanceDecision::getBranch()
{
    if (distanceToTarget < slowDownThreshold) {

        return std::make_unique<CloseEnoughDecision>(distanceToTarget);
    }
    else {

        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::RUN);
    }
}

void DistanceDecision::setDistanceToTarget(float newDistanceToTarget)
{
    distanceToTarget = newDistanceToTarget;
}
