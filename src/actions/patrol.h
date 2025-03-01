#pragma once
#include "raylib.h"
#include "decisions/action_manager/action.h"
#include "core/npc.h"

class Patrol : public Action {
private:
	Npc& npcRef;

public:
	Patrol(Npc& npcRef) : Action(1.0f), npcRef(npcRef) {}

	void execute() override;
};
