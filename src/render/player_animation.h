#pragma once
#include <vector>
#include "raylib.h"
#include "core/config.h"

class PlayerAnimation {

private:
	Vector2 direction{ 1.0f, 0.0f };
	Texture2D up = LoadTexture("resources/player/player_up.png");
	Texture2D left = LoadTexture("resources/player/player_left.png");
	Texture2D right = LoadTexture("resources/player/player_right.png");
	Texture2D down = LoadTexture("resources/player/player_down.png");
	Texture2D dead = LoadTexture("resources/player/player_dead.png");
	
public:
	void updateDirection(Vector2 newDirection);
	void animate(Vector2 position);
};