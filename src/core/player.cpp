#include "player.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>

void Player::draw()
{
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, RED);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f * (this->getHp()) / 100, 5.0f, GREEN);
	DrawCircle(position.x, position.y, radius, WHITE);
}

void Player::update()
{	
	double now = GetTime();  // czas w sekundach
	bool canRegen = (now - regenTime) > regenDelay;

	if (canRegen && (getHp() + regenAmount <= 100)) {
		regenTime = now;
		this->healPawn(regenAmount);
	}
	Vector2 direction = Vector2Zero();
	
	if (IsKeyDown(KEY_UP) && position.y >= area.y + radius) {
		direction.y -= speed;
	}
	if (IsKeyDown(KEY_DOWN) && position.y <= area.y + area.height - radius) {
		direction.y += speed;
	}
	if (IsKeyDown(KEY_LEFT) && position.x >= area.x + radius) {
		direction.x -= speed;
	}
	if (IsKeyDown(KEY_RIGHT) && position.x <= area.x + area.width - radius) {
		direction.x += speed;
	}

	position = Vector2Add(position, Vector2Scale(Vector2Normalize(direction), speed));
}

void Player::dealDmg(int hpAmount)
{
	Pawn::dealDmg(hpAmount); // funkcja klasy bazowej
	double now = GetTime();  // czas w sekundach
	regenTime = now;	// wydłużamy czas następnego leczenia
}
