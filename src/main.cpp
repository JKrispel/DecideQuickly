﻿#include <thread>
#include <set>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "core/player.h"
#include "core/targetted_camera.h"
#include "parallel/worker_thread.h"
#include "core/config.h"
#include "levels/follow_dt_level.h"
#include "levels/patrol_dt_level.h"
#include "levels/follow_sm_level.h"
#include "levels/patrol_sm_level.h"
#include "levels/crowd_follow_dt_level.h"
#include "levels/crowd_follow_sm_level.h"
#include "levels/crowd_patrol_dt_level.h"
#include "levels/crowd_patrol_sm_level.h"
#include "perfo/log_execution_time.h"
#include "perfo/calculate_stats.h"
#include "perfo/log_fps.h"


int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Decide Quickly");
    SetTargetFPS(60);

    // GUI config
    int scroll = 0;
    int active = -1; // defaultowo brak wyboru w menu
    float guiScale = 1.5f;
    GuiSetStyle(DEFAULT, TEXT_SIZE, static_cast<int>(20 * guiScale));
    GuiSetStyle(DEFAULT, TEXT_SPACING, static_cast<int>(2 * guiScale));

    WorkerThread aiWorker; // równoległy wątek dla AI

    std::set<int> initializedLevels;
    std::unique_ptr<Level> activeLevel;

    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (active) {
        case -1: {
            GuiListView(Rectangle{ 0.f, static_cast<float>(GetScreenHeight()) / 16, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
               "Follow - Drzewo Decyzyjne;Patrol - Drzewo Decyzyjne;Follow - Maszyna Stanow;Patrol - Maszyna Stanow; Wykonaj obliczenia statystyczne;Follow limit testing - Drzewo decyzyjne;Patrol limit testing - Drzewo Decyzyjne;Follow limit testing - Maszyna Stanow;Patrol limit testing - Maszyna Stanow",
                &scroll, &active);
            DrawRectangle(0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16, SKYBLUE);
            GuiLabel(Rectangle{ 3.0f, 3.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) / 16 },
                " Wybierz algorytm decyzyjny:");
        } break;

        case 0: {   // Follow - Drzewo decyzyjne

            if (initializedLevels.find(0) == initializedLevels.end()) { // nie znaleziono

                activeLevel = std::make_unique<FollowDTLevel>();
                initializedLevels.insert(0); // oznacz jako załadowany
            }

            aiWorker.addTask([&]() { activeLevel->updateNpcs(); }); // Npc AI na oddzielnym wątku
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();

        } break;

        case 1: {   // Patrol - Drzewo Decyzyjne

            if (initializedLevels.find(1) == initializedLevels.end()) {

                activeLevel = std::make_unique<PatrolDTLevel>();
                initializedLevels.insert(1);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
        } break;
        
        case 2: {   // Follow - Maszyna Stanów

            if (initializedLevels.find(2) == initializedLevels.end()) {

                activeLevel = std::make_unique<FollowSMLevel>();
                initializedLevels.insert(2);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
        } break;

        case 3: {   // Patrol - Maszyna Stanów

            if (initializedLevels.find(3) == initializedLevels.end()) {

                activeLevel = std::make_unique<PatrolSMLevel>();
                initializedLevels.insert(3);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();;
        } break;      

        case 4: {   // obliczenia statystyczne
        
            std::string levelNames = "follow_dt_times;patrol_dt_times;follow_sm_times;patrol_sm_times";
            calculateLevelAverage(levelNames);   // domyślnie dla 3 plików na poziom
            std::cout << "Obliczenia zakonczone!" << std::endl;      
            active = -1;    // powrót do menu
        } break;

        case 5: {   // Follow limit testing - Drzewo decyzyjne 

            if (initializedLevels.find(5) == initializedLevels.end()) {

                activeLevel = std::make_unique<CrowdFollowDTLevel>();
                initializedLevels.insert(5);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
            EndMode2D();
            DrawFPS(10, 10);

            logFpsFrame("followDT");
        } break;

        case 6: {   // Patrol limit testing - Drzewo Decyzyjne

            if (initializedLevels.find(6) == initializedLevels.end()) {

                activeLevel = std::make_unique<CrowdPatrolDTLevel>();
                initializedLevels.insert(6);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
            EndMode2D();
            DrawFPS(10, 10);
        } break;

        case 7: {   // Follow limit testing - Maszyna Stanów

            if (initializedLevels.find(7) == initializedLevels.end()) {

                activeLevel = std::make_unique<CrowdFollowSMLevel>();
                initializedLevels.insert(7);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
            EndMode2D();
            DrawFPS(10, 10);
        } break;

        case 8: {   // Patrol limit testing - Maszyna Stanów

            if (initializedLevels.find(8) == initializedLevels.end()) {

                activeLevel = std::make_unique<CrowdPatrolSMLevel>();
                initializedLevels.insert(8);
            }
            aiWorker.addTask([&]() { activeLevel->updateNpcs(); });
            activeLevel->updatePlayer();
            BeginMode2D(activeLevel->getCameraRef());
            // renderowanie
            activeLevel->draw();
            EndMode2D();
            DrawFPS(10, 10);
        } break;

        default: {
            std::cout << "Nie wybrano opcji" << std::endl;
        } break;
        }
        // obsługa żądania pauzy
        if (activeLevel) {
            Player& playerRef = activeLevel->getPlayerRef();

            if (playerRef.callForPause()) {
                active = -1;
                playerRef.clearPauseCall();
                initializedLevels.clear();
                activeLevel.reset();
            }
        }
        EndDrawing();
    }
    aiWorker.stop();
    CloseWindow();
    return 0;
}
