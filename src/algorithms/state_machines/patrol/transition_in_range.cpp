#include "algorithms/state_machines/patrol/transition_next_point.h"
#include "transition_in_range.h"

bool TransitionInRange::isTriggered()
{

    if (npcRef.getPathRef().distanceToPath() < pathThreshold
        && npcRef.distanceToTarget() < targetThreshold) {

        return true;
    }
    return false;
}
