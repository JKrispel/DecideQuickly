#include "core/pawn.h"
#include "raylib.h"
#include "raymath.h"

void Pawn::dealDmg(int hpAmount)
{
	hp -= hpAmount;
}

void Pawn::healPawn(int hpAmount)
{
	if (hp + hpAmount > 100) {

		hp = 100;
	}
	else {
		hp += hpAmount;
	}
}

int Pawn::getHp()
{
	return hp;
}

Vector2 Pawn::getPosition()
{
	return position;
}

void Pawn::setPosition(float newX, float newY)
{
	position = Vector2{ newX, newY };
}

float Pawn::getSpeed()
{
	return speed;
}

float Pawn::getHitboxRadius()
{
	return radius;
}

void Pawn::moveTo(Vector2 destination)
{
	Vector2 position = this->getPosition();
	Vector2 directionVector = Vector2Normalize(Vector2Subtract(destination, position));
	position = Vector2Add(position, Vector2Scale(directionVector, getSpeed()));
	setPosition(position.x, position.y);
}

void Pawn::setColor(Color newColor)
{
	color = newColor;
}

Color Pawn::getColor()
{
	return color;
}

void Pawn::updateFinished()
{
	{
		std::lock_guard<std::mutex> lock(pawnMutex);
		newUpdate = true;
	}
	updateCondition.notify_one();
}

void Pawn::drawAfterUpdate()
{
	std::unique_lock<std::mutex> lock(pawnMutex);
	updateCondition.wait(lock, [this] { return newUpdate; });  // renderuje dopiero jak zajdzie zmiana
	newUpdate = false;
}
