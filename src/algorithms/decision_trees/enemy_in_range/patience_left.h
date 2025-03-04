#pragma once
#include "decisions/decision_tree/decision.h"
#include "core/npc.h"

class PatienceLeft : public Decision {

private:
	Npc& npcRef;

public:
	PatienceLeft(Npc& enemyRef) :
		npcRef(enemyRef) {
	};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
