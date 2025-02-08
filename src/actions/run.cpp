#include "actions/run.h"
#include <raylib.h>
#include <raymath.h>

void Run::execute()
{
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(target.position, character.position));

	character.position = Vector2Add(character.position, Vector2Scale(directionVector, character.speed));
}

Pawn& Run::getTargetRef()
{
	return target;
}
