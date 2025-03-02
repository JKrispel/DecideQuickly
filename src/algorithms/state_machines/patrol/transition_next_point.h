#pragma once
#include "decisions/state_machine/transition.h"
#include "core/npc.h"

class TransitionNextPoint : public Transition {

private:
	Npc& npcRef;

public:
	TransitionNextPoint(Npc& npcRef, int targetStateIndex, int transitionAction) : 
		Transition(targetStateIndex, transitionAction), npcRef(npcRef) {}
	bool isTriggered() override;
};