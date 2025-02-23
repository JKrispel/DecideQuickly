#pragma once
#include "drzewa_decyzyjne/enemy_in_range/enemy.h"
#include <raylib.h>
#include <decisions/action_manager/action.h>

class ChangeDirection : public Action {
private:
	Enemy& enemyRef;

public:
	ChangeDirection(Enemy& enemyRef) : Action(1.0f), enemyRef(enemyRef) {}

	void execute() override;
};
