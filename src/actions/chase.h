#pragma once
#include "raylib.h"
#include "decisions/action_manager/action.h"
#include "core/npc.h"

class Chase : public Action {
private:
	Npc& npcRef;

public:
	Chase(Npc& npcRef) : Action(1.0f), npcRef(npcRef) {}


	void execute() override;
};
