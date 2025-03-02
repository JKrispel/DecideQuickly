#include "transition_far_enough.h"
#include "raylib.h"
#include "raymath.h"

bool TransitionFarEnough::isTriggered()
{
	float distance = Vector2Distance(target1.getPosition(), target2.getPosition());

	if (distance > threshold) {

		return true;
	}
	else {
		return false;
	}
}
