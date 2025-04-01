#pragma once
#include <unordered_map>
#include "core/npc.h"
#include "utils/npc_action.h"
#include "decisions/action_manager/action.h"
#include "decisions/state_machine/state_machine.h"

class EnemyPatrolSM : public Npc {

private:
	std::unique_ptr<StateMachine> stateMachine;	// algorytm AI
	std::unordered_map<int, std::unique_ptr<Action>> npcActions;

public:
	EnemyPatrolSM(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);

	void update() override;
	void draw() override;
};
