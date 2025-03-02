#include "algorithms/decision_trees/distance_decision/distance_decision.h"
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"
#include "algorithms/decision_trees/distance_decision/close_enough_decision.h"
#include "raylib.h"
#include "raymath.h"

std::unique_ptr<DecisionTreeNode> DistanceDecision::getBranch() {

    float distance = distanceToTarget();

    if (distance < slowDownThreshold) {

        return std::make_unique<CloseEnoughDecision>(distance);
    }
    else {

        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::RUN);
    }
}

float DistanceDecision::distanceToTarget() {

    return Vector2Distance(npcRef.getPosition(), npcRef.getTargetRef().getPosition());
}
