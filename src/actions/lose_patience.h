#pragma once
#include "raylib.h"
#include "decisions/action_manager/action.h"
#include "core/npc.h"

class LosePatience : public Action {
private:
	Npc& npcRef;

public:
	LosePatience(Npc& npcRef) : Action(1.0f), npcRef(npcRef) {}

	void execute() override;
};
