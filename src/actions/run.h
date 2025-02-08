#pragma once
#include "core/pawn.h"
#include <decisions/action_manager/action.h>

class Run: public Action {
private:
	Pawn& character;
	Pawn& target;	// tu powinien być Vector2 tbh


public:
	Run(Pawn& character, Pawn& target): Action(1.0f), character(character), target(target) {}

	void execute() override;
	Pawn& getTargetRef();
};
