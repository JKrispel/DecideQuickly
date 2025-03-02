#include "algorithms/decision_trees/enemy_in_range/on_path.h"
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"

#include <iostream>

std::unique_ptr<DecisionTreeNode> OnPath::getBranch()
{
    double now = GetTime();  // czas w sekundach
     
    // debounce
    if (now - npcRef.directionChangeTime < npcRef.debounceDelay) {
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
    if (npcRef.getPathRef().onPoint()) {

        npcRef.directionChangeTime = now;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::CHANGE_DIRECTION);
    }
    else {
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
}