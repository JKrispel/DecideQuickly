#include "algorithms/state_machines/patrol/transition_no_patience.h"

bool TransitionNoPatience::isTriggered()
{
	if (npcRef.noPatience()) {

		return true;
	}
	return false;
}
