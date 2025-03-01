#include "player.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

Player::Player()
	: Pawn(screen_width / 2, screen_height / 2, 7.0f, player_hitbox_radius),
	upperLimit(bounds.y + player_hitbox_radius),
	bottomLimit(bounds.y + bounds.height - player_hitbox_radius),
	leftLimit(bounds.x + player_hitbox_radius),
	rightLimit(bounds.x + bounds.width - player_hitbox_radius),
	animation(std::make_unique<PlayerAnimation>()) {}

void Player::draw()
{
	Vector2 position = getPosition();
	DrawRectangle(position.x - 28.0f, position.y - (2.2 * player_hitbox_radius + 2.0f), 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 26.0f, position.y - (2.2 * player_hitbox_radius), 51.0f, 5.0f, RED);
	DrawRectangle(position.x - 26.0f, position.y - (2.2 * player_hitbox_radius), 51.0f * (this->getHp()) / 100, 5.0f, GREEN);
	animation->animate(position);
}

void Player::update()
{	
	if (IsKeyPressed(KEY_TAB)) {
		paused = true;
	}

	double now = GetTime();  // czas w sekundach
	bool canRegen = (now - regenTime) > regenDelay;

	if (canRegen && (getHp() + regenAmount <= 100)) {
		regenTime = now;
		this->healPawn(regenAmount);
	}
	Vector2 direction = Vector2Zero();
	Vector2 position = getPosition();

	if (IsKeyDown(KEY_W) && position.y >= upperLimit) {
		direction.y -= 1;
	}
	if (IsKeyDown(KEY_S) && position.y <= bottomLimit) {
		direction.y += 1;
	}
	if (IsKeyDown(KEY_A) && position.x >= leftLimit) {
		direction.x -= 1;
	}
	if (IsKeyDown(KEY_D) && position.x <= rightLimit) {
		direction.x += 1;
	}
	animation->updateDirection(direction);
	position = Vector2Add(position, Vector2Scale(Vector2Normalize(direction), getSpeed()));
	setPosition(position.x, position.y);
}

void Player::dealDmg(int hpAmount)
{
	Pawn::dealDmg(hpAmount); // funkcja klasy bazowej
	double now = GetTime();  // czas w sekundach
	regenTime = now;	// wydłużamy czas następnego leczenia
}

bool Player::callForPause() const
{
	return paused;
}

void Player::clearPauseCall()
{
	paused = false;
}
