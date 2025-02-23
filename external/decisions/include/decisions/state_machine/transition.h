#pragma once

// Forward declaration
class State;

// virtual class
class Transition {

private:
	int targetStateIndex;
	int transitionAction;

public:
	Transition(int targetStateIndex, int transitionAction): 
		targetStateIndex(targetStateIndex), transitionAction(transitionAction) {};
	virtual bool isTriggered() = 0;	// własny warunek logiczny
	int getTargetStateIndex();	// Stan do którego prowadzi
	int getAction();	// towarzysząca Akcja
};
