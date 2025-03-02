#pragma once
#include <decisions/decision_tree/decision.h>
#include "core/npc.h"
#include "utils/path.h"

class OnPath : public Decision {

private:
	Npc& npcRef;

public:
	OnPath(Npc& npcRef) :
		npcRef(npcRef) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
