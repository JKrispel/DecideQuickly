#include <raylib.h>
#include <iostream>
#include "core/player.h"
#include "core/npc.h"
#include "core/enemy.h"


int main(void)
{
	const int screen_width = 1280;
	const int screen_height = 800;

	Rectangle map_bounds{};
	map_bounds.height = float(screen_height) - 20.0f;
	map_bounds.width = float(screen_width) - 20.0f;
	map_bounds.x = 10.0f;
	map_bounds.y = 10.0f;

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screen_width, screen_height, "Decide Quickly");
	SetTargetFPS(60);


	Player player;
	player.position.x = screen_width / 2;
	player.position.y = screen_height / 2;
	player.radius = 20;
	player.speed = 7;
	player.area = map_bounds;

	// npc i enemy otrzymują jako target gracza
	Npc npc = Npc(player);
	npc.position.x = 50.f;
	npc.position.y = 50.f;
	npc.radius = 20;
	npc.speed = 4;

	Enemy enemy = Enemy(player);
	enemy.position.x = 50.f;
	enemy.position.y = 100.f;
	enemy.radius = 20;
	enemy.speed = 4;


	while (!WindowShouldClose()) {
	

		// Updating
		npc.update();	// w środku zawarta logika AI
		enemy.update();
		player.update();


		// Drawing
		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRec(map_bounds, DARKPURPLE);
		player.draw();
		npc.draw();
		enemy.draw();

		EndDrawing();
	}
	CloseWindow();
	return 0;
}