#pragma once
#include "decisions/state_machine/transition.h"
#include "core/npc.h"

class TransitionDeaggro : public Transition {

private:
	Npc& npcRef;
	float aggroThreshold = 300.0f;	// próg dla wykrycia, hardcoded by design

public:
	TransitionDeaggro(Npc& npcRef, int targetStateIndex, int transitionAction) :
		Transition(targetStateIndex, transitionAction), npcRef(npcRef) {
	};

	bool isTriggered() override;
};