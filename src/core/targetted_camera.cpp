#include "targetted_camera.h"

TargettedCamera::TargettedCamera(Pawn& target): target(target)
{
    camera.offset = Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
    camera.target = Vector2{ target.getPosition().x, target.getPosition().y};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f; // domyślne przybliżenie kamery
}

void TargettedCamera::updateCamera()
{
    camera.offset = Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
    camera.target = Vector2{ target.getPosition().x, target.getPosition().y};

    if (IsKeyPressed(KEY_UP) && camera.zoom < 3.0f) {

        camera.zoom += 0.2;
    }
    if (IsKeyPressed(KEY_DOWN) && camera.zoom > 0.5f) {

        camera.zoom -= 0.2;
    }
}

Camera2D& TargettedCamera::getCameraRef()
{
    return camera;
}

