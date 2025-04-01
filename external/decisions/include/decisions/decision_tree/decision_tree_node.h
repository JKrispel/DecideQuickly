#pragma once
#include <memory>
// Abstract Class
class DecisionTreeNode
{
public:
	virtual ~DecisionTreeNode() = default;

	virtual std::unique_ptr<DecisionTreeNode> makeDecision() = 0;
};

