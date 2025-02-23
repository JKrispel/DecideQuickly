#pragma once
#include "core/pawn.h"
#include <memory>
#include <unordered_map>
#include "utils/npc_action.h"
#include "decisions/action_manager/action.h"
#include "decisions/state_machine/state_machine.h"


class NpcFollowSM : public Pawn {

private:
	std::unique_ptr<StateMachine> stateMachine;	// algorytm AI
	Pawn& target;
	std::unordered_map<NpcAction, std::unique_ptr<Action>> npcActions;

public:
	NpcFollowSM(Pawn& target);
	void update() override;
	void draw() override;
};