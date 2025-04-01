#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include "decisions/state_machine/state.h"


class StateMachine {

private:
	int currentStateIndex = 0;
	std::vector<State> machineStates;

public:
	StateMachine(int initialStateAction, int entryAction, int exitAction);
	~StateMachine() = default;

	std::unique_ptr<std::vector<int>> update();	// przejście Maszyny
	void addState(int additionalStateAction, int entryAction, int exitAction);	// dodaje dodatkowy Stan do Maszyny
	void addTransition(int stateIndex, std::unique_ptr<Transition> transitionPtr);
};
