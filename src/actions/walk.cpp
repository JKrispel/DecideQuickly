#include "actions/walk.h"
#include <raylib.h>
#include <raymath.h>

void Walk::execute()
{
	Vector2 characterPosition = character.getPosition();
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(target.getPosition(), characterPosition));

	character.setPosition(Vector2Add(characterPosition, Vector2Scale(directionVector, character.speed / 3)));
	this->complete = true;
}
