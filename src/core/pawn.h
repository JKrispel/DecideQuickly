#pragma once
#include <raylib.h>

// virtual class
class Pawn {

private:
	int hp = 100;
	Vector2 position{};

public:
	float speed{};
	int radius{};
	Rectangle area{};

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void dealDmg(int hpAmount);
	virtual void healPawn(int hpAmount);
	int getHp();
	Vector2 getPosition();
	void setPosition(Vector2 newPosition);
};