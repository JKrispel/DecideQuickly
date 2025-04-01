#pragma once
#include <memory>
// Abstract Class
class Action
{
public:
	float expiryTime;
	float priority;
	bool complete;	// czy akcja została wykonana

	Action(float priority, float expiryTime = 10.0f, bool complete = false)
		: expiryTime(expiryTime), priority(priority), complete(complete) {
	}
	virtual ~Action() = default;

	virtual void execute() = 0;
	bool interrupt();
	bool canDoBoth(const std::unique_ptr<Action>& other); // warunek równoczesnego wykonywania Akcji
	bool isComplete() const;	// getter dla complete
};

