#pragma once
#include "decisions/decision_tree/decision_tree_node.h"
#include "decisions/action_manager/action_manager.h"
#include "decisions/action_manager/action.h"
#include <memory>


class FinalDecision : public DecisionTreeNode {

private:
    int actionType;

public:
    FinalDecision(int action) : actionType(action) {}
    ~FinalDecision() = default;

    std::unique_ptr<DecisionTreeNode> makeDecision() override;
    int getActionType() const;
};