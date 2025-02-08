#pragma once
#include "core/enemy.h"
#include <raylib.h>
#include <decisions/action_manager/action.h>

class Chase : public Action {
private:
	Enemy& enemyRef;

public:
	Chase(Enemy& enemyRef) : Action(1.0f), enemyRef(enemyRef) {}


	void execute() override;
};
