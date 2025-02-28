#pragma once
#include <raylib.h>
#include <condition_variable>

// virtual class
class Pawn {

private:
	int hp = 100;
	Vector2 position{};

	std::mutex pawnMutex;
	bool newUpdate = false;
	std::condition_variable updateCondition;

public:
	float speed{};	// przenieść do
	float radius{};	// sekcji prywatnej
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void dealDmg(int hpAmount);
	virtual void healPawn(int hpAmount);
	int getHp();
	Vector2 getPosition();
	void setPosition(float newX, float newY);

protected:	// funkcje synchronizujące obliczenia AI oraz render
	void updateFinished();
	void drawAfterUpdate();
};