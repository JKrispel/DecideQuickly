#include "algorithms/decision_trees/enemy_in_range/patience_left.h"
#include "algorithms/decision_trees/enemy_in_range/enemy_in_range.h"
#include "algorithms/decision_trees/enemy_in_range/on_path.h"

std::unique_ptr<DecisionTreeNode> PatienceLeft::getBranch()
{
    if (npcRef.noPatience()) {

        return std::make_unique<OnPath>(npcRef);
    }
    else {
        return std::make_unique<EnemyInRange>(npcRef);
    }
}
