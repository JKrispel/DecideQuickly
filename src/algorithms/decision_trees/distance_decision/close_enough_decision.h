#pragma once
#include <decisions/decision_tree/decision.h>


class CloseEnoughDecision : public Decision {

private:
	float stopThreshold = 60.0f;	// próg dla zatrzymania, hardcoded by design
	float distanceToTarget = 0;

public:
	CloseEnoughDecision(float distanceToTarget) :
		distanceToTarget(distanceToTarget) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
