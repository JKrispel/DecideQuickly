#pragma once
#include <vector>
#include <memory>
#include "raylib.h"
#include "core/config.h"
#include "core/log_state.h"
#include "core/player.h"
#include "core/npc.h"
#include "core/targetted_camera.h"
#include "render/floor.h"

#include <iostream>
class Level {
private:
    Floor floor = Floor("resources/floor/floor_tiles.png", screen_width, screen_height);
    std::unique_ptr<TargettedCamera> playerCameraPtr;  // kamera gracza

public:
    Level() {
        // dodawanie Npc
        // npcs.push_back(std::make_unique<ExampleNpc>(x, y, speed, radius, target, color));
        playerPtr = std::make_unique<Player>();
        playerCameraPtr = std::make_unique<TargettedCamera>(*playerPtr);
        resetLoggingSession();
    }
    virtual ~Level() {}

    void updateNpcs();
    void updatePlayer();
    void draw();
    Camera2D& getCameraRef();
    Player& getPlayerRef();

protected:
    std::vector<std::unique_ptr<Npc>> npcPtrs;
    std::unique_ptr<Player> playerPtr;
};
