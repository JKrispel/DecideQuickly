#pragma once
#include "decisions/decision_tree/decision_tree_node.h"
#include "decisions/action_manager/action_manager.h"
#include "decisions/action_manager/action.h"
#include <string>
#include <memory>
#include <type_traits>


// Template class
template <typename ActionEnum>
class FinalDecision : public DecisionTreeNode {
    static_assert(std::is_enum_v<ActionEnum>, "ActionEnum must be an enum type!");

private:
    ActionEnum actionType;

public:
    explicit FinalDecision(ActionEnum action) : actionType(action) {}

    ActionEnum getActionType() const { return actionType; }

    std::unique_ptr<DecisionTreeNode> makeDecision() override {
        return std::make_unique<FinalDecision<ActionEnum>>(actionType);
    }
};