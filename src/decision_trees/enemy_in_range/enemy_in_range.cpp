#include "decision_trees/enemy_in_range/enemy_in_range.h"
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include "decision_trees/enemy_in_range/distance_from_path.h"
#include "decision_trees/enemy_in_range/on_path.h"
    
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

