#include "actions/walk.h"
#include <raylib.h>
#include <raymath.h>

void Walk::execute()
{
	Vector2 characterPosition = character.getPosition();
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(target.getPosition(), characterPosition));
	characterPosition = Vector2Add(characterPosition, Vector2Scale(directionVector, character.getSpeed() / 3));
	character.setPosition( characterPosition.x, characterPosition.y);
	this->complete = true;
}
