#include "algorithms/decision_trees/enemy_in_range/enemy_in_range.h"
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include "algorithms/decision_trees/enemy_in_range/distance_from_path.h"
#include "algorithms/decision_trees/enemy_in_range/on_path.h"
#include "decisions/decision_tree/final_decision.h"
#include "utils/npc_action.h"
    
EnemyInRange::EnemyInRange(Npc& npcRef) : npcRef(npcRef) {}

std::unique_ptr<DecisionTreeNode> EnemyInRange::getBranch()
{
    if (npcRef.distanceToTarget() < aggroThreshold) {

        return std::make_unique<DistanceFromPath>(npcRef);
    }
    else {

        return std::make_unique<OnPath>(npcRef);
    }
}

