#include <thread>
#include <set>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "core/player.h"
#include "drzewa_decyzyjne/distance_decision/npc.h"
#include "drzewa_decyzyjne/enemy_in_range/enemy.h"
#include "core/targetted_camera.h"
#include "utils/log_execution_time.h"
#include "maszyny_stanów/follow/npc_follow_sm.h"
#include "parallel/ai_worker_thread.h"

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
    player.setPosition(Vector2{ screen_width / 2, screen_height / 2 });
    player.radius = 20;
    player.speed = 7;
    player.area = map_bounds;

    // kamera gracza
    TargettedCamera gameCamera = TargettedCamera(player);

    // npc i enemy otrzymują jako target gracza
    // Drzewa decyzyjne
    Npc npc = Npc(player);
    npc.setPosition(Vector2{ 50.0f, 50.0f});
    npc.radius = 20;
    npc.speed = 4;

    Enemy enemy = Enemy(player);
    enemy.setPosition(Vector2{ 50.0f, 100.0f });
    enemy.radius = 20;
    enemy.speed = 4;

    // Maszyny Stanów
    NpcFollowSM npcSM = NpcFollowSM(player);
    npcSM.setPosition(Vector2{ 50.0f, 50.0f });
    npcSM.radius = 20;
    npcSM.speed = 4;

    // GUI config
    int scroll = 0;
    int active = -1; // defaultowo brak wyboru w menu
    float guiScale = 1.5f;
    GuiSetStyle(DEFAULT, TEXT_SIZE, static_cast<int>(20 * guiScale));
    GuiSetStyle(DEFAULT, TEXT_SPACING, static_cast<int>(2 * guiScale));

    AIWorkerThread aiWorker; // parallel thread
    // TODO
    // wybór w menu powinien czyścić stan gry, ładować na nowo potrzebne assety (structs)
    std::set<int> initializedLevels;

        while (!WindowShouldClose()) {
            BeginDrawing();

            switch (active) {
            case -1: {
                GuiListView(Rectangle{ 0.f, static_cast<float>(GetScreenHeight()) / 16, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
                    "Follow - Drzewo Decyzyjne;Patrol - Drzewo Decyzyjne;Follow - Maszyna Stanow; Coming Soon",
                    &scroll, &active);
                DrawRectangle(0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16, SKYBLUE);
                GuiLabel(Rectangle{ 3.0f, 3.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16 },
                    " Wybierz algorytm decyzyjny:");
            } break;

            case 0: {   // Follow - Drzewo decyzyjne

                if (initializedLevels.find(0) == initializedLevels.end()) { // nie znaleziono

                    // TODO załaduj assety
                    initializedLevels.insert(0);    // oznacz jako załadowany
                }
                aiWorker.addTask([&]() { npc.update(); });
                BeginMode2D(gameCamera.getCameraRef());
                gameCamera.updateCamera();
                player.update();
                // renderowanie
                ClearBackground(BLACK);
                DrawRectangleRec(map_bounds, DARKPURPLE);
                player.draw();
                npc.draw();
            } break;

            case 1: {   // Patrol - Drzewo Decyzyjne

                if (initializedLevels.find(1) == initializedLevels.end()) {

                    // TODO załaduj assety
                    initializedLevels.insert(1);
                }
                aiWorker.addTask([&]() { enemy.update(); });
                BeginMode2D(gameCamera.getCameraRef());
                gameCamera.updateCamera();
                player.update();

                ClearBackground(BLACK);
                DrawRectangleRec(map_bounds, DARKPURPLE);
                player.draw();
                enemy.draw();
            } break;
        
            case 2: {   // Follow - Maszyna Stanów

                if (initializedLevels.find(1) == initializedLevels.end()) {

                    // TODO załaduj assety
                    initializedLevels.insert(1);
                }
                aiWorker.addTask([&]() { npcSM.update(); });
                BeginMode2D(gameCamera.getCameraRef());
                gameCamera.updateCamera();
                player.update();

                ClearBackground(BLACK);
                DrawRectangleRec(map_bounds, DARKPURPLE);
                player.draw();
                npcSM.draw();
            } break;

            case 3: {   // nowy algorytm (WIP)  
                BeginMode2D(gameCamera.getCameraRef());
                gameCamera.updateCamera();
                player.update();

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
                // TODO zniszcz wszystkie assety
                initializedLevels.clear();
            }
            EndDrawing();
        }
        aiWorker.stop();
        CloseWindow();
        return 0;
    }
