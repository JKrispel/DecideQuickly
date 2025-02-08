#pragma once
#include <decisions/decision_tree/decision.h>
#include "core/enemy.h"

class DistanceFromPath : public Decision {

private:
	float distanceThreshold = 400.0f;	// próg oddalenia się od ścieżki, hardcoded by design
	Enemy& enemyRef;

public:
	DistanceFromPath(Enemy& enemyRef) :
		enemyRef(enemyRef) {};

	std::unique_ptr<DecisionTreeNode> getBranch();
};
