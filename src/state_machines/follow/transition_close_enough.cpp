#include "transition_close_enough.h"
#include "raylib.h"
#include "raymath.h"


bool TransitionCloseEnough::isTriggered()
{
	float distance = Vector2Distance(target1.getPosition(), target2.getPosition());

	if (distance < threshold) {

		return true;
	}
	else {
		return false;
	}
}
