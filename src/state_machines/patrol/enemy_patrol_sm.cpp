#include "state_machines/patrol/enemy_patrol_sm.h"
#include "actions/chase.h"
#include "actions/change_direction.h"
#include "actions/patrol.h"
#include "state_machines/follow/transition_far_enough.h"
#include "state_machines/follow/transition_close_enough.h"

EnemyPatrolSM::EnemyPatrolSM(Pawn& targetRef) :
	Npc(50.0f, 100.0f, 7.0f, 20.0f, targetRef)
{
	// inicjalizacja unordered_map
	npcActions[NpcAction::CHASE] = std::make_unique<Chase>(*this);
	npcActions[NpcAction::CHANGE_DIRECTION] = std::make_unique<ChangeDirection>(*this);
	npcActions[NpcAction::PATROL] = std::make_unique<Patrol>(*this);

	Pawn& target = getTargetRef();
	// Stan "Stój w miejscu" (index: 0)
	stateMachine = std::make_unique<StateMachine>(  // heap allocation (obiekt jest całkiem złożony)
		static_cast<int>(NpcAction::STOP),  // state Action
		static_cast<int>(NpcAction::STOP),  // entry 
		static_cast<int>(NpcAction::STOP)); // exit
	stateMachine->addTransition(0, std::make_unique<TransitionFarEnough>(60.0f, *this, target, 1, static_cast<int>(NpcAction::WALK)));
	// Stan "Idź za graczem" (index: 1)
	stateMachine->addState(static_cast<int>(NpcAction::WALK), static_cast<int>(NpcAction::STOP), static_cast<int>(NpcAction::STOP));
	stateMachine->addTransition(1, std::make_unique<TransitionCloseEnough>(60.0f, *this, target, 0, static_cast<int>(NpcAction::STOP)));
	stateMachine->addTransition(1, std::make_unique<TransitionFarEnough>(200.0f, *this, target, 2, static_cast<int>(NpcAction::WALK)));
	// Stan "Biegnij za graczem" (index: 2)
	stateMachine->addState(static_cast<int>(NpcAction::RUN), static_cast<int>(NpcAction::STOP), static_cast<int>(NpcAction::STOP));
	stateMachine->addTransition(2, std::make_unique<TransitionCloseEnough>(60.0f, *this, target, 0, static_cast<int>(NpcAction::STOP)));
	stateMachine->addTransition(2, std::make_unique<TransitionCloseEnough>(200.0f, *this, target, 1, static_cast<int>(NpcAction::STOP)));
}
