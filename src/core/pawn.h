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

protected:	// funkcje synchronizujące obliczenia i render
	void updateFinished();
	void drawAfterUpdate();
};