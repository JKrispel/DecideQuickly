#pragma once
#include "decisions/state_machine/transition.h"
#include "core/pawn.h"

class TransitionFarEnough : public Transition {

private:
	float threshold{};
	Pawn& target1;
	Pawn& target2;

public:
	TransitionFarEnough(float threshold, Pawn& target1, Pawn& target2,int targetStateIndex, int transitionAction):
		Transition(targetStateIndex, transitionAction),
		threshold(threshold),
		target1(target1),
		target2(target2) {};

	bool isTriggered();
};