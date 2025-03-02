#include "algorithms/state_machines/patrol/enemy_patrol_sm.h"
#include "actions/chase.h"
#include "actions/change_direction.h"
#include "actions/patrol.h"
#include "actions/lose_patience.h"
#include "actions/stop.h"
#include "algorithms/state_machines/patrol/transition_next_point.h"
#include "algorithms/state_machines/patrol/transition_aggro.h"
#include "algorithms/state_machines/patrol/transition_deaggro.h"
#include "algorithms/state_machines/patrol/transition_path_distance.h"
#include "algorithms/state_machines/patrol/transition_in_range.h"
#include "algorithms/state_machines/patrol/transition_no_patience.h"

EnemyPatrolSM::EnemyPatrolSM(float x, float y, float speed, float radius, Pawn& targetRef, Color color): 
	Npc(x, y, speed, radius, targetRef, color)
{
	Path& pathPtr = getPathRef();
	// patrolowana ścieżka:
	pathPtr.addPoint(50.0f, 100.0f);
	pathPtr.addPoint(50.0f, 400.0f);
	pathPtr.addPoint(50.0f, 700.0f);
	pathPtr.addPoint(50.0f, 400.0f);
	// inicjalizacja unordered_map
	npcActions[NpcAction::CHASE] = std::make_unique<Chase>(*this);
	npcActions[NpcAction::CHANGE_DIRECTION] = std::make_unique<ChangeDirection>(*this);
	npcActions[NpcAction::PATROL] = std::make_unique<Patrol>(*this);
	npcActions[NpcAction::LOSE_PATIENCE] = std::make_unique<LosePatience>(*this);
	npcActions[NpcAction::STOP] = std::make_unique<Stop>();

	// Stan "Patrol" (index: 0)
	stateMachine = std::make_unique<StateMachine>(  // heap allocation (obiekt jest całkiem złożony)
		NpcAction::PATROL,  // state Action
		NpcAction::STOP,  // entry 
		NpcAction::STOP); // exit
	stateMachine->addTransition(0, std::make_unique<TransitionNextPoint>(*this, 0, NpcAction::CHANGE_DIRECTION));
	stateMachine->addTransition(0, std::make_unique<TransitionAggro>(*this, 1, NpcAction::CHASE));

	// Stan "Atakuj" (index: 1)
	stateMachine->addState(NpcAction::CHASE, NpcAction::STOP, NpcAction::STOP);
	stateMachine->addTransition(1, std::make_unique<TransitionDeaggro>(*this, 2, NpcAction::CHASE));
	stateMachine->addTransition(1, std::make_unique<TransitionPathDistance>(*this, 2, NpcAction::CHASE));
	// Stan "Ubywająca cierpliwość" (index: 2)
	stateMachine->addState(NpcAction::LOSE_PATIENCE, NpcAction::STOP, NpcAction::STOP);
	stateMachine->addTransition(2, std::make_unique<TransitionInRange>(*this ,1, NpcAction::CHASE));
	stateMachine->addTransition(2, std::make_unique<TransitionNoPatience>(*this, 0, static_cast<int>(NpcAction::LOSE_PATIENCE)));
}

void EnemyPatrolSM::update()
{
	// Działanie Maszyny Stanów
	std::unique_ptr<std::vector<int>> resultActions = stateMachine->update(); // Akcje wynikowe

	for (int actionIndex : *resultActions) {

		npcActions[actionIndex]->execute();
	}
	updateFinished();
}

void EnemyPatrolSM::draw()
{
	drawAfterUpdate();

	Vector2 position = getPosition();
	if (!noPatience()) {
		DrawRectangle(position.x - 27.0f, position.y - 32.0f, 55.0f, 10.0f, BLACK);
		DrawRectangle(position.x - 25.0f, position.y - 30.0f, 50.0f * (getPatience() / 100), 5.0f, ORANGE);
	}
	DrawCircle(position.x, position.y, getHitboxRadius(), getColor());
}
