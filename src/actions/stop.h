#pragma once
#include <decisions/action_manager/action.h>

class Stop : public Action {


public:
	Stop() : Action(1.0f) {}

	void execute() override;
};
