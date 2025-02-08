#pragma once
#include <decisions/decision_tree/decision.h>


class DistanceDecision : public Decision {

private:
	float slowDownThreshold = 200.0f;	// próg dla zwolnienia, hardcoded by design
	float distanceToTarget = 0;

public:
	DistanceDecision(float distanceToTarget) : 
		distanceToTarget(distanceToTarget) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
	void setDistanceToTarget(float newDistanceToTarget);
};
