#include "targetted_camera.h"

TargettedCamera::TargettedCamera(Pawn& target): target(target)
{
    camera.offset = Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
    camera.target = Vector2{ target.position.x, target.position.y };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;
}

void TargettedCamera::updateCamera()
{
    camera.offset = Vector2{ static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
    camera.target = Vector2{ target.position.x, target.position.y };
}

Camera2D& TargettedCamera::getCameraRef()
{
    return camera;
}

