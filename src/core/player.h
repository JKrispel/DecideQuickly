#pragma once
#include <core/pawn.h>

class Player: public Pawn {

private:
	bool paused = false;
	int regenAmount = 10;	// szybkość regeneracji
	double regenTime = 0.0;
	const double regenDelay = 0.5;  // dmg debounce
public:
	void draw() override;
	void update() override;
	void dealDmg(int hpAmount) override;
	bool callForPause() const;
	void clearPauseCall();
};
