#include "npc_follow_sm.h"
#include "raylib.h"
#include "actions/run.h"
#include "actions/walk.h"
#include "actions/stop.h"
#include "algorithms/state_machines/follow/transition_far_enough.h"
#include "algorithms/state_machines/follow/transition_close_enough.h"

#include <chrono>
#include "utils/log_execution_time.h"

NpcFollowSM::NpcFollowSM(float x, float y, float speed, float radius, Pawn& targetRef, Color color):
Npc(x, y, speed, radius, targetRef, color)
{
	// inicjalizacja unordered_map
	npcActions[NpcAction::RUN] = std::make_unique<Run>(*this, targetRef);
	npcActions[NpcAction::WALK] = std::make_unique<Walk>(*this, targetRef);
	npcActions[NpcAction::STOP] = std::make_unique<Stop>();

	// Stan "Stój w miejscu" (index: 0)
	stateMachine = std::make_unique<StateMachine>(  // heap allocation (obiekt jest całkiem złożony)
		static_cast<int>(NpcAction::STOP),  // state Action
		static_cast<int>(NpcAction::STOP),  // entry 
		static_cast<int>(NpcAction::STOP)); // exit
	stateMachine->addTransition(0, std::make_unique<TransitionFarEnough>(60.0f, *this, targetRef, 1, static_cast<int>(NpcAction::WALK)));
	// Stan "Idź za graczem" (index: 1)
	stateMachine->addState(static_cast<int>(NpcAction::WALK), static_cast<int>(NpcAction::STOP), static_cast<int>(NpcAction::STOP));
	stateMachine->addTransition(1, std::make_unique<TransitionCloseEnough>(60.0f, *this, targetRef, 0, static_cast<int>(NpcAction::STOP)));
	stateMachine->addTransition(1, std::make_unique<TransitionFarEnough>(200.0f, *this, targetRef, 2, static_cast<int>(NpcAction::WALK)));
	// Stan "Biegnij za graczem" (index: 2)
	stateMachine->addState(static_cast<int>(NpcAction::RUN), static_cast<int>(NpcAction::STOP), static_cast<int>(NpcAction::STOP));
	stateMachine->addTransition(2, std::make_unique<TransitionCloseEnough>(60.0f, *this, targetRef, 0, static_cast<int>(NpcAction::STOP)));
	stateMachine->addTransition(2, std::make_unique<TransitionCloseEnough>(200.0f, *this, targetRef, 1, static_cast<int>(NpcAction::STOP)));
}

void NpcFollowSM::update()
{
	std::string filename = "follow_sm";
	auto start = std::chrono::high_resolution_clock::now();

	std::unique_ptr<std::vector<int>> resultActions = stateMachine->update();	// Działanie Maszyny Stanów

	for (int actionIndex : *resultActions) {

		NpcAction action = static_cast<NpcAction>(actionIndex);
		npcActions[action]->execute();
	}	

	auto end = std::chrono::high_resolution_clock::now();
	double execution_time = std::chrono::duration<double, std::milli>(end - start).count();
	logExecutionTime(execution_time, filename);

	updateFinished();
}

void NpcFollowSM::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
	DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f, 5.0f, GREEN);
	DrawCircle(position.x, position.y, getHitboxRadius(), getColor());
}
