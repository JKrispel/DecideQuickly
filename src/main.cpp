#include <thread>
#include <set>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "core/player.h"
#include "decision_trees/distance_decision/npc_follow_dt.h"
#include "decision_trees/enemy_in_range/enemy_patrol_dt.h"
#include "core/targetted_camera.h"
#include "utils/log_execution_time.h"
#include "state_machines/follow/npc_follow_sm.h"
#include "parallel/worker_thread.h"
#include "render/floor.h"
#include "core/config.h"

int main(void)
{



    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Decide Quickly");
    SetTargetFPS(60);


    Player player; 
    TargettedCamera gameCamera = TargettedCamera(player);   // kamera gracza

    // npc i enemy otrzymują jako target gracza
    // Drzewa decyzyjne
    auto npcDTptr = std::make_unique<NpcFollowDT>(player);
    auto enemyDTptr = std::make_unique<EnemyPatrolDT>(player);

    // Maszyny Stanów
    auto npcSMptr = std::make_unique<NpcFollowSM>(player);

    // GUI config
    int scroll = 0;
    int active = -1; // defaultowo brak wyboru w menu
    float guiScale = 1.5f;
    GuiSetStyle(DEFAULT, TEXT_SIZE, static_cast<int>(20 * guiScale));
    GuiSetStyle(DEFAULT, TEXT_SPACING, static_cast<int>(2 * guiScale));

    WorkerThread aiWorker; // równoległy wątek
    // TODO
    // wybór w menu powinien czyścić stan gry, ładować na nowo potrzebne assety (structs)
    std::set<int> initializedLevels;
    Floor floor("resources/floor/floor_tiles.png", screen_width, screen_height);
    
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
                initializedLevels.insert(0); // oznacz jako załadowany
            }
            aiWorker.addTask([&]() { npcDTptr->update(); });  // here the main thread needs to finish queueing
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            player.update();
            // renderowanie
            ClearBackground(BLACK);
            floor.draw();
            player.draw();
            npcDTptr->draw(); // in order to get to this point
        } break;

        case 1: {   // Patrol - Drzewo Decyzyjne

            if (initializedLevels.find(1) == initializedLevels.end()) {

                // TODO załaduj assety
                initializedLevels.insert(1);
            }
            aiWorker.addTask([&]() { enemyDTptr->update(); });
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            player.update();

            ClearBackground(BLACK);
            floor.draw();
            player.draw();
            enemyDTptr->draw();
        } break;
        
        case 2: {   // Follow - Maszyna Stanów

            if (initializedLevels.find(1) == initializedLevels.end()) {

                // TODO załaduj assety
                initializedLevels.insert(1);
            }
            aiWorker.addTask([&]() { npcSMptr->update(); });
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            player.update();

            ClearBackground(BLACK);
            floor.draw();
            player.draw();
            npcSMptr->draw();
        } break;

        case 3: {   // nowy algorytm (WIP)  
            BeginMode2D(gameCamera.getCameraRef());
            gameCamera.updateCamera();
            player.update();

            ClearBackground(BLACK);
            floor.draw();
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
