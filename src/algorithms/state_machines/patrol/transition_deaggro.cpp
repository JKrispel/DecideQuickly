#include "algorithms/state_machines/patrol/transition_deaggro.h"

bool TransitionDeaggro::isTriggered() {

    if (npcRef.distanceToTarget() < aggroThreshold) {

        return true;
    }
    else {

        return false;
    }
}