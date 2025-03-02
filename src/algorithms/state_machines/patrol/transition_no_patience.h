#pragma once
#include "decisions/state_machine/transition.h"
#include "core/npc.h"

class TransitionNoPatience : public Transition {

private:
	Npc& npcRef;

public:
	TransitionNoPatience(Npc& npcRef, int targetStateIndex, int transitionAction) :
		Transition(targetStateIndex, transitionAction), npcRef(npcRef) {
	}
	bool isTriggered() override;
};