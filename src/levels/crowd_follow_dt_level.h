#pragma  once
#include "core/level.h"

class CrowdFollowDTLevel : public Level {

public:
	CrowdFollowDTLevel();

	~CrowdFollowDTLevel() override {
		std::cout << "Destroying FollowDTLevel" << std::endl;
	}
};