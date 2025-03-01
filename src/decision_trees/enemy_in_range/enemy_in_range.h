#pragma once
#include <decisions/decision_tree/decision.h>
#include <memory>
#include "core/npc.h"

class Enemy;

class EnemyInRange : public Decision {

private:
	float aggroThreshold = 300.0f;	// próg dla wykrycia, hardcoded by design
	Npc& npcRef;

public:
	EnemyInRange(Npc& npcRef);

	std::unique_ptr<DecisionTreeNode> getBranch();
};
