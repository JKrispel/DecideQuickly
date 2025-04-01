#pragma  once
#include "core/level.h"

class FollowDTLevel : public Level {

public:
	FollowDTLevel();

	~FollowDTLevel() override {
		std::cout << "Destroying FollowDTLevel" << std::endl;
	}
};