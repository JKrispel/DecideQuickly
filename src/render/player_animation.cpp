#include "render/player_animation.h"
#include <iostream>
void PlayerAnimation::updateRotation(float newRotation)
{
	rotation = newRotation;
}

void PlayerAnimation::updateDirection(Vector2 newDirection)
{
	direction = newDirection;
}

void PlayerAnimation::animate(Vector2 position)
{
	// texture offset
	position.x = position.x - (0.53f * player_hitbox_radius) * player_sprite_scale;
	position.y = position.y - (1.3f * player_hitbox_radius) * player_sprite_scale;

	//DrawTextureEx(up, position, rotation, player_sprite_scale, WHITE);
	//std::cout << "Rotation = " << rotation << std::endl;

	if (direction.y == -1.0f) {
		
		DrawTextureEx(up, position, 0, player_sprite_scale, WHITE);
	}
	else if (direction.y == 1.0f) {
		DrawTextureEx(down, position, 0, player_sprite_scale, WHITE);
	}
	else if (direction.x == -1.0f) {
		DrawTextureEx(left, position, 0, player_sprite_scale, WHITE);
	}
	else if (direction.x == 1.0f) {
		DrawTextureEx(right, position, 0, player_sprite_scale, WHITE);
	}
	else {
		DrawTextureEx(down, position, 0, player_sprite_scale, WHITE);
	}
	std::cout << "Direction = " << direction.x << ", " <<direction.y<< std::endl;
}
