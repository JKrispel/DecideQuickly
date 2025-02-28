#include "player.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

Player::Player() : Pawn() {
	setPosition(screen_width / 2, screen_height / 2);
	radius = player_hitbox_radius;
	speed = 7.0f;
	upperLimit = bounds.y + radius;
	bottomLimit = bounds.y + bounds.height - radius;
	leftLimit = bounds.x + radius;
	rightLimit = bounds.x + bounds.width - radius;
	animation = std::make_unique<PlayerAnimation>();
};

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
	//animation->updateRotation(atan2(-direction.y, direction.x) * (180.0f / PI));
	animation->updateDirection(direction);
	position = Vector2Add(position, Vector2Scale(Vector2Normalize(direction), speed));
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
