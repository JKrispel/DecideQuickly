#pragma once
#include "decisions/state_machine/transition.h"
#include "core/npc.h"

class TransitionInRange : public Transition {

private:
	float pathThreshold = 400.0f;
	float targetThreshold = 300.0f;
	Npc& npcRef;

public:
	TransitionInRange(Npc& npcRef, int targetStateIndex, int transitionAction) :
		Transition(targetStateIndex, transitionAction), npcRef(npcRef) {
	}
	bool isTriggered() override;
};