#include "algorithms/state_machines/patrol/transition_aggro.h"

bool TransitionAggro::isTriggered()
{
    // debounce
    if (npcRef.noPatience()) {

        return false;
    }

    if (npcRef.distanceToTarget() < aggroThreshold) {

        return true;
    }
    else {

        return false;
    }
}
