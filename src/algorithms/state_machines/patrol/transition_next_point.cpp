#include "algorithms/state_machines/patrol/transition_next_point.h"
#include "raylib.h"

bool TransitionNextPoint::isTriggered()
{
    double now = GetTime();  // czas w sekundach

    // debounce
    if (now - npcRef.directionChangeTime < npcRef.directionChangeDelay) {

        return false;
    }
    if (npcRef.getPathRef().onPoint()) {

        npcRef.getPathRef().nextPathPoint();
        npcRef.directionChangeTime = now;
        return true;
    }
    else return false;
}
