#include "core/level.h"

void Level::updateNpcs()
{
    for (auto& npc : npcPtrs) {
        npc->update();
    }
}

void Level::updatePlayer()
{
    playerPtr->update();
    playerCameraPtr->updateCamera();
}

void Level::draw()
{
    ClearBackground(BLACK);
    floor.draw();
    for (auto& npc : npcPtrs) {
        npc->draw();
    }
    playerPtr->draw();
}

Camera2D& Level::getCameraRef()
{
    return playerCameraPtr->getCameraRef();
}

Player& Level::getPlayerRef()
{
    return *playerPtr;
}
