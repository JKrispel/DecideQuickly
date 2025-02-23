#include "drzewa_decyzyjne/enemy_in_range/distance_from_path.h"
#include <decisions/decision_tree/final_decision.h>
#include "utils/npc_action.h"

std::unique_ptr<DecisionTreeNode> DistanceFromPath::getBranch()
{
    double now = GetTime();  // czas w sekundach


    // debounce
    if (now - enemyRef.lostAggroTime < enemyRef.aggroDelay) {
        //std::cout << "Aggro on CD" << std::endl;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }

    if (enemyRef.getPathDistance() > distanceThreshold) {
        //std::cout << "Patrol" << std::endl;
        enemyRef.lostAggroTime = now;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::PATROL);
    }
    else {
        //std::cout << "Chase" << std::endl;
        return std::make_unique<FinalDecision<NpcAction>>(NpcAction::CHASE);
    }
}
