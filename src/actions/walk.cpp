#include "actions/walk.h"
#include <raylib.h>
#include <raymath.h>

void Walk::execute()
{
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(target.position, character.position));

	character.position = Vector2Add(character.position, Vector2Scale(directionVector, character.speed / 2));
	this->complete = true;
}
