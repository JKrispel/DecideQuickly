#pragma once
#include <memory>
#include "raylib.h"
#include "core/pawn.h"

class TargettedCamera {

private:
	Camera2D camera;
	Pawn& target;

public:
	TargettedCamera(Pawn& target);
	void updateCamera();
	Camera2D& getCameraRef();
};