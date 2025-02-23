#pragma once
#include <memory>
#include <vector>
#include "decisions/state_machine/transition.h"

class State {

private:
	std::vector<std::unique_ptr<Transition>> transitions;	// przejścia ze Stanu
	int stateAction{};
	int entryAction{};
	int exitAction{};

public:
	State(int stateAction, int entryAction, int exitAction);

	int getStateAction();
	int getEntryAction();
	int getExitAction();
	void addTransition(std::unique_ptr<Transition> transition);	// dodaje Przejście ze Stanu
	std::vector<std::unique_ptr<Transition>>& getTransitionsRef();
};

