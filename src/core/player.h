#pragma once
#include <core/pawn.h>
#include <core/config.h>
#include <render/player_animation.h>

class Player: public Pawn {

private:
	Rectangle bounds{ 10, 10, screen_width - 20, screen_height - 20 };
	std::unique_ptr<PlayerAnimation> animation;
	float upperLimit;
	float bottomLimit;
	float leftLimit;
	float rightLimit;
	bool paused = false;
	int regenAmount = 10;	// szybkość regeneracji
	double regenTime = 0.0;
	const double regenDelay = 0.5;  // dmg debounce
public:
	Player();
	void draw() override;
	void update() override;
	void dealDmg(int hpAmount) override;
	bool callForPause() const;
	void clearPauseCall();
};
