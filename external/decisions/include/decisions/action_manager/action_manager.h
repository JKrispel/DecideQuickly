#pragma once
#include "Action.h"
#include <queue>
#include <set>
#include <memory>

class ActionManager
{	
	struct CompareActions {
		bool operator()(const std::unique_ptr<Action>& lhs, const std::unique_ptr<Action>& rhs) const {
			return lhs->priority > rhs->priority;  // In a priority queue, lower priority should come first
		}
	};
public:
	// unique_ptr - usuniecie Akcji z queue bedzie niszczyc obiekt
	std::priority_queue<std::unique_ptr<Action>, std::vector<std::unique_ptr<Action>>, CompareActions> queue;
	std::set<std::unique_ptr<Action>, CompareActions> active;	// Sygnalizuje, które akcje sa aktywne (isComplete() decyduje o usunieciu)
	// Obie struktury sa uporzadkowane rosnaco !!
	void scheduleAction(std::unique_ptr<Action> action);
	void execute(float currentTime);
};

// Nowa Akcja obsługiwana jest przez 2 klatki:
//      pierwsza klatka - dodanie do active i wykonanie
//      druga klatka - jeżeli complete to ją usuń

// WAŻNE: Aktywna Akcja będzie wykonywana (execute()) w kółko, co klatkę dopóki właściwość complete
// nie zmieni wartości na true.
