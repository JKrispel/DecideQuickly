#include "drzewa_decyzyjne/enemy_in_range/enemy_in_range.h"
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include "core/enemy.h"
#include "drzewa_decyzyjne/enemy_in_range/distance_from_path.h"
#include "drzewa_decyzyjne/enemy_in_range/on_path.h"
    
EnemyInRange::EnemyInRange(Enemy& enemyRef) : enemyRef(enemyRef) {}

std::unique_ptr<DecisionTreeNode> EnemyInRange::getBranch()
{
    if (enemyRef.getTargetDistance() < aggroThreshold) {

        return std::make_unique<DistanceFromPath>(enemyRef);
    }
    else {

        return std::make_unique<OnPath>(enemyRef);
    }
}

