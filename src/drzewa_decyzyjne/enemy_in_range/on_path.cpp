#include "drzewa_decyzyjne/enemy_in_range/on_path.h"
#include <decisions/decision_tree/final_decision.h>
#include "utils/npc_action.h"
#include "utils/is_close.h"

#include <iostream>

std::unique_ptr<DecisionTreeNode> OnPath::getBranch()
{
    double now = GetTime();  // czas w sekundach
     
    // debounce
    if (now - enemyRef.changeDirectionTime < enemyRef.debounceDelay) {
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
    if (isClose(enemyRef.getPathDistance(), 0.0f)) {

        enemyRef.changeDirectionTime = now;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::CHANGE_DIRECTION);
    }
    else {
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
}