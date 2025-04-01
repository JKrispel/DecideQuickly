#pragma once
#include "decisions/decision_tree/decision_tree_node.h"
#include <memory>
// Abstract Class
class Decision :
    public DecisionTreeNode
{
public:
    virtual ~Decision() = default;

    virtual std::unique_ptr<DecisionTreeNode> getBranch() = 0;  // miejsce na własną implementację decyzji
    std::unique_ptr<DecisionTreeNode> makeDecision() override;  
};

