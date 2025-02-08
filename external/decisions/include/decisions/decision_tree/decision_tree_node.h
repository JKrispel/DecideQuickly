#pragma once
#include <memory>
// Abstract Class
class DecisionTreeNode
{
public:
	virtual std::unique_ptr<DecisionTreeNode> makeDecision() = 0;
};

