#pragma once
#include <decisions/decision_tree/decision.h>
#include "drzewa_decyzyjne/enemy_in_range/enemy.h"
#include "utils/path.h"

class OnPath : public Decision {

private:
	Enemy& enemyRef;

public:
	OnPath(Enemy& enemyRef) :
		enemyRef(enemyRef) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
