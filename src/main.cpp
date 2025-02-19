﻿#include <thread> // For multithreading
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "core/player.h"
#include "core/npc.h"
#include "core/enemy.h"
#include "core/targetted_camera.h"
#include <iostream>
	
int main(void)
{
    const int screen_width = 1920;
    const int screen_height = 1080;

    Rectangle map_bounds{};
    map_bounds.height = float(screen_height) - 20.0f;
    map_bounds.width = float(screen_width) - 20.0f;
    map_bounds.x = 10.0f;
    map_bounds.y = 10.0f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "Decide Quickly");
    SetTargetFPS(60);


    Player player;
    player.position.x = screen_width / 2;
    player.position.y = screen_height / 2;
    player.radius = 20;
    player.speed = 7;
    player.area = map_bounds;

    // kamera gracza
    TargettedCamera gameCamera = TargettedCamera(player);

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
    // GUI config
    int scroll = 0;
    int active = -1; // defaultowo brak wyboru w menu
    float guiScale = 1.5f; // Scale factor (1.0 = normal size)
    GuiSetStyle(DEFAULT, TEXT_SIZE, static_cast<int>(20 * guiScale)); // Default size is 10px
    GuiSetStyle(DEFAULT, TEXT_SPACING, static_cast<int>(2 * guiScale)); // Adjust spacing

    // TODO
    // wybór w menu powinien czyścić stan gry, ładować na nowo potrzebne assety
    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (active) {
        case -1: {
            GuiListView(Rectangle{ 0.f, static_cast<float>(GetScreenHeight()) / 16, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
                "Follow - Drzewa Decyzyjne;Patrol - Drzewa Decyzyjne;Coming Soon",
                &scroll, &active);
            DrawRectangle(0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16, SKYBLUE);
            GuiLabel(Rectangle{ 3.0f, 3.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16 },
                " Wybierz algorytm decyzyjny:");
            std::cout << "Selected: " << active << std::endl;
        } break;

        case 0: {   // Follow - Drzewa decyzyjne
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            std::thread npcThread([&]() { npc.update(); });
            player.update();
            npcThread.join();   // czekanie na wątek
            // renderowanie
            ClearBackground(BLACK);
            DrawRectangleRec(map_bounds, DARKPURPLE);
            player.draw();
            npc.draw();
        } break;

        case 1: {   // Patrol - Drzewa Decyzyjne
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            std::thread enemyThread([&]() { enemy.update(); });
            player.update();
            enemyThread.join();
            // renderowanie
            ClearBackground(BLACK);
            DrawRectangleRec(map_bounds, DARKPURPLE);
            player.draw();
            enemy.draw();
        } break;

        case 2: {   // nowy algorytm (WIP)  
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            player.update();
            // renderowanie
            ClearBackground(BLACK);
            DrawRectangleRec(map_bounds, DARKPURPLE);
            player.draw();
        } break;

        default: {
            std::cout << "Nie wybrano opcji" << std::endl;
        } break;
        }
        // obsługa żądania pauzy
        if (player.callForPause()) {
            active = -1;
            player.clearPauseCall();
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
