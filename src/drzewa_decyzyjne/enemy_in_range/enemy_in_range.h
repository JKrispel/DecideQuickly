#pragma once
#include <decisions/decision_tree/decision.h>
#include <memory>
#include "utils/path.h"

class Enemy;

class EnemyInRange : public Decision {

private:
	float aggroThreshold = 300.0f;	// próg dla wykrycia, hardcoded by design
	Enemy& enemyRef;

public:
	EnemyInRange(Enemy& enemyRef);

	std::unique_ptr<DecisionTreeNode> getBranch();
};
