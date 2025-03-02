#pragma once
#include "core/npc.h"
#include <memory>
#include <unordered_map>
#include "utils/npc_action.h"
#include "decisions/action_manager/action.h"
#include "decisions/state_machine/state_machine.h"


class NpcFollowSM : public Npc {

private:
	std::unique_ptr<StateMachine> stateMachine;	// algorytm AI
	std::unordered_map<NpcAction, std::unique_ptr<Action>> npcActions;

public:
	NpcFollowSM(float x, float y, float speed, float radius, Pawn& targetRef, Color color = BLANK);

	void update() override;
	void draw() override;
};