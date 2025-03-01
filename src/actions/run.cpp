#include "actions/run.h"
#include <raylib.h>
#include <raymath.h>

void Run::execute()
{
	Vector2 characterPosition = character.getPosition();
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(target.getPosition(), characterPosition));
	characterPosition = Vector2Add(characterPosition, Vector2Scale(directionVector, character.getSpeed()));
	character.setPosition(characterPosition.x, characterPosition.y);
}

Pawn& Run::getTargetRef()
{
	return target;
}
