#pragma once
#include "decisions/decision_tree/decision.h"
#include "core/npc.h"

class DistanceDecision : public Decision {

private:
	Npc& npcRef;
	float slowDownThreshold = 200.0f;	// pr�g dla zwolnienia, hardcoded by design

public:
	DistanceDecision(Npc& npcRef) : 
		npcRef(npcRef) { };

	std::unique_ptr<DecisionTreeNode> getBranch() override;
	float distanceToTarget();
};
