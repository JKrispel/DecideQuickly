#pragma once
#include "decisions/decision_tree/decision.h"
#include "core/npc.h"

class DistanceFromPath : public Decision {

private:
	float distanceThreshold = 400.0f;	// próg oddalenia się od ścieżki, hardcoded by design
	Npc& npcRef;

public:
	DistanceFromPath(Npc& enemyRef) :
		npcRef(enemyRef) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
