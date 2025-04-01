#pragma once
#include <raylib.h>
#include <condition_variable>
#include <external/stb_rect_pack.h>

// virtual class
class Pawn {

private:
	int hp = 100;
	Vector2 position;
	float speed;
	float radius;
	Color color;
	std::mutex pawnMutex;
	bool newUpdate = false;
	std::condition_variable updateCondition;

public:
	Pawn(float x, float y, float speed, float radius, Color color = BLANK)
		: position{ x, y }, speed(speed), radius(radius), color(color) {}
	virtual ~Pawn() = default;

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void dealDmg(int hpAmount);
	virtual void healPawn(int hpAmount);
	int getHp();
	float getSpeed();
	float getHitboxRadius();
	Vector2 getPosition();
	void setPosition(float newX, float newY);
	void moveTo(Vector2 destination);
	void setColor(Color newColor);
	Color getColor();

protected:	// funkcje synchronizujące obliczenia AI oraz render
	void updateFinished();
	void drawAfterUpdate();
};